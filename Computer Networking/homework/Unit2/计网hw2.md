# homework2

1. 网页和八个图片对象一共有九个对象
a) 采用非持久 HTTP 时，每个对象都需要单独的 TCP 连接，而无并发 TCP 连接情况下，该过程需要串行执行。故总用时 $T = RTT_0 + 8 \times RTT_0 = 9 \times RTT_0$
b) 若采用五个并发 TCP 连接，首先发起 HTML 请求，获取到 HTML 后，可以并行发起对图片对象的请求，第一个 RTT 请求五张图片，后一个 RTT 请求三张图片。故总用时为 $T = RTT_0 + RTT_0 + RTT_0 = 3 \times RTT_0$
c) 持久 HTTP 允许在同一个 TCP 中发送多个请求，但考虑到无流水线，只能依次发送这九个请求。$T = 9 \times RTT_0$
d) 若采用流水线方式，可以在请求 HTML 后，几乎无间隔地一次请求图片对象。故 $T = RTT_0 + RTT_0 = 2 \times RTT_0$
2. * 根域名服务器：是 DNS 的顶层，负责存储所有顶级域名服务器的地址。是 DNS 解析过程的起点——当本地域名服务器无法解析某个域名（即没有缓存）时，会首先向根域名服务器查询，从而得到适当的顶级域名服务器地址。
   * 顶级域名服务器：负责管理特定顶级域的所有域名记录包括一些公用的顶级域和所有国家的顶级域。当根域名服务器返回顶级域名服务器的地址后，本地域名服务器会向该顶级域名服务器查询，以获取对应的权威域名服务器的地址。
   * 权威域名服务器：存储特定域名的详细 DNS 记录，向本地域名服务器的请求响应目标域名的具体信息。
   * 本地域名服务器：通常是用户的网络中的 DNS 服务器，负责缓存和解析 DNS 查询。当用户输入域名时，首先检查缓存中是否有相应的 IP，如果有则直接返回，否则从根服务器开始查询。
3. 设最低缓存命中率是 p， 则有流量强度 $I = \frac{aL}{R} \times (1 - p) = \frac{16 \times 1.2 Mbps}{15Mbps} \times(1 - p) \leq 1$，计算得 $p_{min} \approx 21.9%$
4.  a)  1. 域名注册服务商需要在 .com 顶级域名服务器注入的 RR 信息：
            * `(startup.com, ns1.startup.com, NS)`
            * `(ns1.startup.com, IP2, A)`
            * `(startup.com, ns2.startup.com, NS)`
            * `(ns2.startup.com, IP3, A)`
        2. `"ns1.startup.com"`, `"ns2.startup.com"`上应包含： * `(www.startup.com, IP1, A)`
            * `(startup.com, smtp1.startup.com, MX)`
    b)  该过程如下：
        * 用户在浏览器中输入网址 `www.startup.com` 发起请求，浏览器需要获取该域名对应的 IP 地址
        * 用户主机向本地 DNS 服务器发送一个 DNS 查询报文，内容包含主机名`www.startup.com`
        * 本地 DNS 服务器发现没有缓存，向根域名服务器转发该请求报文
        * 根域名响应 "com" 对应的顶级域 DNS 服务器，返回 "com" 域的 NS 记录
        * 本地 DNS 服务器根据 NS 记录向其中一个 com DNS 服务器发送请求，内容包含主机名`www. startup.com`
        * com DNS 服务器返回 `startup.com` 对应的权威 DNS 服务器的 NS 记录
        * 本地 DNS 服务器根据 NS 记录向其中一个权威 DNS 服务器（`ns1.startup.com` 或 `ns2.startup.com`）发送请求，内容包含主机名`www.startup.com`
        * 权威 DNS 服务器返回包含 `www.startup.com` 对应的 IP 地址(IP1)的 A 记录
        * 本地 DNS 服务器将该 IP 地址返回给用户主机
        * 用户主机收到 IP 地址后，通过 HTTP 协议向该 IP 地址的 Web 服务器发送 HTTP 请求报文，内容为获取网站主页对应的报文
        * Web 服务器接受请求后，处理并返回 HTML 内容到用户的浏览器
        * 用户浏览器收到数据后，解析并渲染网站页面，最终显示给用户
其中与 Web 无关、未明确提到协议的部分均采用运行在 UDP 协议上的 DNS 协议