# Outline of Compiler

[TOC]

## Lexical Analysis

- 程序是以字符串的形式传递给编译器的, 词法分析的目的是将输入字符串识别为有意义的子串
- 词法分析器对源程序采用非常局部的观点, 只考虑一个字符或一个字符序列,
而不判断该字符在此处是否合理, 如 `fi (<expr>) { do something }` 并不会报错,
而是将 `fi` 识别为 id

### 词法分析器的自动生成

1. 用正则表达式描述 token
2. 用状态转换图识别 token
    - 冲突的解决
        1. 最长匹配原则: 选择满足匹配的最长前缀
        2. 优先匹配原则: 选择先列出的模式进行匹配
3. NFA(Non-Deterministic Finite Automata) and DFA(Deterministic Finite Automata)
    - NFA: 存在状态对某输入符号有不止一种转移路径
        - 对于一个 token, 常需要进行***尝试+回退***, 效率很低, 所以需引入 `DFA`
    - DFA: 所有状态对任意输入符号有唯一的转移路径
    - DFA 与 NFA 在功能上等价, 但前者运行效率更高(虽然需要占用更多内存,
    但两害相权取其轻)
4. RE $\to$ NFA $\to$ DFA $\to$ Simplified DFA(这是机械的构造方式,
    手工构造时不必严格遵循)
    - RE $\to$ NFA
        - Thompson's Construction
            1. 构造识别 $\epsilon$ 和字母表中任一符号的 NFA
            2. 构造主算符为***选择, 连接, 闭包***的 NFA
    - NFA $\to$ DFA
        - 子集构造法: DFA 的一个状态是 NFA 的状态集合, 读取任一字母表的符号后, 若 
        NFA 能够到达状态 $s_1, s_2, \ldots, s_k$, 则 DFA 能够到达状态
        $S = \{s_1, \ldots, s_k\}$
            1. NFA 的初始状态的 $\epsilon-$闭包对应 DFA 的初始状态
            2. 针对每个 DFA 状态, 求输入每个符号后能够到达的 NFA 状态的 $\epsilon-$
            闭包并集, 该集合对应 DFA 中的一个状态, 否则将这个状态加入 DFA
            3. DFA 中包含 NFA 接受状态的状态为 DFA 的接受状态
    - DFA  $\to$ Simplified DFA
        - 状态合并法: DFA 中接受任何符号后都转移到相同状态的状态不可区分, 
        可将其合并为一个状态
            1. 按是否是接受状态将 DFA 的状态分为两个集合: 接受状态集合, 
            非接受状态集合
            2. 对于非接受状态集合, 按接受任意符号后是否到达相同的状态继续划分,
            直至任一集合中的状态之间均不可区分

## Parser

- 语法分析的目的是教会计算机判断输入的合法性

### 上下文无关文法 CFG

- 定义
- 推导
- 文法二义性
    - 某些句子存在不止一种最左/右推导, 或者不止一棵分析树, 则该文法是二义的
    - 可通过定义运算优先级与结合律来消除
- 可以先画出最简 DFA, 然后根据 DFA 写上下文无关文法

### 自顶向下

- 针对输入串, 从文法的开始符号出发, 尝试根据产生式规则推导出该输入串

#### 递归下降

- 数据结构: 一个输入缓冲区和 `lookahead` 指针
- 基本思想: 
    1. 为每个非终结符写一个分析过程
    2. 用 `lookahead` 得到的符号指导产生式规则的选择
- 分析过程
    - 自左向右扫描输入串
    - 设计一个 `match()` 函数, 将 `lookahead` 
    指向的符号与产生式迭代生成的终结符匹配, 
    若匹配成功, 将 `lookahead` 右移
    - 递归调用非终结符的分析过程进行分析
- 不足之处
    - 自顶向下分析无法处理左递归, 需要消除左递归
        - $A \to A\alpha | \beta$
        - $A \to \beta A', A' \to \alpha A' | \epsilon$
    - 若文法有左公因子, 需提取
        - $A \to \alpha \beta_1 | \alpha \beta_2$
        - $A \to \alpha A', A' \to \beta_1 | \beta_2$
    - 非终结符可能有多个产生式, 由于信息不足, 无法准确预测. 
    常常需要进行多次尝试与回溯, 代价太高

#### LL(1) 文法

- 与递归下降类似, 但通过向前看一些符号来预测需要用到的产生式, 不需要进行尝试与回溯
- Two important functions
    - $FIRST(\alpha) = \{a | \alpha \Rightarrow^* a\ldots, a \in V_T\}$
        - 意义: 可从 $\alpha$ 推导得到的串的首符号集合(考虑 $\epsilon$)
        - 计算(需考虑所有 X 在左侧的产生式)
            - If $X \in V_T$, then $FIRST(X) = \{X\}$
            - If $X \in V_N, X \to \epsilon$, then $\epsilon \in FIRST(X)$
            - If $X \in V_N, X \to Y_1Y_2\ldots Y_k$, 
                - If $a \in FIRST(Y_i), \epsilon \in FIRST(Y_1), \ldots,
                FIRST(Y_{i-1})$, then $a \in FIRST(X)$
                - If $\epsilon \in FIRST(Y_1), \ldots, FIRST(Y_k)$, then
                $\epsilon \in FIRST(X)$
    - $FOLLOW(A) = \{a | S \Rightarrow^* \ldots Aa \ldots, a \in V_T\}$
        - 意义: 在推导过程中可能出现 A 右边相邻位置的终结符的集合(不考虑 
                $\epsilon$)
        - 计算(需考虑所有 A 在右侧的产生式)
            - 若 $A$ 为开始符号, 将 $\$$ 加入到 $FOLLOW(A)$ 中
            - 若 $A \to \alpha B \beta$, 则 $FIRST(\beta) \setminus \{\epsilon\}
            \subseteq FOLLOW(B)$
            - 若 $A \to \alpha B$ 或 $A \to \alpha B \beta, \epsilon \in 
            FIRST(\beta)$, 则 $FOLLOW(A) \subseteq FOLLOW(B)$
- LL(1) 文法
    - 定义: 任何两个产生式 $A \to \alpha, A \to \beta$ 都满足两个条件
        1. $FIRST(\alpha) \cap FIRST(\beta) = \emptyset$
        2. 若 $\beta \Rightarrow^* \epsilon$, 则 $FIRST(\alpha) \cap
        FOLLOW(A) = \emptyset$
    - 上述两个条件是为了保证对于一个输入能够选择确定的一个产生式, 也是判断依据
    - LL(1) 文法不含左递归, 没有公共左因子, 不是二义的
- 非递归预测分析
    - 数据结构: 输入缓冲区, 一个栈, `lookahead` 指针, 预测分析表 M
    - 预测分析表的构造
        - 对文法的每个产生式 $A\to \alpha$, 执行
            1. 对 $FIRST(\alpha)$ 的每个终结符 $a$, 将 $A\to \alpha$ 加入 $M[A, a]$
            2. 若 $\epsilon \in FIRST(\alpha)$, 即 $\alpha \Rightarrow^* \epsilon$,
            则对 $FOLLOW(A)$ 的每个终结符 $a$, 将 $A\to \alpha$ 加入 $M[A, a]$
            (包括 `$`)

### 自底向上

- 针对输入串, 尝试根据产生式规则归约到文法的开始符号
- 移进-归约分析方法: 用栈保存已扫描过的文法符号, 缓冲区存放还未分析的符号
    - 移进(shift): 将下一输入符号放到栈顶形成句柄
    - 归约(reduce): 将句柄替换为对应的产生式的左部非终结符
    - 接受(accept): 分析成功
    - 报错(error): 发现语法错误
