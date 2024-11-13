# Outlines of Linear Algebra from MIT

[TOC]

本笔记只记录一些支离破碎的点, 较完整笔记可参考 [Linear Algebra](https://nbviewer.org/github/zlotus/notes-linear-algebra/blob/master/ReadMe.ipynb)

## Geometry of Linear Algebra

对于线性方程组, 有两种理解方式(以二元一次方程组为例)

### Row Picture

传统的理解方法, 每个方程都对应 x-y 平面中的一条直线, 直线的交点即为解.

### Column Picture

将线性方程组写成矩阵形式 $Ax=b$, b 和 A 的每个列向量都代表 $R^m$ 中的一个向量, $Ax$ 是
A 中列向量的线性组合, x 为系数. 该方程有解当且仅当 b 在 A 的列空间中

## Elimination with Matrices

`Gaussian Elimination`, 即高斯消元法, 将系数矩阵 A 通过行的线性组合(通常
是当前行减去前面的行)转为上三角矩阵 U, 然后回代(back substitution).

## Multiplication and Inverse Matrices

注意, 矩阵乘法满足交换律, 不满足结合律.

### Matrix multiplication

对于矩阵乘法 $A\cdot B = C$, 我们有下面五种理解方式

#### Multiply row by column

$$C_{ij} = \Sigma_{k=1}^nA_{ik}B_{kj}$$

#### Multiply matrix by column

$$A\cdot B = A \cdot [B_1 B_2 \cdots B_n] = [A \cdot B_1 \quad A \cdot B_2 \quad \cdots \quad A \cdot B_n]$$
Namely,$$C_{j} = A\cdot B_j$$

#### Multiply row by matrix

$$A\cdot B = 
\begin{bmatrix}
    A_1 \\ A_2 \\ \vdots \\ A_n
\end{bmatrix} \cdot B = 
\begin{bmatrix}
    A_1 \cdot B \\ A_2 \cdot B \\ \vdots \\ A_n \cdot B
\end{bmatrix}$$
Namely, $$C_i = A_i \cdot B$$

#### Multiply column by row

$$A\cdot B = 
\begin{bmatrix}
    A_1 A_2 \cdots A_n
\end{bmatrix} \cdot
\begin{bmatrix}
    B_1 \\ B2 \\ \vdots \\ B_n
\end{bmatrix} = 
\begin{bmatrix}
    A_1 \cdot B_1 + A_2 \cdot B_2 + \cdots + A_n \cdot B_n
\end{bmatrix}$$

#### Multiply by blocks

$$A\cdot B = 
\begin{bmatrix}
    A_1\ A_2 \\ A_3\ A_4
\end{bmatrix} \cdot
\begin{bmatrix}
    B_1\ B_2 \\ B_3\ B_4
\end{bmatrix} =
\begin{bmatrix*}
    A_1B_1 + A_2B_3 \ A_1B_2 + A_2B_4 \\
    A_3B_1 + A_4B_3 \ A_3B_2 + A_4B_4
\end{bmatrix*}$$

### Inverse

* 是否可逆是针对方阵的性质
* 判定方法
    1. 若 A 乘以任意非零向量能够得到零向量, 则矩阵 A 不可逆--对向量 x 做 A 对应
    的线性变换得到一个新的向量, 该向量无论如何也不能变回 x, 这是一个不可逆的过程
    2. $det(A) \neq 0$ 说明 A 是可逆的
    3. 若存在矩阵 B 使得 $A\cdot B = 0$ 或 $B\cdot A = 0$, 说明 A 是可逆的
    且 $B = A^{-1}$
* 求逆矩阵
    * 高斯-若尔当方法(Gauss-Jordan) 
    \[\begin{bmatrix}A\quad I  \end{bmatrix} \to \begin{bmatrix}I\quad A^{-1}\end{bmatrix}\]
        

## Factorization into $A=LU$

* $A=LU$ 是高斯消元法的另一种求解形式, 其中 L, U 分别代表 lower matrix, upper
    matrix. 通过 LU 分解, 求解线性方程组的时间复杂度为 $\Theta(n^2)$, 而高斯
    消元法为 $\Theta(n^3)$
* LU 分解的条件
    1. 主元不能为0(不能出现行变换)
    2. 矩阵是方阵
    3. 矩阵是可逆的
* LU 分解的过程(以三阶矩阵为例)
    1. 首先, 与高斯消元法类似, 得到 $E_{32}E_{31}E_{21}A = U$
    2. 故 $A = E_{21}^{-1}E_{31}^{-1}E_{32}^{-1}U = LU$
    其中 $ l_{ij} = -e_{ij}$, 通过逆矩阵实现了自底向上的操作, 从而消除了各矩阵
    之间的相互影响

## Transposes, Permutation, Spaces $R^n$

### Permutation Matrix

* 考虑到 LU 分解时主元未必总是0, 有时需要进行行变换, 这就引入了置换矩阵 P
* $P^{-1} = P^T$

### Transpose Matrix

* $A^T_{ij} = A_{ji}$

### Symmetric Matrix

* $A^T = A$
* 对任意矩阵 R, $R^TR$ 均为对称矩阵$$(R^TR)^T = R^T(R^T)^T=R^TR$$

## Vector Space

* 向量空间中任意向量的线性组合也要在该空间中, 即向量空间对加法和数乘是封闭的
    * 因此, 任意向量空间必须包含零向量

### Column Space and Nullspace

我们考虑 $Ax = b$

#### Column Space

* $A_{m\times n}$ 中的 m 说明讨论的向量空间为 $R^m$(A 的每个列向量大小都为 m)
* 由 A 的列向量生成的空间为 A 的列空间 C(A), 是 $R^m$ 的子空间. 一般用 pivot columns 的线性组合表示
* $Ax = b$ 有解当且仅当 b 属于 A 的列空间
* ***A 的列空间本质是 A 对应的线性映射的值域***

#### Nullspace

* A 的零空间 N(A) 是 $Ax = 0$ 中 x 的解组成的集合. 取自由变量为 I, 解出 pivot variable
的值, 即得到 null space 的基; 对一个线性映射 A, 使得输出为 0 的所有输入构成零空间.
* 任何与零空间"平行"的空间, 其线性变换的输出均为同一个向量

### Solving $Ax=0$, Pivot Variables, Special Solutions

1. 通过高斯消元法得到 U,找出主变量, 主变量个数即矩阵的秩(rank), 主变量所在的列为主列,
其余列为自由列. 自由列中的变量为自由变量, 自由变量的个数为 $n-r$
2. 将自由变元组成的矩阵取 I, 然后求主变量的值. 由此可以求得 $n-r$ 个特解, 特解的线性组合即为零
空间

还可以将 U 矩阵简化为 R 矩阵, 即简化行阶梯形(Reduced row echelon form). $$Ax=0\to Ux=0\to Rx=0$$

在简化行阶梯形中, 主元上下的元素均为 0, 且当某行不为 0 向量时, 该行第一个非零元素必须为 1. 对 R 进行列变换, 将主变量集中在左侧, 得到
$$R =
\begin{bmatrix*}
I\ F \\ 0\ 0
\end{bmatrix*}
$$
因为零空间矩阵 N 的列为 $Ax=0$ 的特解, 故 $R\cdot N = 0$, 即
$$R\cdot N =
\begin{bmatrix*}
    I\ F \\ 0\ 0
\end{bmatrix*}\cdot
\begin{bmatrix*}
    x_{pivot} \\ x_{free}
\end{bmatrix*}=
\begin{bmatrix*}
    x_{pivot} + F\cdot x_{free} \\ 0
\end{bmatrix*} = 0$$
故$$x_{pivot} = -F\cdot x_{free}$$
若我们取$$x_{free} = I$$
则$$N =
\begin{bmatrix}
-F \\ I
\end{bmatrix}$$

### Solving $Ax=b$

* 对于$Ax=b$, 我们称 $[A\ b]$ 为增广矩阵.
* $Ax=b$ 有解当且仅当 b 在 A 的列空间中
* 求解步骤
    1. 将 A 化为 U 或 R
    2. 将所有自由变量设为 0, 求得 $x_{particular}$
    3. 求解 $Ax=0$ 得到通解 $x_{nullspace}$, 则 $x_p + x_n$ 即为 $Ax=b$
    的通解
* 不同情况下解的个数
    | $r = m = n$ | $r = n < m$ | $r < m < n$ | $r < m, r < n$ |
    | :---------: | :---------: | :---------: | :------------: |
    | $R = I$     | $R=\begin{bmatrix}I\\0\end{bmatrix}$ | $R = \begin{bmatrix}I\ F\end{bmatrix}$ | $R = \begin{bmatrix} I\ F \\ 0\ 0\end{bmatrix}$ |
    | 1 solution | 0 or 1 solution | $\infty$ solution | 0 or $\infty$ solution |

### Independence, Basis and Dimension

#### Independence

Suppose Vecotr $x_1, \ldots, x_n$ are columns of A, they're independent when
* No combinations give zero vector
* Null-space of A is the zero vector
* rank(A) = n

Each of these conditions can lead to the conclusion.

Vectors $v_1, \ldots, v_l$ span a space, means: the space consists of all combinations of these vectors.

#### Basis

* Basis for a space is  a sequence of vectors $v_1, \ldots, v_d$ with two
properties:
    1. they're independent
    2. they span the space
* As for $R^n$, n vectors give basis if the $n\times n$ matrix is invertible
* Given a space, every basis for the space has the same numberr of vectors, and
this number is the dimension of the space.

#### Dimension

* $rank(A) = \text{number of pivots} = dim(C(A))$
* $dim(N(A)) = \text{number of free variables} = n - r$

### Four Fundamental Subspaces

* ***Column Space $C(A) \in R^m, dim(C(A)) = r$***
    * Get rank and pivot columns by Gauss Elimination, and the columns in A corresponding to them are the
    basis of C(A)
* ***Null Space $N(A) \in R^n, dim(N(A)) = n - r$***
    * rank of N(A) is $n-r$, set the free variables as "Identity matrix", and the results are the basis
    of N(A)
* ***Row Space $C(A^T)\in R^n, dim(C(A^T)) = r$***
* ***Left Null Space $N(A^T) \in R^m, dim(N(A^T)) = m - r$*** 

## Matrix Spaces, Rank 1 Matrix and Small World Graph

### Matrix Spaces

* Suppose, M = all 3 by 3 matrices, S = all 3 by 3 symmetric matrices,
U = all 3 by 3 upper triangular matrices
* dim(M) = 9, dim(S) = 6, dim(U) = 6
* `intersection`: $S \cap U = diagonal\; matrices$, $dim(S\cap U) = 6$
* `sum`: $S + U = all\; 3\times 3's$, $dim(S+U)=9$
* $dim(S) + dim(U) = dim(S\cap U) + dim(S+U)$

### Rank 1 Matrix

* All rank 1 matrix $A = uv^T$, where both u and v are column vector
* rank 1 matrices are like building blocks that can build all matrices
    * eg: a $5\times 17$ ranked 4 matrix, can be built by 4 rank 1 matrices

### Small World Graphs

* Graph is composed of nodes and edges.

## Graphs and Networks

可参考 [图和网络](https://nbviewer.org/github/zlotus/notes-linear-algebra/blob/master/chapter12.ipynb)

## Orthogonal Vectors and Subspace

* vectors x and y are orthogonal if
    * $x^T\cdot y = 0$ or
    * $\left | x \right |^2 + \left | y \right |^2 = \left | x+y \right |^2$
* Subspace S is orthogonal to subspace T means
    * $\forall x \in S, \forall y \in T, x\bot y$
* $C(A) \bot N(A^T); C(A^T) \bot N(A)$
    * $Ax=0; A^Ty=0$
    * $N(A)$ and $C(A^T)$ are orthogonal complements(正交补) in $R^n$, because 
    $N(A)$ contains all vectors that are perpendicular to $C(A^T)$
    * 行空间和零空间将 $R^n$ 分割为两个正交的子空间, 同样的, 列空间和左零空间将 $R^m$
    分割为两个正交的子空间
* $A^TA$ 初探
    * 本章核心为 $A^TAx=A^Tb$, 该变换可用来将 "坏方程组" 变为 "好方程组"
    * $Ax=b$ 有解当且仅当 $b\in C(A)$, 然而, 有时候由于坏数据的存在, 该条件并不成立.
    此时我们可以通过该方式获得解
    * 结论
        * $N(A^TA) = N(A), rank(A^TA)=rank(A)$
        * 故 $A^TA$ 可逆的条件是 $rank(A)=n$


## Projections onto Subspaces

* 投影矩阵 $P=A(A^TA)^{-1}A^T$ 
    * 若向量 b 不在 A 的列空间上, $Ax=b$ 无解, 我们只能求出最接近的解
    * 通过 $p=Pb$ 可将向量 b 映射到 A 的列空间上, 从而求出最接近的解
    * $P^T=P$, $P^2=P$


## Projection Matrices and Least Squares

* 已知投影矩阵 $P=A(A^TA)^{-1}A^T$, Pb 会将向量投影在 A 的列空间中, 举两个特例
    * if $b\in C(A)$, then $Pb=b$
    * if $b\bot C(A)$, then $Pb=0$
* Least Squares(最小二乘法)

## Orthogonal Matrices and Gram-Schmidt

* 标准正交向量(orthonormal vectors)
    * \[q_i^Tq_j=\begin{cases} 0, \quad i\neq j\\1, \quad i=j\end{cases}\]
* 标准正交矩阵(orthonormal matrix)
    * $Q=\begin{bmatrix}q_1\;q_2\;\cdots\;q_n\end{bmatrix}$
    * $Q^TQ=I$
    * 当 Q 恰好是方阵时, Q 可逆, 由上式可知 $Q^T=Q^{-1}$
* Gram-Schmidt 正交化
    * 为什么要做正交化: 做投影时, 投影矩阵 $P=A(A^TA)^{-1}A^T$, 若 $A=Q$, 则
    $P=Q(Q^TQ)^{-1}Q^T=QQ^T$, 即, 当列向量为标准正交基时, $QQ^T$ 为投影矩阵,
    这能够极大的简化计算. 此时 $P^2=(QQ^T)^2=QQ^T=P$, 特别的, 若矩阵为标准正交方阵, 
    $QQ^T=I$
    * independent vectors a,b $\to$ orthogonal vectors A,B $\to$ orthonormal
    vectors $q_1, q_2$
        * $A=a, B=b-A\frac{A^Tb}{A^TA}$, 容易验证 $B\bot A$
        * $q_1 = \frac{A}{|A|}, q_2=\frac{B}{|B|}$
    * a, b, c $\to$ A, B, C $\to$ $q_1, q_2, q_3$
        * $A=a, B=b-A\frac{A^Tb}{A^TA}, C=c-A\frac{A^Tc}{A^TA}
        -B\frac{B^Tc}{B^TB}$
        * $q_1, q_2, q_3$ 略
    * 与用 $A=LU$ 描述消元法类似, 我们也用矩阵描述标准正交化 $A=QR$.
    设 $A=\begin{bmatrix} a_1 a_2 \end{bmatrix}$, 则标准正交化后有
    \[\begin{bmatrix} a_1 a_2 \end{bmatrix} = 
    \begin{bmatrix} q_1 q_2 \end{bmatrix}
    \begin{bmatrix} a_1^Tq_1 \; a_2^Tq_1 \\
                    a_1^Tq_2 \; a_2^Tq_2 \end{bmatrix}\]
    其中左下角的 $a_1^Tq_2$ 始终为零, 因为 Gram-Schmidt 正交化总是使后来构造的向量正交
    于先前的向量. 故 R 为上三角矩阵