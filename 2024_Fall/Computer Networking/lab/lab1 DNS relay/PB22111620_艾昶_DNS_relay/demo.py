import socket
import struct
from time import time
import threading


def config(path):
    """根据配置文件提取"""
    name2ip = {}
    with open(path, 'r', encoding='utf-8') as file:     # read file with path
        for line in file:
            if line.strip():  # 判断行非空
                ip, domain = line.rstrip().split(' ', 1)    # 将一行分成两部分, 分别为 ip 和 domain
                name2ip[domain] = ip    # 以行为单位, 将域名映射到 ip, 构造查找表

    return name2ip

# query_part() 中的 unpack, pack 针对的是问题节
class query_part():
    """一条问题记录, 解析+打包"""
    def __init__(self) -> None:
        self.name = ""
        self.idx = 0
        self.type = None
        self.classify = None
        self.querypart = None
# 长度不固定的域名怎么解析, 怎么打包
    def unpack(self, data):
        """*****************************************************************
        ******解析二进制查询报文中的问题节, data -> name, type, class**********
        *****************************************************************"""
        self.name = []
        i = 0
        length = 0
        label = ''
        while True:
            d = data[i]
            if length == 0:    # 当前标签已读完(或尚未开始读取)
                self.name.append(label)
                label = ''
                if d == 0:  # 已读完全部标签
                    break
                else:
                    length = int(d)     # 未读完全部标签, 记录下一标签长度
            else:                   # 每次读取一个字符, 标签剩余长度 -1
                label += chr(d)
                length -= 1
            i += 1          # 指针自增
        self.name = '.'.join(self.name[1:])

        self.type, self.classify = struct.unpack('>HH', data[i + 1:i + 5])  # 因为不需要进行对齐
        self.idx = i + 5
        self.querypart = data[0:self.idx]

    def pack(self):
        # 可能要将请求转发给其他 DNS 服务器
        # 为什么要打包问题节? 本来不就是打包好的?
        """打包回二进制"""
        """*****************************************************************
        ******将问题节打包回二进制查询报文, name, type, class -> data**********
        *****************************************************************"""
        # labels = self.name.split('.')
        # data = bytearray()
        # for label in labels:
        #     data.append(len(label))             # append 将整个参数作为一个整体传入 data
        #     data.extend(label.encode('utf-8'))  # extend 将参数各部分直接加入 data
        # data.append(0)          # 结束符
        # data.extend(struct.pack('>HH', self.type, self.classify))   # 将 type, classify 加到域名之后
        # return data
        return self.querypart

# message() 中的 unpack 对象是整个报文
# 应答报文的各个部分怎么获得, 每个字段的内容怎么获得
class message():
    """一封DNS报文, 解析头部, 若是查询报文则进一步解析问题节"""
    def __init__(self, data) -> None:
        self.data = data
        self.unpack(data)

    def unpack(self, data):
        # DNS 报文头部解封装, p5
        # data[0]-data[11], 以字节为单位
        self.id, self.flags, self.quests, self.answers, self.author, self.addition = struct.unpack('>HHHHHH', data[0:12])       # '>HHHHHH' what's the meaning? 12 bytes, 6 H

        self.qr = data[2] >> 7      # or self.qr = self.flags >> 15
        if self.qr == 0:  # 是查询报文, 进一步解析问题节, p7
            self.query = query_part()
            self.query.unpack(data[12:])        # 请求报文 = 头部 + 问题, 头部占 12 字节, 故从 12 开始到结束均为问题节

    def r_pack(self, ip):   # DNS 报文答复节
        """*****************************************************************
        ****根据ip资源(通过 config 得到)和当前查询报文内容生成回复报文, 注意哪些头部字段要修改******
        *****************************************************************"""
        # response_header 为报文头部, 有 12 bytes
        if ip != '0.0.0.0':
            flags = 0x8180
        else:
            flags = 0x8583
        answers = 1
        timetolive = 200
        datalength = 4
        s = ip.split('.')
        response_header = struct.pack('>HHHHHH', self.id, flags, self.quests, answers, self.author, self.addition)
        question = self.query.pack()    # 打包问题节
        # Qname, Qtype, Qclass, TTL, Rdatalength, Rdata(ip address)
        name = 0xc00c   # As a pointer to position 0c, c is a symbol to pointer
        answer = struct.pack('>HHHLH', name, 1, 1, timetolive, datalength)
        answer += struct.pack('BBBB', int(s[0]), int(s[1]), int(s[2]), int(s[3]))
        return response_header + question + answer

# 收到报文后如何处理, 判断是否在配置文件中以及对应 IP 是否有意义, 如何获得应答报文的数据部分
class relay_server():
    """中继器, 接收DNS报文并处理"""
    def __init__(self, path) -> None:
        self.config = config(path)  # 调用函数解析配置文件, 存储为字典{name: ip}
        self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.s.bind(('0.0.0.0', 53))
        self.s.setblocking(False)
        self.nameserver = ('114.114.114.114', 53)  # 一个公共DNS服务器, 也可选择其他, 注意事先测试
        self.transaction = {}       # 记录下无法处理传给公共 DNS server 的报文信息

    """
    1. 拦截-intercept: 请求域名在配置中, 且对应 IP 为 0.0.0.0, 无意义, 返回表示域名不存在的应答
    2. 本地解析-local resolved: 请求域名在配置中, 且对应 IP 有意义, 向客户端返回对应 IP
    3. 中继-relay: 若请求域名不在配置中, 将请求转发到一个正常的 DNS 服务器, 将服务器发来的应答返回给客户端
    """
    def process(self, data, addr):
        """报文处理"""
        start_time = time()
        m = message(data)
        """*****************************************************************
        ****************解析收到的报文, 生成回复返回给请求方*******************
        *****************************************************************"""
        if m.qr == 0:       # 是查询报文
            name = m.query.name

            if name in self.config:   # 查询对象在配置中, 且为 IPv4
                ip = self.config[name]  # 找到 domain 对应的 ip
                response = m.r_pack(ip)
                self.s.sendto(response, addr)
                if ip == "0.0.0.0":         # ip 无意义
                    print('query to %+70s'%name, 'handled as      intercept, takes','%fs'%(time()-start_time),sep='\t')
                    # print('the ip of that domain is %15s'%ip)
                else:
                    print('query to %+70s'%name, 'handled as local resolved, takes','%fs'%(time()-start_time),sep='\t')
                    # print('the ip of that domain is %15s'%ip)
            else:   # 查询对象不在配置中, 是中继请求
                self.s.sendto(data, self.nameserver)    # 向公共 DNS server 求助
                self.transaction[m.id] = (addr, name, start_time)   # 记录下来
        else:               # 不是查询报文, 可能是来自公共 DNS server 的答复
            if m.id in self.transaction:
                target_addr, name, start_time = self.transaction[m.id]
                self.s.sendto(data, target_addr)
                print('query to %+70s'%name, 'handled as          relay, takes','%fs'%(time()-start_time),sep='\t')

                del self.transaction[m.id]

    def run(self):
        """循环接收DNS报文"""
        while True:
            try:
                data, addr = self.s.recvfrom(1024)
                threading.Thread(target=self.process, args=(data, addr)).start()  # 多线程
            except Exception:   # what's the meaning? 例外? 中断?
                pass


if __name__ == "__main__":
    path = 'example.txt'
    r = relay_server(path)
    r.run()