- 句型的句柄: 可归约串
- 最右句型: LR 语法分析的每一步都形成一个 config: $(s_0X_1s_1\ldots X_ms_m, |
        a_ia_{i+1}\ldots a_n\$)$. 其中 $X_1\ldots X_m a_i\ldots a_n$ 为
        `最右句型`, $X_1\ldots X_m$ 是最右句型的一个前缀, 称为`活前缀`,
        每个前缀对应一个状态
- LR(k) 中的 k 表示前看符号的数量

#### Simple LR

- LR(0) 项目, 简称项目
    - 在右部的某个地方加点的产生式, 加点的目的是用来表示分析过程中的状态
    - 项目代表了一个可能的前缀
- 构造识别活前缀的 DFA
    - 增广文法: 额外新增一个产生式 $E' \to E$, 用来判断分析何时成功
    - 构造 LR(0) 项目集规范族
        - 如果 $A\to \alpha \cdot B\beta$ 在 $closure(I)$ 中, 且 $B\to \gamma$
        是产生式, 那么 $closure(I) \cup = \{B \to \cdot \gamma\}$
        - 若 $goto(I_i, X) = I_j$, 则 $I_j = \emptyset, \forall A \to \alpha
        \cdot X \beta \in I_i, I_j \cup = \{ A \to \alpha \cdot X \beta \}$
- 构造 SLR 分析表(因为下面需要用到 $FOLLOW$ 集, 所以需要提前计算)
    - 状态 $i$ 从 $I_i$ 构造, 它的 $action$ 函数如下确定(下面的 a 均为终结符)
        - 若 $[A \to \alpha \cdot a \beta] \in I_i, goto(I_i, a) = I_j$, 则令
        $action[i, a] = sj$
        - 若 $[A \to \alpha \cdot] \in I_i, A \neq S'$, 则对 $\forall a 
        \in FOLLOW(A)$, 令 $action[i, a] = rj$, 其中 $j$ 是该产生式的编号
        - 若 $[S' \to S \cdot] \in I_i$, 则令 $action[i, \$] = acc$
    - 状态的 $goto$ 函数如下确定
        - 对所有非终结符 $A$, 若 $goto(I_i, A) = I_j$, 那么 $goto[i, A] = j$
- 一个上下文无关文法 G, 通过上述算法构造出 SLR 语法分析表, 且表项中没有移进-
归约冲突和归约-归约冲突, 那么 G 就是 SLR(1) 文法, 常写作 SLR 文法
- 其中 1 代表了当看到某个产生式右部时, 只需要再向前看一个符号就可以决定是否使用
该产生式进行归约

#### 规范的 LR 方法

- 目标: SLR 的描述能力优先, 故引入规范的 LR 方法吗在识别或前缀 DFA 的状态中,
    增加信息, 排除一些不正确的归约操作
- 方法: 添加了前向搜索符
    - 一个项目 $A \to \alpha \cdot \beta$, 如果最终用这个产生式进行归约之后,
    期望看见的符号是 $a$, 则这个项目的前向搜索符是 $a$
    - 上述项目写为 $A \to \alpha \cdot \beta, a$
    - 使用注意事项
        - 若 $\beta$ 不为空, $a$ 不起作用
        - 若 $\beta$ 为空, 如果下一个输入符号是 $a$, 将按照 $A \to \alpha$
        进行归约, $a$ 的集合是 $FOLLOW(A)$ 的子集
- 与 SLR(1) 分析的区别: 项目集的定义发生了改变: $LR(0) \Rightarrow LR(1)$
- 构造识别活前缀的 DFA / 构造 LR(1) 项目族
    - 若有项目 $[A \to \alpha \cdot B \beta, a] \in closure(I)$, 而 $B \to
    \gamma$ 是产生式, 则 $closure(I) \cup = [B \to \cdot \gamma,FIRST(\beta a)]$
    - 若有项目 $[A \to \alpha \cdot X \beta, a] \in I_i, goto(I_i, X) = I_j$, 
    则 $closure(I_j) \cup = [A \to \alpha \cdot X \beta, a]$
- 构造规范的 LR 分析表(如果构造过程中出现了冲突, 那么文法不是 LR(1))
    - 状态 i 由 I_i 构造, 其 $action$ 函数如下确定
        - 若 $[A \to \alpha \cdot a \beta, b] \in I_i, goto(I_i, a) = I_j$, 则令
        $action[i, a] = sj$(与 SLR 一致)
        - 若 $[A \to \alpha \cdot, a] \in I_i, goto(I_i, a) = I_j, A \neq S'$, 
        则令 $action[i, a] = rj$(与 SLR 不同)
        - 若 $[S' \to S] \in I_i$, 则令 $action[i, \$] = acc$
    - 状态 i 的 $goto$ 函数如下确定
        - 若 $goto(I_i, A) = I_j$, 则令 $goto[i, A] = j$

## Intermediate Representation

- 利用 IR 可将编译器的前后端分离, 降低开发成本
- 常见的中间表示
    - 后缀表示
    - 语法树或有向无环图
    - 三地址码(TAC): 最多一个算符, 三个计算分量
    - 静态单赋值形式(SSA): 所有赋值指令都是对不同名字变量的赋值,
    同一个变量在所有控制流路径上都被定值
- 基本块
    - 定义: 连续的三地址指令序列, 控制流从它的开始进入, 并从末尾离开,
    中间不能停止或分支
    - 基本块划分算法
        - 输入: 三地址指令序列
        - 输出: 基本块列表
        - 算法
            - 确定基本块的第一条指令, 即首指令(leader)
                1. 指令序列的第一条三地址指令是首指令
                2. 任一转移指令的目标指令是首指令
                3. 紧跟一条转移指令的指令是首指令
            - 每个首指令对应的基本块包括了从它自己开始, 直到下一个首指令
            (不含) 或指令序列结之间的所有指令
- 流图(flow graph)
    - 流图的节点是一些基本块
    - 从基本块 B 到 C 之间有一条边, 当且仅当 C 的第一条指令可能紧跟在 B
    的最后一条指令之后执行, 判定方式如下:
        - 有一个从 B 的结尾跳转到 C 的开头的跳转指令 
        - 在原三地址指令序列中, C 紧跟在 B 之后, 且 B 的结尾不是无条件跳转指令
- 循环(loop)
    - 流图的一个节点集合 L 是一个循环, 如果它满足
        - 该集合有唯一的入口节点
        - 任意节点都有一个到达入口节点的非空路径, 且该路径全部在 L 中
    - 不包含其他循环的循环叫做内循环
        
### 语法制导翻译(Syntax-Directed Translation, SDT)

- 使用 CFG 引导对语言的翻译, 是一种面向文法的翻译技术
- 应用
    1. 中间代码生成
    2. 语义分析: 对结构上正确(经过了词法翻译)的源程序进行上下文有关性质的审查
- 问题
    1. 如何表示语义属性
        - 为 CFG 中的文法符号设置语义属性, 用来表示语法成分对应的语义信息
    2. 如何计算语义属性
        - 对于给定的输入串, 构建语法分析树,
          利用与产生式相关联的语义规则来计算分析树中各节点对应的语义属性值

#### 语法制导定义(Syntax-Directed Definition, SDD)

- 定义
    - 基础的上下文无关文法
    - 每个文法符号有一组属性
    - 每个文法产生式 $A \to \alpha$ 有一组形为 $b = f(c_1, c_2, \ldots, c_k)$ 
    的语义规则, 其中 $f$ 是函数, $b, c_1, \ldots, c_k$ 是产生式文法符号的属性,
    - 综合属性(synthesized attribute): 如果 $b$ 是 $A$ 的属性, $c_1, \ldots,
    c_k$ 是产生式右部文法符号的属性或 $A$ 的其他属性, 那么称 $b$ 是 $A$ 
    的综合属性(终结符(如 num, id 等)只能有综合属性, 属性值由词法分析给定, 无需计算)
    - 继承属性(inherent attribute): 如果 $b$ 是右部某文法符号 X 的属性, 
    $c_1, \ldots, c_k$ 是 $A$ 和产生式右部文法符号的属性, 那么称 $b$ 是
    $X$ 的继承属性
- 属性依赖图(attribute dependency graph)
  是一个描述分析树中节点间属性依赖关系的有向图
    - 属性为点, 分析树中每个节点的每个属性对应依赖图中的一个节点
    (继承属性放左边, 综合属性放右边)
    - 属性依赖关系为边, 如果属性 $X.a$ 依赖属性 $Y.b$ 的值,
    则依赖图中有一条从 $Y.b$ 指向 $X.a$ 的有向边
- 属性可行的计算顺序是属性依赖图的拓扑排序, 当图中出现环时, 
表明属性之间存在循环依赖关系, 不存在拓扑排序
    - 使用 S-SDD, L-SDD 来避免出现环
- 应用
    - 抽象语法树的构造
    - 类型检查
    - 中间代码生成

##### S-SDD

- 仅仅使用综合属性的 SDD 称为 S 属性的 SDD
    - S-SDD 可以按照语法分析树节点的任何自底向上顺序来计算属性值
    - S-SDD 可以在自底向上的语法分析中实现, eg: LL 分析器

##### L-SDD

- L-SDD 的直观含义
    - 在一个产生式所关联的各属性之间, 依赖图的边可以从左到右, 但不能从右到左
    - 可以在 LR 分析器或者 LL 分析器中实现, 更加一般化(每个 S-SDD 都是 L-SDD)
- 定义
    - 任意产生式 $A \to X_1 \ldots X_n$, 其右部符号 $X_i$
      的继承属性仅依赖下列属性
        - $A$ 的继承属性
        - 产生式中 $X_i$ 左侧符号 $X_1, \ldots, X_{i-1}$ 的属性
        - $X_i$ 本身的属性, 但 $X_i$ 的属性之间不能再依赖图中形成环路

##### 抽象语法树的构造

- 将算符和关键字作为内部节点, 与分析树等价, 但更为简略. 语法制导翻译可基于分析树或语法树
- 建立算符表达式的语法树
    - 对基本运算对象节点
        - 一个域存放对象类别, 另一个域存放其值, 也可以存放指针,
          指向保存在其他地方的属性值
        - eg: $[num, val], [id, ptr]$
    - 对算符节点
        - 一个域存放算符并作为该节点的标记, 其余两个域存放指向运算对象的指针
    - `mknode(op, left, right)`
        - 建立一个运算符节点, 标号是 `op`, 两个域 `left, right`
        分别指向左右子树
    - `mkleaf(id, entry)`
        - 建立一个标识符节点, 标号为 `id`, 一个域 `entry`
        指向标识符在符号表中的入口
    - `mkleaf(num, val)`
        - 建立一个数节点, 标号为 `num`, 一个域 `val`
        用于存放其值
- S-SDD 的语法树构造
    - 每个属性都是综合属性
    - 在依赖图中, 总是通过子节点的属性值来计算父节点的属性值
        - 适合与自底向上的语法分析一起计算
            - 在用产生式归约时, 即在构造完分析树的中间节点时,
            计算相关属性
        - 也可与自顶向下的语法分析一起计算
            - 递归下降分析中, 可以在过程 $A()$ 的最后一步计算 A
            的属性(此时 A 调用的其他子过程已经处理结束)
- L-SDD 的语法树构造
    - S-SDD 无法处理消除左递归得到的文法, 因此引入了 L-SDD
    的语法树构造

#### 语法制导翻译方案

- 语法制导翻译方案是在产生式右部中嵌入了程序片段(称为语义动作)的 CFG
- SDT 可以看作 SDD 的具体实施方案, 有如下两种实现方式
    - 通过建立语法分析树来实现 SDD 的方案
    - 在语法分析中, 边分析边计算的方案
        - 与 LR/LL 分析方法结合

##### S-SDT

- 将 "S-SDD" 转为 "S-SDT" 的方法
    - 将每个语义动作放在产生式最后(因为只有继承属性, 放在最后准没错)
    - 称为后缀翻译方案
- 实现方式1: 先建树, 后计算(基于分析树的语法制导翻译方案)
    1. 建立语法分析树
    2. 将语义动作视为虚拟节点挂在产生式左部文法符号对应的节点的右侧
    3. 从左到右, 深度优先地遍历分析树, 在访问虚拟节点时执行相应动作
        (也可以理解为回退时执行)
- 实现方式2: 边分析, 边计算
    - 综合属性可通过自底向上的 LR 方法来计算, 当发生归约时执行相应的语义动作
    - 可通过扩展的 LR 语法分析栈来实现
        - 在分析栈中使用一个附加的域来存放综合属性值. 若支持多个属性,
            可在栈中存放指针, 每个栈元素包含状态, 文法符号, 综合属性三个域.
        - 也可以将分析栈看作三个平行的栈, 分别是状态栈, 文法符号栈, 综合属性栈.
            分开看的理由是, 出入栈并不完全同步
        - 语义动作将修改为堆栈中文法符号属性的计算
            - e.g. $A \to XYZ \{A.a = f(X.x, Y.y, Z.z)\} \Rightarrow
                notation[top - 2] = A, \quad val[top - 2] = f(val[top - 2],
                val[top - 1], val[top]), \quad top = top - 2$
    - 采用自底向上分析时, 首先给出 SDT, 然后将 SDT 变为可执行的代码段,
        放到产生式的尾部, 这就构成了翻译程序. 随着语法分析的进行,
        归约前调用相应的语义子程序, 完成翻译的任务

##### L-SDT

- 定义
    - 如果每个产生式 $A \to X_1 \ldots X_n$ 的每条语义规则计算的属性要么是
        $A$ 的综合属性, 要么是 $X_j$ 的继承属性, 但他仅依赖
        - 该产生式中 $X_1, \ldots, X_{j-1}$ 的属性
        - $A$ 的继承属性
        - $X_j$ 的其他属性, 且属性间依赖关系不能成环
    - 那么称该 SDT 为 L-SDT
- 将 L-SDD 转为 L-SDT 的规则
    - 将计算一个产生式左部符号综合属性的动作放在这个产生式右部的最右端
    - 将计算某个非终结符 $A$ 的继承属性的动作插入产生式右部中紧靠 $A$
        的本次出现前面的位置

- 实现方式1: 与递归下降分析结合
    - 递归下降分析器的设计
        - 为每个非终结符 $A$ 构造一个函数
            - $A$ 的每个继承属性对应该函数的一个形参
            - 函数返回值是 $A$ 的综合属性
        - 在函数体中
            - 首先选择适当的 $A$ 的产生式
            - 用局部变量保存产生式中文法符号的属性
            - 对产生式中的终结符, 读入符号并获取其综合属性(由词法分析得到)
            - 对产生式中的非终结符, 调用相应函数, 记录返回值
- 实现方式2: 与 LR 分析结合
    - 无法将带有继承属性的 L-SDD 直接与 LR 结合起来, 可将产生式中嵌入的动作删除,
        挪到产生式最右端
    - 将 L-SDD 转为 SDT
    - 对于产生式 $A \to \alpha {a} \beta$, 其中 $a$ 是语义动作
        - 引入新的非终结符 $M$ 代替 ${a}$, 形成 $A \to \alpha M \beta$
        - 引入新的产生式$M \to \epsilon$
        - 修改 $a$ 得到 $a'$, 将 $a$ 需要的 $A, \alpha$ 中属性作为 M
            的继承属性复制, 计算各属性, 将这些属性作为 $M$ 的综合属性保存,
            并将 $a'$ 与 $M \to \epsilon$ 关联起来
#### Conclusion

- 语义规则的两种描述方法: 语法制导定义和语法制导翻译方案
- 设计简单问题的 SDD, SDT 是本章的重点和难点

### Intermediate Code Generation

#### Brief Introduction for IR Generation

##### Common TAC

- 运算, 赋值语句: `x = y op z, x = op y, x = y`
- 无条件转移: `goto L`
- 条件转移1: `if x goto L, if False x goto L`
- 条件转移2: `if x relop y goto L`
- 过程调用:
    - param x1
    - param x2
    - ...
    - param xn
    - call p, n     // p 为子过程, n 为参数个数
- 过程返回: `return y`
- 索引赋值: `x = y[i], x[i] = y`
- 地址和指针赋值: `x = &y, x = *y, *x = y`

##### IR Generation

- 表达式的翻译
- switch 语句的翻译
- 过程或函数的翻译
- 控制流语句的翻译
- 类型检查
- 声明语句的翻译
- 记录或结构体的翻译
- 数组寻址的翻译

#### Simple sentences

##### Expression

- 表达式文法: 
    - $S \to id = E$
    - $E \to E_1 + E_2 | -E_1 | \;(E_1)\; |\; id$
- 语法制导翻译方案
    - 属性: E.place 存放结果的地址
    - 语义动作
        - 从符号表中获取 id 的地址, 如果不存在, 返回 nil: `lookup(id.lexeme)` 
        - 产生临时变量, 保存中间结果: `newTemp()`
        - 将地址, 运算符, 临时变量拼接成字符串. 输出翻译后的三地址指令: `gen(addr, op, arg1, arg2)`
    - 具体实现:
        - $S \to id = E$
            ```C
            {
                p = lookup(id.lexeme);
                if(p != nil)
                    gen(p, '=', E.place);
                else 
                    error;
            }
            ```
        - $E \to E_1 + E_2$
            ```C
            {
                E.place = newTemp();
                gen(E.place, '=', E1.place, '+', E2.place);
            }
            ```
        - $E \to - E_1$
            ```C
            {
                E.place = newTemp();
                gen(E.place, '=', 'uminus', E1.place);
            }
            ```
        - $E \to (E_1)$
            ```C
            {
                E.place = E1.place;
            }
            ```
        - $E \to id$
            ```C
            {
                p = lookup(id.lexeme);
                if(p != nil)
                    E.place = p;
                else
                    error;
            }
            ```

##### switch

- switch 文法:
    ```C
    switch(E){          // E 是一个表达式
        case V1: S1     // V 是常量, S 是语句(序列)
        case V2: S2
        ...
        case Vn-1: Sn-1
        default: Sn
    }
    ```
- 语法制导翻译方案
    - 分支数较少时
        ```C
            t = E.place
            if t != V1 goto L1
            S1
            goto next   // 没有 break 时, next 指向物理上的下一个基本块
        L1: if t != V2 goto L2
            S2
            goto next
        L2: ...
            ...
        Ln-2:
            if t != Vn-1 goto Ln-1
            Sn-1
            goto next
        Ln-1:
            Sn
        next:
            ...
        ```
    - 分支数较多时, 将分支测试代码集中在一起
        ```C
            t = E.place
            goto test
        L1: S1
            goto next
        L2: S2
            goto next
            ...
            ...
        Ln: Sn
            goto next
            
        test:
            if t == V1 goto L1
            if t == V2 goto L2
            ...
            if t == Vn-1 goto Ln-1
            goto Ln
        next:
        ```

##### Function Call

- 函数调用文法
    $S \to call\; id\;(Elist)$
    $Elist \to Elist, E$
    $Elist \to E$
- 语法制导翻译方案
    - 中间代码结构
        ```txt
        E1
        E2
        ...
        En
        param E1.place
        param E2.place
        ...
        param En.place
        call id.place n
        ```
    - 具体实现
        - $Elist \to E$
            ```C
            {
                Elist.paramlist = createEmptyList();
                Elist.paramlist.push_back(E.place);
            }
            ```
        - $Elist \to Elist1, E$
            ```C
            {
                Elist.paramlist = Elist1.paramlist;
                Elist.paramlist.push_back(E.place);
            }
            ```
        - $S \to call\; id\;(Elist)$
            ```C
            {
                for E in Elist.paramlist
                    gen('param', E.place);
                gen('call', id.place, Elist.paramlist.size());
            }
            ```

#### Control Flow

- 控制流语句的文法
    - $S \to if\; B\; then\; S1$
    - $S \to if\; B\; then\; S1\; else\; S2$
    - $S \to while\; B\; do\; S1$
    - $S \to S1;\; S2$

- `S -> if B then S1`
    - 语义规则:
        ```C
        B.true = newLabel();    // 标号指向 S 内部的三地址码时需要调用 newLabel()
        B.false = S.next;   // 指向 S 外部的三地址码时需要从 S 继承
        S1.next = S.next;
        S.code = B.code || gen(B.true, ":") || S1.code  
        // 将 B.true 标签附加到 S1 的第一条三地址指令上
        // S1 后面不需要加跳转, 顺序执行即是跳转
        // 这里的 || 意思是连接
        ```
- `S -> if B then S1 else S2`
    - 语义规则
        ```C
        B.true = newLabel();
        B.false = newLabel();
        S1.next = S.next;
        S2.next = S.next;
        S.code = B.code || gen(B.true, ":") || S1.code || gen('goto', S.next) 
                        || gen(B.false, ":")|| S2.code
        ```
- `S -> while B do S1`
    - 语义规则
        ```C
        S.begin = newLabel();
        B.true = newLabel();
        B.false = S.next;
        S1.next = S.begin;
        S.code = gen(S.begin, ":") || B.code || gen(B.true, ":") 
                    || S1.code || gen("goto", S.begin)
        ```
- `S -> S1; S2`
    - 语义规则
        ```C
        S1.next = newLabel();
        S2.next = S.next;
        S.code = S1.code || gen(S1.next, ":") || S2.code
        ```

#### Boolean Expression

- 在前面的翻译中, 并未对 B.code 进行展开, 现在考虑 B.code 的三地址码翻译
- 布尔表达式的两个基本目的:
    1. 在控制流语句中作为条件表达式(eg: `if(B) then S1`)
    2. 计算逻辑值(eg: `x = y > 0`)
- 本节考虑的布尔表达式文法
    - `B -> B or B | B and B | not B | (B) | E relop E | true | false`
    - 布尔运算符: or, and, not(其中优先级 `not > and > or`)
    - 关系运算符 relop: $<, \leq, =, \neq, \geq, >$
    - 布尔常量: true, false
- 布尔表达式的完全计算
    - 将整个表达式所有值全部算出
- 布尔表达式的"短路"计算(更快)
    - `B1 or B2` B1 为真即为真
    - `B1 and B2` B1 为假即为假

##### Translation

- `B -> B1 or B2`
    ```C
    B1.true = B.true;
    B1.false = newLabel();
    B2.true = B.true;
    B2.false = B.false;
    B.code = B1.code || gen(B1.false, ":") || B2.code
    ```
- `B -> B1 and B2`
    ```C
    B1.true = newLabel();
    B1.false = B.false;
    B2.true = B.true;
    B2.false = B.false;
    B.code = B1.code || gen(B1.true, ":") || B2.code
    ```
- `B -> E1 relop E2`
    ```C
    B.code = E1.code || E2.code 
    || gen("if", E1.place, relop.op, E2.place, "goto", B.true) 
    || gen("goto", B.false)
    ```
- `B -> (B1)`
    ```C
    B1.true = B.true
    B1.false = B.false
    B.code = B1.code
    ```
- `B -> not B1`
    ```C
    B1.true = B.false
    B1.false = B.true
    B.code = B1.code
    ```
- `B -> true`
    ```C
    B.code = gen("goto", B.true)
    ```
- `B -> false`
    ```C
    B.code = gen("goto", B.false)
    ```

##### Summary

- 上述翻译过程中, 有一个关键问题, 即如何匹配跳转指令与跳转目标
- B.true, B.false 均为继承属性
- 上述过程需要两趟分析来计算
    1. 生成语法树
    2. 深度优先遍历树, 计算属性值, 将标号和具体地址绑定起来
- 为了一遍完成上述过程, 我们引入了标号回填技术

#### Backpatching

- 问题: 在布尔表达式短路计算翻译中, 产生了转移目标不明确的跳转指令
- 解决方案:
    - 当生成跳转指令时, 暂时不指定目标地址
    - 当有关目标地址确定后, 在回填到翻译代码中
- 具体实现:
    - 将有相同转移目标的转移代码的标号用链表存储, 可以方便回填目标
    - 该 list 变成了综合属性, 可以与 LR 结合
    - 数据结构及语义函数
        - 将生成的指令放入一个指令数组, 数组下标即为指令的标号
        - makelist(i)
            - 创建含标号为 i 的指令的链表
            - i 不是目标指令, 而是源指令(即不完整的 goto 指令)
        - backpatch(instruction-list, target-label)
            - 将目标地址 target-label 填回 instruction-list 中每条指令
        - merge(instruction-list1, instruction-list2)
            - 合并 list1 和 list2, 两个链中指令都会跳转到同一目标
    - 综合属性
        - 对布尔表达式而言, 有两个综合属性. 在生成代码时, 一些语句的 goto 是不完整的(因为跳转目标在布尔表达式之外), 需要用 truelist, falselist 来管理
            1. B.truelist: 代码中所有转向真出口的代码指令链
            2. B.falselist: 代码中所有转向加出口的代码指令链
        - 对一般语句而言, 有一个综合属性
            1. S.nextlist: 代码中所有跳转到紧跟 S 的代码之后的指令
                eg: S -> {L}    // 程序块
                    S -> if B then S1 else S2

##### 基于标号回填的布尔表达式翻译

-   
    ```bison
    B -> not B1         { B.truelist = B1.falselist; 
                          B.falselist = B1.truelist;}
    ```
-   
    ```bison
    B -> (B1)           { B.truelist = B1.truelist;
                          B.falselist = B1.falselist;}
    ```
-   
    ```bison
    B -> true           { B.truelist = makelist(nextinstr);
                          gen("goto" -);}
    ```
-   
    ```
    B -> false          { B.falselist = makelist(nextisntr);
                          gen("goto" -);}
    ```    
-   
    ```
    B -> E1 relop E2    { B.truelist = makelist(nextinstr);
                          B.falselist = makelist(nextinstr + 1);
                          gen("if" E1.place relop.op E2.place "goto" -);
                          gen("goto" -)};
    ```
-   
    ```
    B -> B1 or M B2      { backpatch(B1.falselist, M.instr);
                           B.truelist = merge(B1.truelist, B2.truelist);
                           B.falselist = B2.falselist;}
    M -> \epsilon       { M.instr = nextinstr}
    ```
-   
    ```
    B -> B1 and M B2    { backpatch(B1.truelist, M.instr);
                          B.truelist = B2.truelist;
                          B.falselist = merge(B1.falselist, B2.falselist);}
    M -> \epsilon       { M.instr = nextinstr;}
    ```

##### 基于标号回填的控制流语句翻译

- 控制流语句文法汇总(用 S, L 分别表示一条语句和语句列表)
    ```
    S -> if B then S1
    S -> if B then S1 else S2
    S -> while B do S1
    S -> A
    S -> {L}    // {} 的作用是将内部多个语句绑定在一起, 当成一个语句
    L -> L; S | S   // 这不是左递归了吗? 是的, 但只有自顶向下处理不了左递归
    ```
- 
    ```
    S -> if B then M S1 
    {   backpatch(B.truelist, M.instr);
        S.nextlist = merge(B.falselist, S1.nextlist);
    }
    M -> \epsilon       {M.instr = nextinstr}
    ```
-
    ```
    S -> if B then M1 S1 N else M2 S2   
    {   backpatch(B.truelist, M1.instr);
        backpatch(B.falselist, M2.instr);
        // S1 结束后要越过 S2, 所以在 S1 后面插入无条件跳转语句
        temp = merge(S1.nextlist, N.nextlist);
        S.nextlist = merge(temp, S2.nextlist);
    
        
    }
    M1 -> \epsilon      {M1.instr = nextinstr}
    M2 -> \epsilon      {M2.instr = nextinstr}                
    N -> \epsilon       {N.nextlist = makelist(nextinstr);
                         gen("goto" -);
    }
    ```
-
    ```
    S -> while M1 B do M2 S1
    {   backpatch(B.truelist, M2.instr);
        backpatch(S1.nextlist, M1.instr);   // maybe S1.nextlist is empty
        S.nextlist = B.falselist;
        gen("goto" M1.instr);               // 无条件跳转语句
    }
    M1 -> \epsilon      {M1.instr = nextinstr}
    M2 -> \epsilon      {M2.instr = nextinstr}
    ```
*
    ```
    S -> A      {S.nextlist = {};}
    S -> {L}    {S.nextlist = L.nextlist}
    L -> S      {L.nextlist = S.nextlist}
    ```
*
    ```
    L -> L1; M S
    {   backpatch(L1.nextlist, M.instr);
        L.nextlist = S.nextlist;
    }
    M -> \epsilon       {M.instr = nextinstr}
    ```
- 举例, 具体过程见 `Lecture18-IR Translation-part4`
    ```C
    if (a < b or c < d and e < f) then
        while(a > c) do c = c + 1
    else d = d + 1
    e = e + d
    ```

#### Type Expression and Automatic Construction

##### 类型表达式

- 部分类型表达式文法(D 代表声明语句, S 代表一般语句)
    - `P -> D; S`
    - `D -> D; D | id: T`
    - `T -> boolean | integer | array [num] of T | *T | T '->' T`. 
        其中前两个为基本类型, 后面三个分别为数组, 指针, 函数; 属于复杂且可组合的类型
- 基本类型是类型表达式
    - `boolean, int, char, real, type_error, void`
        type_error 是出错类型, 在类型检查中传递错误
        void 无类型, 是语句的类型
- 可为类型表达式命名, 类名也是类型表达式
- 将类型构造算子(type constructor)作用于类型表达式可以构成新的类型表达式
    - 数组类型构造算子 array
        - 如果 T 是类型表达式, N 是一个整数, 则 array(N, T) 是类型表达式
    - 指针类型构造算子 pointer
        - 如果 T 是类型表达式, 则 pointer(T) 也是类型表达式
    - 笛卡尔乘积类型构造算子 $\times$
        - 如果 T1 和 T2 是类型表达式, 则 $T1 \times T2$ 也是类型表达式
        - 主要用于描述列表和元组, 如函数的参数
    - 函数类型构造算子 ->
        - 若 T1, T2, ..., Tn 和 R 是类型表达式, 则 $T1 \times T2 \times \ldots \times Tn \to R$ 也是
    - 记录类型构造算子 record   (类似 C 中的结构体)
        - 若有标识符 N1, N2, ..., Nn 以及对应的类型表达式 T1, T2, ..., Tn, 则 $record((N1\times T1)\times (N2\times T2) \times \ldots \times (Nn\times Tn))$ 也是类型表达式

##### 类型表达式的语法制导定义 SDD

- 为以下文法指定构造类型表达式的语义规则
- 为每个语法符号设置综合属性 t 和继承属性 b
    - t: 该符号对应的类型表达式
    - b: 将类型信息从左到右传递

    | 产生式 | 语义规则 |
    | :----- | :------- |
    | $T \to B C$ | $T.t = C.t,\ C.b = B.t$ |
    | $B \to int$ | $B.t = integer$ |
    | $B \to float$| $B.t = float$ |
    | $C \to [num] C1$| $C.t = array(num.val, C1.t);\ C1.b = C.b$ |
    | $C \to \epsilon$ | $C.t = C.b$ |

##### 类型表达式的语法制导翻译 SDT

- 先需要将 SDD 改为 SDT, 但继承属性的计算与 LR 分析方法不适配, 因此需要改造文法
    ```
    T -> B {C.b = B.t} C {T.t = C.t}
    B -> int {B.t = integer}
    B -> float {B.t = float}
    C -> [num] {C1.b = C.b} C1 {C.t = array(num.val, C1.t)}
    C -> \epsilon {C.t = C.b}
    ```
- 通过改造文法, 将中间翻译方案变为后缀翻译
    - 引入标记 M, C 规约时可以在栈顶以下位置找到 B.t
    - 引入标记 N, 把继承属性 C.b 当作综合属性记录
        ```
        T -> B M C {T.t = C.t}
        M -> \epsilon {M.t = B.t}       // M 每次出现时, B 必定在 M 下面一个位置
        B -> int {B.t = integer}
        B -> float {B.t = float}
        C -> [num] N C1 {C.t = array(num.val, C1.t)}
        N -> \epsilon {N.t = C.b}       // 归约时, 通过 val[top + 1] = val[top - 3] 得到 N.t
        C -> \epsilon {C.t = C.b}       // 归约时从前一个位置得到
        ```

#### Declaration Sentences

##### Symbol Table

- 符号表的使用和修改伴随编译的全过程
- 存储 entity 的各种信息
    - 如 variable names, function names, objects, classes, interfaces 等
    - 如类型信息, 所占用内存空间, 作用域等
- 用于编译过程中的分析与合成
    - 语义分析: 如使用前声明检查, 类型检查, 确定作用域等
    - 合成: 如类型表达式构造, 内存空间分配等

##### Declaration Sentences

- 翻译要点
    1. 不产生中间代码指令, 但要更新符号表
    2. 分配存储单元: 名字, 类型, 字宽, 偏移
        - 文法 G 的翻译如下
            ```
            P -> {offset = 0} D; S             // 初始化 offset
            D -> D; D
            D -> id : T    {enter(id.lexeme, T.type, offset);
                            offset = offset + T.width } // 更新符号表信息
            T -> integer   {T.type = integer; T.width = 4}
            T -> array [ number ] of  T1   {T.type = array(num.val, T1.type);
                                            T.width = num.val - T1.width}
            T -> pointer(T1)   {T.type = pointer(T1.type)
                                T.wdith = 4}    // 指针, int 宽度均为 4
            ```
    3. 作用域的管理: 过程调用
        - 所讨论语言的文法
            ```
            P -> D; S
            D -> D; D | id: T | proc id; D; S
            ```
        - 符号表
            - 每个过程内声明的符号要置于该过程的符号表中, 符号表通过哈希表实现
            - 符号表之间有双向链
                - 父->子: 过程中包含哪些子过程定义
                - 子->父: 分析完子过程后回到父过程
            - 维护符号表栈(tblptr)和地址偏移量栈(offset)
            - 语义动作用到的函数
                ```C
                // 建立新的符号表, 其表头指针指向父过程符号表
                mkTable(parent-table)  
                // 将所声明变量填入当前符号表 
                enter(current-table, name, type, current-offset)
                // 在父过程符号表中建立子过程名的条目
                enterProc(parent-table, sub-proc-name, sub-table)
                // 在符号表首部添加变量累加宽度, 可利用符号表栈和偏移栈
                addWidth(table, width)
                ```
            - 翻译过程如下
                ```C
                // 修改变量分配空间大小并清空符号表栈和偏移栈
                P -> M D; S            {addWidth(top(tblptr), top(offset));
                                        pop(tblptr); pop(offset)}
                // 建立主程序符号表, 偏移量从 0 开始 
                M -> \epsilon          {t = mkTable(NIL);
                                        push(t, tblptr);
                                        push(0, offset)}
                // 保留当前声明过程的子空间, 弹出符号表和偏移栈顶(露出父过程的符号表和偏移),
                // 在父过程符号表中填写子过程有关内容
                D -> proc id; N D1; S  {t = top(tblptr);
                                        addWidth(t, top(offset)); 
                                        pop(tblptr); pop(offset);
                                        enterProc(top(tblptr), id.lexeme, t)}
                // 建立子过程的符号表
                N -> \epsilon          {t = mkTable(top(tblptr));
                                        push(t, tblptr); push(0, offset)}
                // 将变量填入当前符号表
                D -> id :T {enter(top(tblptr), id.lexeme, T.type, top(offset));
                            top(offset) += T.width} 
                ```
    4. 记录类型(结构体)的管理
        - 文法
            `T -> record D end`
        - 翻译
            ```C
            T -> record L D end        {T.type = record(top(tblptr));
                                        T.width = top(offset);
                                        pop(tblptr); pop(offset)}
            L -> \epsilon              {t = mkTable(NIL);
                                        push(t, tblptr); push(0, offset)} 
            ```
        - 注意变量的偏移和对齐

#### Array-addressed Translation               

##### Array Type Declaration(It's so difficult!)

- e.g. Pascal 数组声明
    - A: array[low1..high1,...,lown..highn] of integer;
    - 数组元素: A[i, j, k,...] 或 A[i][j][k]...
- e.g. C 数组声明
    - int A[high1][high2][high3]...
    - 数组元素: A[i][j][k]...

##### Translation of Array Elements

- 翻译主要任务
    - 输出地址计算的指令
    - "基址[偏移]" 相关的中间指令: t=b[o], b[o]=t
- 数组元素的地址计算
    - 一维数组 A 第 i 个元素的地址计算
        - $base + (i-low)\times w$, 其中 base 为整个数组的基地址, 即分配给该数组
        的内存块的相对地址; low 为下标的下界, w 为每个元素的宽度
        - 可以变换为 $i\times w + (base - low\times w)$, 括号内部分是常量(也称
        为静态部分), 可以在编译时计算, 避免了重复计算.
    - 二维数组 A: array[1..2, 1..3] of T
        - 列为主: A[1,1], A[2,1], A[1,2], A[2,2], A[1,3], A[2,3]
            - 在特定场景下会更高效
        - 行为主: A[1,1], A[1,2], A[1,3], A[2,1], A[2,2], A[2,3]
            - 更为常见
            - $A[i_1][i_2]$ 的地址为 $base+((i_1 - low_1)\times n_2 + (i_2-low_2))\times w$, 可以变换为 $(i_1\times n_2 + i_2)\times w + (base-(low_1\times n_2+low_2)\times w)$
    - 多维数组下标变量 $A[i_1,i_2,...,i_k]$ 的地址表达式
        - $base+ ((((i_1-low_1)\times n_2 + (i_2-low_2))\times n_3)\dots+(i_k-low_k))\times n_k$
        - $((((i_1\times n_2 + i_2)\times n_3 + i_3)...)\times n_k + i_k)\times w + base - ((((low_1\times n_2 + low_2)\times n_3+low_3)...)\times n_k + low_k)\times w$
        - 可得动态部分的递推公式
            - $e_1 = i_1$
            - $e_m = e_{m-1} \times n_m + i_m$

##### Array Element Address Compustation Translation Scheme

- 下标变量访问的文法
    ```C
    S -> L := E
    L -> id [ Elist ] | id
    // 由 Elist 的结构只能得到各维的下标, 但无法获取数组的信息
    Elist -> Elist, E | E   
    E -> L 
    ```
- 当分析下标时, 需要用到 Elist 的子节点以获取各维信息, 但移进归约分析不适合计算继承属性. 故
    需要修改文法, 使数组名 id 成为 Elist 的子节点, 从而避免继承属性的出现
    ```C
    S -> L := E
    E -> E + E | (E) | L
    L -> Elist ] | id
    Elist -> Elist, E | id [ E
    ```
- 相关符号属性定义
    - `L.place,` `L.offset`
        - 若 L 为数组元素, L.place 为其地址的常量部分, L.offset 为地址的可变部分,
        数组元素表示为 L.place[L.offset]
        - 若 L 是简单变量, L.place 为其值, L.offset 为空
    - 属性信息
        - `Elist.place`: 存放地址中可变部分的值的地址
        - `Elist.array`: 数组名条目的指针, 可以用来查询 base
        - `Elist.ndim`: 当前处理的维数
    - 辅助函数
        - `limit(array, j)`: 第 j 维的大小
        - `width(array)`: 数组元素的宽度
        - `invariant(array)`: 静态可计算的值
    - 翻译过程如下
        ```C
        S -> L := E    {if L.offset == null // L 是简单变量
                            gen(L.place, '=', E.place)
                        else
                            gen(L.place, '[', L.offset, ']', '=', E.place)}
        Elist -> id [ E{Elist.place = E.place;
                        Elist.ndim = 1;
                        Elist.array = id.place}
        Elist -> Elist1, E {m = Elist1.ndim + 1;
                            n_m = limit(Elist1.array, m);
                            t = newTemp();
                            gen(t, '=', Elist1.place, '*', n_m);
                            gen(t, '=', t, '+', E.place);
                            Elist.array = Elist1.array;
                            Elist.place = t;
                            Elist.ndim = m}
        L -> Elist ]   {L.place = newTemp();
                        gen(L.place, '=', invariant(Elist.array));
                        L.offset = newTemp();
                        gen(L.offset, '=', width(Elist.array))}
        L -> id        {L.place = id.place; L.offset = null}
        E -> L         {if L.offset == null
                            E.place = L.place;
                        else
                            E.place = newTemp();
                            gen(E.place, '=', L.place, '[', L.offset, ']')}
        E -> E1, E2    {E.place = newTemp();
                        gen(E.place, '=', E1.place, '+', E2.place)}
        E -> (E1)      {E.place - E1.place}
        ```

## Runtime Environment

### Outline of Runtime Environment

- 运行时涉及的主要内容
    * 运行时存储空间组织管理概述
    * 活动树与栈式空间分配
    * 调用序列与返回序列
    * 非局部数据的访问
- 编译器为目标程序创建并管理一个运行时环境, 目标程序运行在该环境中.
    该环境提供以下功能
    * 对象存储位置和空间的分配
    * 访问变量的机制
    * 过程间的连接
    * 参数传递机制

### Storage Organization and Allocation

* 编译器必须为源程序中出现的一些数据对象分配运行时的存储空间
    * 静态存储分配
        * 对于在编译时就可以确定大小的数据对象, 可以在编译时就为他们分配空间, 这样的策略
        称为静态存储分配
    * 动态存储分配
        * 如果不能在编译时完全确定数据对象的大小, 就要采取动态存储分配的策略. 即在编译时
        仅产生必要的信息, 而在运行时再动态地分配存储空间
        * 栈式存储分配
            * 与过程调用有关, 涉及过程的局部变量以及过程活动记录
        * 堆式存储分配
            * 关系到部分生命周期较长的数据
    * 存储块是否必须被显式地释放
* 过程
    * 过程的调用与返回
    * 过程的执行需要: 代码段+活动记录(过程运行所需的额外信息, 如参数, 局部数据, 返回地址等)
    * 活动记录
        * 使用过程作为用户自定义动作的单元的语言, 其编译器通常以过程为单位分配存储空间
        * 过程的每次执行称为该过程的一个活动(activation)
        * 编译器为每一个活动分配一块连续存储区域, 用来管理此次执行所需的信息, 这片区域称为
        活动记录(activation record)
        * 活动记录的常见布局
            | 临时数据 | 保存表达式求值过程中产生的中间结果 |
            | :-----: | :----: | 
            | 局部数据 | |
            | 机器状态 | 本次过程调用前的机器状态, 如程序计数器的值 |
            | 访问链   | 用来访问存放于其他活动记录中的非局部数据, C 没有访问链 | 
            | 控制链   | 指向调用者的活动记录 | 
            | 返回值   | |
            | 参数     | |
* 局部存储分配
    * 基本概念
        * 作用域: 变量的作用范围        e.g. 局部变量与全局变量
        * 生存期: 变量从生成到撤销的这段时间
    * 环境和状态
        * 环境将名字映射到左值(即将 id 映射到该变量的存储位置)
        * 状态将左值映射到右值(即将变量从存储位置映射到值)
        * 赋值改变状态, 但不改变环境. 过程调用改变环境
        * 如果环境将名字 x 映射到存储单元 s, 则说 x 被绑定到 s
    * 静态概念与动态概念的对应
        |   静态概念   |   动态概念   |
        | :---------: | :--------: |
        | 过程的定义   | 过程的活动   |
        | 名字的声明   | 名字的绑定   |
        | 声明的作用域 | 绑定的生存期  |
    * 局部数据的布局
        * 字节是可编址内存的最小单位
        * 变量所需的存储空间可根据其类型而静态确定
        * 一个过程所声明的局部变量, 按这些变量声明时出现的次序, 在局部数据域中依次分配空间
        * 局部数据的地址可以用相对于活动记录中某个位置的地址来表示
        * 数据对象的存储布局还有对齐的问题
    * 程序块
        * 本身含有局部变量声明的语句
        * 可以嵌套
        * 并列程序块不会同时活跃
        * 并列程序块的变量可以重叠分配

### Stack Allocation of Space

* Outline
    * 对于支持过程的语言, 其编译器通常会用栈的形式来管理其运行时刻存储
    * 当一个过程被调用时, 该过程的活动记录被压入栈中; 当过程结束时, 记录被弹出
    * 这种安排不仅允许活跃时段不重叠的多个过程调用共享空间; 而且可以使得过程的非局部变量的
    相对地址总是固定的, 和调用序列无关

#### Activation Tree

* 活动树
    * 用来描述程序运行期间控制进入和离开各个活动的情况的树
    * 树中的每个节点对应一个活动; 根节点是 main 过程的活动
    * 对于过程 p, 其子节点对应于被 p 的这次活动调用的各个过程的活动. 按照调用次序, 自左向右地
    显示; 一个子节点必须在其右兄弟节点对应的活动开始之间结束
    * 当前活跃着的过程活动可以保存在一个栈中$\to$控制栈
        * 每个活跃的活动都有一个位于控制栈中的活动记录
        * 活动树的根节点的记录位于栈底
        * 程序控制所在的活动的记录位于栈顶
        * 栈中全部活动记录的序列对应在活动树中到达当前控制所在的活动节点的路径
* 运行栈
    * 把控制栈中的信息拓广到包括过程活动所需的所有局部信息(即活动记录, activation record)

#### Calling Sequence && Return Sequence

* 对运行栈的管理
    * 代码序列: 过程调用和过程返回都需要执行一些代码来管理运行栈
    * 过程调用序列: 过程调用时执行. 分配活动记录, 将信息填入它的域中, 使被调用过程开始执行
    * 过程返回序列: 被调用过程返回时执行. 恢复机器状态, 释放被调用过程活动记录, 使调用过程
    继续执行
    * 调用序列和返回序列都分成两部分, 分处于调用过程和被调用过程的活动记录中.
* 过程调用序列/返回序列和活动记录中各域的次序因实现而异, 但有一些基本原则
    * 调用者与被调用者之间交流的数据放在被调用者活动记录的开始处
        * 参数域紧邻调用者活动记录
        * 返回域在参数域之上
    * 固定长度的域放在活动记录的中间
        * 控制链, 访问链, 机器状态
    * 编译时不能确定大小的数据一般放在活动记录的末端
        * 局部动态数组, 临时数据
    * 以活动记录中间的某个位置(控制链)作为基地址
* 过程调用序列
    * 两个指针: 
        * `top_sp`, 栈顶寄存器, 指向栈顶活动记录的末端; 
        * `base_sp`, 基址寄存器, 指向栈顶活动记录中控制链所在位置
    * 过程 p 调用过程 q 的调用序列
        1. p 计算实参, 依次放入栈顶, 并在栈顶留出放返回值的空间(过程中 top_sp 改变)
        2. p 把返回地址和当前 base_sp 的值存入 q 的活动记录中, 建立 q 的控制链, 修改
        base_sp 的值
        3. q 保存寄存器的值和其他机器状态信息
        4. q 根据局部数据域和临时数据域的大小修改 top_sp 的值, 初始化局部数据并开始执行过程
    * 过程 p 调用过程 q 的返回序列
        1. q 把返回值放在指定位置
        2. q 对应调用序列的步骤 4, 修改 top_sp 的值
        3. q 恢复寄存器(包括 base_up)和机器状态, 返回 p
        4. p 根据参数个数与类型和返回值类型调整 top_sp, 然后取出返回值
    * 过程参数可变的情况
        1. 函数返回值用寄存器传递
        2. 编译器产生将实参表达式逆序计算并将结果入栈的代码
* 全局栈式存储分配
    * 栈上可变长数据
        * 数据对象的长度在编译时不能确定, 但仅为该活动使用, 放在栈上可以避免垃圾回收开销
    * 如何布局?
        * 先分配存放数组指针的单元, 对数组的访问通过指针间接实现
        * 运行时, 指针指向分配在栈顶的数组存储空间

### Access to Nonlocal Data on the Stack

#### Nested Procedures?

* 过程嵌套
    * 无过程嵌套的数据访问
        * 过程体中的非局部引用可直接使用静态确定的地址(非局部数据此时就是全局数据)
        * 局部变量在栈顶的活动记录中, 可以通过 base_sp 指针来访问
        * 无需深入栈中取数据, 无需访问链
    * 有过程嵌套的数据访问
        * 如 PASCAL 中, 可以在一个过程中声明另一个过程.
        * 如果过程 A 的声明中包含了过程 B 的声明, 那么 B 可以使用在 A 中声明的变量
        * 需要建立访问链使 B 能够找到 A 的活动记录

#### Data Access with Nested Procedures

* 过程嵌套
    * 例子
        ```
        sort
            readarray
            exchange
            quicksort
                partition   
        ```
    * 过程嵌套深度: 主程序为 1, 进入一个被包围的过程时加 1
    * 变量嵌套深度: 它的声明所在过程的嵌套深度作为改名字的嵌套深度
    * 过程嵌套的静态作用域在活动记录中增加访问指针形成访问链
        * 用来寻找非局部名字的存储单元
        * 假设 p 直接嵌套在 q 中, 那么 p 活动记录的访问链指针指向最靠近的 p 的活动记录
* 通过访问链访问非局部引用
    * 设过程 p 的嵌套深度为 $n_p$, 它引用嵌套深度为 $n_a$ 的变量  a
        * $n_a \leq n_p$
            * 从栈顶的活动记录开始, 追踪访问链 $n_p-n_a$ 此
            * 到达 a 的声明所在过程的活动记录
            * 访问链的追踪可用间接操作完成
* 访问链的建立
    * 设嵌套深度为 $n_x$ 的过程 x 调用嵌套深度为 $n_y$ 的过程 y
        * 若 $n_x < n_y$(外层调用内层)
            * y 肯定是在 x 中定义的, y 的访问链指向 x
        * 若 $n_x = n_y$(本层调用本层)
            * y 与 x 的访问链相同, 直接复制即可
        * 若 $n_x > n_y$(内层调用外层)
            * 过程 x 必定嵌套在某个过程 z 中, 而 z 中定义了 y
            * 从 x 的活动记录开始, 沿着访问链经过 $n_x - n_y + 1$ 步就可以找到离栈顶
            最近的 z 的活动记录, y 的访问链指向 z

## IR Optimization

***Outlines of Topics***

### 常见的优化方式

- 公共子表达式删除
    - 如 `x op y` 已计算过, 且到现在为止 `x, y` 的值均未变,
      则该表达式的本次出现时公共子表达式. 本次计算可以删除,
      其值用上一次的结果替代
- 死代码删除
    - 死代码指永远不会执行或计算的结果永远不被引用的语句. 复制传播,
      常量合并都可能引起死代码
- 复制传播
    - 在复制语句 `x = y` 之后尽可能用 `y` 代替 `x`, 这本身不会带来优化,
      但可能产生死代码
- 常量合并
    - 如果编译时推导出某表达式的值为常量, 则可以使用该常量代替这个表达式
- 循环系列优化
    - 强度削弱
        - 将循环中(循环外也可, 带来的优化会小一些)
          执行时间较长的运算替换为执行时间较短的运算
    - 删除归纳变量
        - 如果某个变量每次赋值都增加常量 c, 则该变量称为归纳变量.
          按照变化步调将归纳变量分组, 一组归纳变量只保留一个
    - 循环不变量外提
        - 略

### 到达定值分析

- $IN[B] = \cup_{predecessor} OUT[P]$
- $OUT[B] = gen_{B} \cup (IN[B] - kill_B)$
- Initialization: $OUT[B] = \emptyset$

### 可用表达式分析

- $IN[B] = \cap_{predecessor} OUT[P]$
- $OUT[B] = e\_gen_B \cup (IN[B] - e\_kill_B)$
- Initialization: $OUT[ENTRY] = \emptyset, OUT[B] = U$

### 活跃变量分析

- $IN[B] = use_B \cup (OUT[B] - def_B)$
- $OUT[B] = \cup_{successor} IN[S]$
- Initialization: $IN[B] = \emptyset$

### 基本块内的优化

- 利用 DAG 图表示基本块, 实现局部公共子表达式, 死代码的删除. 
    与基本块的重组

## 流图中的循环

## 易混辨析

### 各种树

1. 分析树(parse tree)
    - 利用文法产生式, 将开始符号展开成句子
2. 抽象语法树(abstract syntax tree)
    - 简称语法树, 将算符和关键字作为内部节点, 是分析树的浓缩表示,
    也是图形化的中间表示
3. 注释分析树(annotated parse tree)
    - 在分析树的基础上, 对每个结点上的属性进行求值得到的树
4. 深度优先排序
    - 先序遍历: 父节点 + 左子树 + 右子树(以自上而下的视角的左与右)
    - 后序遍历: 左子树 + 右子树 + 父节点
    - 深度优先排序: 父节点 + 右子树 + 左子树, 与后序遍历相反