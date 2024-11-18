# Outlines of Linear Algebra from MIT

[TOC]

本笔记只记录一些支离破碎的点, 较完整笔记可参考 [Linear Algebra](https://nbviewer.org/github/zlotus/notes-linear-algebra/blob/master/ReadMe.ipynb)

## Solving Linear Equations

### Geometry of Linear Algebra

There are two ways to understand a linear system of equations

#### Row Picture

Traditional way, each equation corresponds to a straight line in the x-y
plane, and the intersection of these lines is the solution(Supposing that
we are considering the 2 dimensional case)

#### Column Picture

Transform the equations into matrix form $Ax=b$, and each column of A is
a vector in $R^m$, and $Ax$ is the linear combinations of columns in A.
Therefore, there is a solution if and only if b is in the column space of A.
Namely, b can be described as the linear combinations of A's columns.

### Elimination with Matrices

`Gaussian Elimination`, 即高斯消元法, 将系数矩阵 A 通过行的线性组合(通常
是当前行减去前面的行)转为上三角矩阵 U, 然后回代(back substitution).

### Multiplication and Inverse Matrices

注意, 矩阵乘法满足结合律, 不满足交换律

#### Matrix multiplication

对于矩阵乘法 $A\cdot B = C$, 我们有下面五种理解方式

##### Multiply row by column

$$C_{ij} = \Sigma_{k=1}^nA_{ik}B_{kj}$$

##### Multiply matrix by column

$$A\cdot B = A \cdot [B_1 B_2 \cdots B_n] = [A \cdot B_1 \quad A \cdot B_2 \quad \cdots \quad A \cdot B_n]$$
Namely,$$C_{j} = A\cdot B_j$$

##### Multiply row by matrix

$$A\cdot B = 
\begin{bmatrix}
    A_1 \\ A_2 \\ \vdots \\ A_n
\end{bmatrix} \cdot B = 
\begin{bmatrix}
    A_1 \cdot B \\ A_2 \cdot B \\ \vdots \\ A_n \cdot B
\end{bmatrix}$$
Namely, $$C_i = A_i \cdot B$$

##### Multiply column by row

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

##### Multiply by blocks

$$A\cdot B = 
\begin{bmatrix}
    A_1\ A_2 \\ A_3\ A_4
\end{bmatrix} \cdot
\begin{bmatrix}
    B_1\ B_2 \\ B_3\ B_4
\end{bmatrix} =
\begin{bmatrix}
    A_1B_1 + A_2B_3 \ A_1B_2 + A_2B_4 \\
    A_3B_1 + A_4B_3 \ A_3B_2 + A_4B_4
\end{bmatrix}$$

#### Inverse

- 是否可逆是针对方阵的性质
- 判定方法
    1. 若 A 乘以任意非零向量能够得到零向量, 则矩阵 A 不可逆--对向量 x 做 A 对应
    的线性变换得到一个新的向量, 该向量无论如何也不能变回 x, 这是一个不可逆的过程
    2. $det(A) \neq 0$ 说明 A 是可逆的
    3. 若存在矩阵 B 使得 $A\cdot B = 0$ 或 $B\cdot A = 0$, 说明 A 是可逆的
    且 $B = A^{-1}$
- 求逆矩阵
    - 高斯-若尔当方法(Gauss-Jordan) 
    \[\begin{bmatrix}A\quad I  \end{bmatrix} \to \begin{bmatrix}I\quad A^{-1}\end{bmatrix}\]
        

### Factorization into $A=LU$

- $A=LU$ 是高斯消元法的另一种求解形式, 其中 L, U 分别代表 lower matrix, upper
    matrix. 通过 LU 分解, 求解线性方程组的时间复杂度为 $\Theta(n^2)$, 而高斯
    消元法为 $\Theta(n^3)$
- LU 分解的条件
    1. 主元不能为0(不能出现行变换)
    2. 矩阵是方阵
    3. 矩阵是可逆的
- LU 分解的过程(以三阶矩阵为例)
    1. 首先, 与高斯消元法类似, 得到 $E_{32}E_{31}E_{21}A = U$
    2. 故 $A = E_{21}^{-1}E_{31}^{-1}E_{32}^{-1}U = LU$
    其中 $ l_{ij} = -e_{ij}$, 通过逆矩阵实现了自底向上的操作, 从而消除了各矩阵
    之间的相互影响

### Transposes, Permutation

#### Permutation Matrix

- 考虑到 LU 分解时主元未必总是0, 有时需要进行行变换, 这就引入了置换矩阵 P(有时称为初等矩阵)
- $P^{-1} = P^T$

#### Transpose Matrix

- $A^T_{ij} = A_{ji}$
- Some properties
    - $(A^T)^T = A$
    - $(A+B)^T = A^T + B^T$
    - $(AB)^T = B^T A^T$

#### Symmetric Matrix

- $A^T = A$
- For any matrix R, $R^TR$ is always a symmetric matrix
$$(R^TR)^T = R^T(R^T)^T=R^TR$$

## Vector Spaces and Subspaces

### Vector Space

- 向量空间中任意向量的线性组合也要在该空间中, 即向量空间对加法和数乘是封闭的
    - 因此, 任意向量空间必须包含零向量

#### Column Space and Nullspace

我们考虑 $Ax = b$

##### Column Space

- $A_{m\times n}$ 中的 m 说明讨论的向量空间为 $R^m$(A 的每个列向量大小都为 m)
- 由 A 的列向量生成的空间为 A 的列空间 C(A), 是 $R^m$ 的子空间. 一般用 pivot columns 的线性组合表示
- $Ax = b$ 有解当且仅当 b 属于 A 的列空间
- ***A 的列空间本质是 A 对应的线性映射的值域***

##### Nullspace

- A 的零空间 N(A) 是 $Ax = 0$ 中 x 的解组成的集合. 取自由变量为 I, 解出 pivot variable
的值, 即得到 null space 的基; 对一个线性映射 A, 使得输出为 0 的所有输入构成零空间.
- 任何与零空间"平行"的空间, 其线性变换的输出均为同一个向量

#### Solving $Ax=0$, Pivot Variables, Special Solutions

1. 通过高斯消元法得到 U,找出主变量, 主变量个数即矩阵的秩(rank), 主变量所在的列为主列,
其余列为自由列. 自由列中的变量为自由变量, 自由变量的个数为 $n-r$
2. 将自由变元组成的矩阵取 I, 然后求主变量的值. 由此可以求得 $n-r$ 个特解, 特解的线性组合即为零空间

还可以将 U 矩阵简化为 R 矩阵, 即简化行阶梯形(Reduced row echelon form). $$Ax=0\to Ux=0\to Rx=0$$

在简化行阶梯形中, 主元上下的元素均为 0, 且当某行不为 0 向量时, 该行第一个非零元素必须为 1. 对 R 进行列变换, 将主变量集中在左侧, 得到
$$R =
\begin{bmatrix}
I\ F \\ 0\ 0
\end{bmatrix}
$$
因为零空间矩阵 N 的列为 $Ax=0$ 的特解, 故 $R\cdot N = 0$, 即
$$R\cdot N =
\begin{bmatrix}
    I\ F \\ 0\ 0
\end{bmatrix}\cdot
\begin{bmatrix}
    x_{pivot} \\ x_{free}
\end{bmatrix}=
\begin{bmatrix}
    x_{pivot} + F\cdot x_{free} \\ 0
\end{bmatrix} = 0$$
故$$x_{pivot} = -F\cdot x_{free}$$
若我们取$$x_{free} = I$$
则$$N =
\begin{bmatrix}
-F \\ I
\end{bmatrix}$$

#### Solving $Ax=b$

- 对于$Ax=b$, 我们称 $[A\ b]$ 为增广矩阵.
- $Ax=b$ 有解当且仅当 b 在 A 的列空间中
- 求解步骤
    1. 将 A 化为 U 或 R
    2. 将所有自由变量设为 0, 求得 $x_{particular}$
    3. 求解 $Ax=0$ 得到通解 $x_{nullspace}$, 则 $x_p + x_n$ 即为 $Ax=b$
    的通解
- 不同情况下解的个数
    | $r = m = n$ | $r = n < m$ | $r < m < n$ | $r < m, r < n$ |
    | :*********: | :*********: | :*********: | :************: |
    | $R = I$     | $R=\begin{bmatrix}I\\0\end{bmatrix}$ | $R = \begin{bmatrix}I\ F\end{bmatrix}$ | $R = \begin{bmatrix} I\ F \\ 0\ 0\end{bmatrix}$ |
    | 1 solution | 0 or 1 solution | $\infty$ solution | 0 or $\infty$ solution |

#### Independence, Basis and Dimension

##### Independence

Suppose Vecotr $x_1, \ldots, x_n$ are columns of A, they're independent when
- No combinations give zero vector
- Null-space of A is the zero vector
- rank(A) = n

Each of these conditions can lead to the conclusion.

Vectors $v_1, \ldots, v_l$ span a space, means: the space consists of all combinations of these vectors.

##### Basis

- Basis for a space is  a sequence of vectors $v_1, \ldots, v_d$ with two
properties:
    1. they're independent
    2. they span the space
- As for $R^n$, n vectors give basis if the $n\times n$ matrix is invertible
- Given a space, every basis for the space has the same numberr of vectors, and
this number is the dimension of the space.

##### Dimension

- $rank(A) = \text{number of pivots} = dim(C(A))$
- $dim(N(A)) = \text{number of free variables} = n - r$

#### Four Fundamental Subspaces

- ***Column Space $C(A) \in R^m, dim(C(A)) = r$***
    - Get rank and pivot columns by Gauss Elimination, and the columns in A corresponding to them are the
    basis of C(A)
- ***Null Space $N(A) \in R^n, dim(N(A)) = n - r$***
    - rank of N(A) is $n-r$, set the free variables as "Identity matrix", and the results are the basis
    of N(A)
- ***Row Space $C(A^T)\in R^n, dim(C(A^T)) = r$***
- ***Left Null Space $N(A^T) \in R^m, dim(N(A^T)) = m - r$*** 

### Matrix Spaces, Rank 1 Matrix and Small World Graph

#### Matrix Spaces

- Suppose, M = all 3 by 3 matrices, S = all 3 by 3 symmetric matrices,
U = all 3 by 3 upper triangular matrices
- dim(M) = 9, dim(S) = 6, dim(U) = 6
- `intersection`: $S \cap U = diagonal\; matrices$, $dim(S\cap U) = 6$
- `sum`: $S + U = all\; 3\times 3's$, $dim(S+U)=9$
- $dim(S) + dim(U) = dim(S\cap U) + dim(S+U)$

#### Rank 1 Matrix

- All rank 1 matrix $A = uv^T$, where both u and v are column vector
- rank 1 matrices are like building blocks that can build all matrices
    - eg: a $5\times 17$ ranked 4 matrix, can be built by 4 rank 1 matrices

#### Small World Graphs

- Graph is composed of nodes and edges.

### Graphs and Networks

可参考 [图和网络](https://nbviewer.org/github/zlotus/notes-linear-algebra/blob/master/chapter12.ipynb)

## Orthoganality

### Orthogonal Vectors and Subspace

- vectors x and y are orthogonal if they have following properties
    - $x^T\cdot y = 0$
    - $\left | x \right |^2 + \left | y \right |^2 = \left | x+y \right |^2$
- Subspace S is orthogonal to subspace T means
    - $\forall x \in S, \forall y \in T, x\bot y$
- $C(A) \bot N(A^T); C(A^T) \bot N(A)$
    - $Ax=0; A^Ty=0$
    - $N(A)$ and $C(A^T)$ are orthogonal complements(正交补) in $R^n$, because 
    $N(A)$ contains all vectors that are perpendicular to $C(A^T)$
    - Row space and Null space divide $R^n$ into two orthogonal subspace; To be
    the same, Column space and Left null space dive $R^m$ into two orthogonal
    subspace
- $A^TA$ 初探
    - 本章核心为 $A^TAx=A^Tb$, 该变换可用来将 "坏方程组" 变为 "好方程组"
    - $Ax=b$ 有解当且仅当 $b\in C(A)$, 然而, 有时候由于坏数据的存在, 该条件并不成立.
    此时我们可以通过该方式获得解
    - 结论
        - $N(A^TA) = N(A), rank(A^TA)=rank(A)$
        - Therefore, $A^TA$ is invertible if $rank(A) = n$

### Symmetric Matrices and Orthoganality

- Two properties:
    - The eigenvalues are real
    - The eigenvectors are perpendicular(can be chosen as)
- In usual case, $A = S\Lambda S^{-1}$
    - For symmetric matrices, $A = Q\Lambda Q^{-1}$, $Q$ consists of
    orthonormal vectors.
    - $A = Q\Lambda Q^{-1} = \begin{bmatrix} q_1 \; \cdots \; q_n \end{bmatrix}
    =\begin{bmatrix} \lambda_1 & 0 & \cdots & 0 \\
    0 & \lambda_2 & \cdots & 0\\
    \vdots & \vdots & \ddots & \vdots\\
    0 & 0 & \cdots & \lambda_n \end{bmatrix}
    \begin{bmatrix}q_1^T \\ q_2^T \\ \vdots \\ q_n^T\end{bmatrix} = 
    \lambda_1 q_1 q_1^T + \ldots + \lambda_n q_n q_n^T$
    - Every symmetric matrices is a combination of perpendicular projection
    matrices($P = A(A^TA)^{-1}A^T = qq^T$).
- For symmetric matrices, # positive pivots = # positive $\lambda$'s
- Positive definite symmetric matrix
    - All eigenvalues / pivots / subdeterminants are positive

### Projections onto Subspaces

- 投影矩阵 $P=A(A^TA)^{-1}A^T$ 
    - 若向量 b 不在 A 的列空间上, $Ax=b$ 无解, 我们只能求出最接近的解
    - 通过 $p=Pb$ 可将向量 b 映射到 A 的列空间上, 从而求出最接近的解
    - $P^T=P$, $P^2=P$


### Projection Matrices and Least Squares

- 已知投影矩阵 $P=A(A^TA)^{-1}A^T$, Pb 会将向量投影在 A 的列空间中, 举两个特例
    - if $b\in C(A)$, then $Pb=b$
    - if $b\bot C(A)$, then $Pb=0$
- Least Squares(最小二乘法)

### Orthogonal Matrices and Gram-Schmidt

- 标准正交向量(orthonormal vectors)
    - \[q_i^Tq_j=\begin{cases} 0, \quad i\neq j\\1, \quad i=j\end{cases}\]
- 标准正交矩阵(orthonormal matrix)
    - $Q=\begin{bmatrix}q_1\;q_2\;\cdots\;q_n\end{bmatrix}$
    - $Q^TQ=I$
    - 当 Q 恰好是方阵时, Q 可逆, 由上式可知 $Q^T=Q^{-1}$
- Gram-Schmidt 正交化
    - 为什么要做正交化: 做投影时, 投影矩阵 $P=A(A^TA)^{-1}A^T$, 若 $A=Q$, 则
    $P=Q(Q^TQ)^{-1}Q^T=QQ^T$, 即, 当列向量为标准正交基时, $QQ^T$ 为投影矩阵,
    这能够极大的简化计算. 此时 $P^2=(QQ^T)^2=QQ^T=P$, 特别的, 若矩阵为标准正交方阵, 
    $QQ^T=I$
    - independent vectors a,b $\to$ orthogonal vectors A,B $\to$ orthonormal
    vectors $q_1, q_2$
        - $A=a, B=b-A\frac{A^Tb}{A^TA}$, 容易验证 $B\bot A$
        - $q_1 = \frac{A}{|A|}, q_2=\frac{B}{|B|}$
    - a, b, c $\to$ A, B, C $\to$ $q_1, q_2, q_3$
        - $A=a, B=b-A\frac{A^Tb}{A^TA}, C=c-A\frac{A^Tc}{A^TA}
        -B\frac{B^Tc}{B^TB}$
        - $q_1, q_2, q_3$ 略
    - 与用 $A=LU$ 描述消元法类似, 我们也用矩阵描述标准正交化 $A=QR$.
    设 $A=\begin{bmatrix} a_1 a_2 \end{bmatrix}$, 则标准正交化后有
    \[\begin{bmatrix} a_1 a_2 \end{bmatrix} = 
    \begin{bmatrix} q_1 q_2 \end{bmatrix}
    \begin{bmatrix} a_1^Tq_1 \; a_2^Tq_1 \\
                    a_1^Tq_2 \; a_2^Tq_2 \end{bmatrix}\]
    其中左下角的 $a_1^Tq_2$ 始终为零, 因为 Gram-Schmidt 正交化总是使后来构造的向量正交
    于先前的向量. 故 R 为上三角矩阵

## Determinants

### Properties of Determinants

- $\det A = |A|$
- Properties:
    - $\det I = 1$
    - Exchange two Rows of A, then the sign of $\det A$ is flipped
    - Linearity about the rows
    - 如果两行相等, 则行列式为 0
    - take l$\times$Row i from Row k, determinant doesn't change
    - 如果方阵的某一行为 0, 则其行列式为 0
    - 有上三角矩阵$$U = \begin{bmatrix} d_1& *& \ldots& * \\
    0& d_2 & \ldots & * \\ \vdots & \vdots & \ddots & \vdots \\
    0& 0& \ldots& 1 \end{bmatrix}$$, 则 $\det U = d_1d_2\cdots d_n$
    - 当矩阵为奇异矩阵时, 其行列式为 0; 当且仅当矩阵可逆时, 行列式不为 0
    - $\det AB = \det A \det B$, therefore, $\det A^{-1} = \frac{1}{\det A}$.
    Similarly, $\det A^2 = (\det A)^2$, $\det kA = k^n \det A$. ***Pay
    Attention!***
    - $\det A^T = \det A$, Columns of matrix share the same properties with Rows
- Some tricks:
    - Laplace Theorem
        - $$\begin{vmatrix} A& * \\ O& B \end{vmatrix} = 
        \begin{vmatrix} A& 0 \\ *& B \end{vmatrix} = |A||B|$$
        - $$\begin{vmatrix} 0& A \\ B& * \end{vmatrix} = 
        \begin{vmatrix} *& A \\ B& 0 \end{vmatrix} = (-1)^{mn}|A||B|$$
- About rank
    - $rank(AB) \leq min\{rank(A), rank(B)\}$
    - $rank(AB) \geq rank(A) + rank(B) - n$
        - $AB = 0 \Rightarrow rank(A) + rank(B) \leq n$
    - $rank(A+B) \leq rank(A) + rank(B)$
    - $rank(\begin{bmatrix} A& 0\\ 0&B\end{bmatrix}) = rank(A) + rank(B)$



### Determinant Formulas and Cofactors

- BIG FORMULA
    - $\det A = \Sigma \pm a_{1\alpha} a_{2\beta} \cdots a_{n\omega},\quad 
    (\alpha, \beta, \ldots, \omega) = P_n$
- Cofactors(代数余子式)
    - Cofactors of $a_{ij} = C_{ij} = (-1)^{i+j}\det{M}$, M 为原矩阵删去第 i 行,
    第 j 列后得到的矩阵
    - $\det A = \Sigma_{j=1}^{n} a_{ij}C_{ij}$
- Adjugate Matrix
    - $A^* = C^T$ 称为伴随矩阵
    - Some properties
        - $AA^* = A^*A = |A| I$
        - $A^* = |A| A^{-1}$, $(A^*)^* = |A|^{n-2}A$
        - $|A^*| = |A|^{n-1}$
        - $rank(A^*) = \begin{cases} n, if\; rank(A) = n\\
        1, if\; rank(A) = n-1\\
        0, if\; rank(A) < n-1 \end{cases}$

### Cramer's Rule, Inverse Matrix and Volumes

- Inverse Matrix
    - $A^{-1} = \frac{1}{\det A} A^*$
- Cramer's Rule
    - 用来求解 $Ax=b$
        - $x = A^{-1}b = \frac{1}{\det A} A^* b$
        - $x_j = \frac{\det B_j}{\det A}$, 其中 $B_j = \begin{bmatrix} A_1
        \ldots A_{j-1} B_j A_{j+1} \ldots A_n\end{bmatrix}$
    - The cost of Cramer's Rule is very high
- Volume
    - The determinant of a $3\times 3$ matrix equals to the volume of the box
    constructed by $\hat i, \hat j, \hat k$, likewise, the det of a $2\times 2$
    matrix describes the area of a parallelogram constructed by $\hat i, \hat j$
    - This property provides us with a much more convenient way to get the area of
    a parallelogram or a volume of a box.

## Eigenvalues and Eigenvectors

### Introduction

- $Ax = \lambda x$
    - 进行 A 线性变换后仍与原向量平行的向量 x 称为特征向量, 系数 $\lambda$ 称为特征值
    - 如果 A 是奇异的, $\lambda = 0$ 是一个特征值
- 如何求解 $Ax = \lambda x$
    - $(A-\lambda I)x = 0$, $A-\lambda x$ 一定是奇异的(否则特征向量不存在)
    - 求解***特征方程*** $\det(A-\lambda I) = 0$, 得出特征值, 然后求零空间即可
    - 两个特性: $Trace(A) = \Sigma_{i=1}^{n} a_{ii} = \Sigma_{i=1}^{n} = 
    \lambda_i$, $\prod_{i=1}^{n} \lambda_i = \det A$

### Diagonalization and Power of A

For $Ax = \lambda x$, we introduce `eigenvalues` and `eigenvectors`.
The first is to find them, we do it by solving `characteristic equation`.
And then is to use them, we will talk about it in this lecture.

- Suppose that A has n independent eigenvectors, take them as columns of S
    - $AS = A \begin{bmatrix} x_1& x_2& \cdots x_n \end{bmatrix} =
    \begin{bmatrix} \lambda_1 x_1& \lambda_2 x_2& \cdots \lambda_n x_n
    \end{bmatrix} = \begin{bmatrix} x_1 \cdots x_n \end{bmatrix}
    \begin{bmatrix} \lambda_1 & 0 &\cdots & 0\\
    0& \lambda_2& \cdots& 0\\
    \vdots& \vdots& \ddots& \vdots\\
    0& 0& \cdots& \lambda_n \end{bmatrix} = S\Lambda$
    - $A = S\Lambda S^{-1}$, $A^n = S\Lambda^n S^{-1}$. 即对于矩阵的幂运算,
    其特征向量不变, 特征值做同样的幂运算.
    - 若 A 的特征值各不相同, 则 A 一定有 n 个独立的特征向量, A 可以被对角化; 若 A
    有重复的特征值, 可能有 n 个独立的特征向量
- 利用上面的结论, 可以更方便地处理 $A^n$ 的问题

### Differential Equations and exp(At)

#### Differential Equations $\frac{\rm du}{\rm dt} = Au$

- $\frac{\rm du}{\rm dt} = Au$ 的通解为 $$u(t) = c_1 e^{\lambda_1 t} x_1 + 
c_2 e^{\lambda_2 t} x_2$$
- steady state: $\lambda_i = 0$ and other $\lambda \;s.t. Re(\lambda) < 0 $,
then $x_i$ is a steady state, which means $$\lim_{t\to \infty} u(t) = x_i$$
- $u_k$ blows up if any $Re(\lambda) > 0$
- set $u = Sv, S = [eigenvectors]$, then $S\frac{\rm dv}{\rm dt} = ASv$,
$\frac{\rm dv}{\rm dt} = S^{-1}ASv = \Lambda v$, 其解为 
$v(t) = e^{\Lambda t}v(0)$, 此时 $u(t) = Se^{\Lambda t} S^{-1} v(0) 
= e^{At}u(0)$

#### Matrix Exponential

$$e^{At} = I + At + \ldots + \frac{(At)^n}{n!} + \ldots =
SS^{-1} + S\Lambda S^{-1}t + \ldots + \frac{S\Lambda^{n}S^{-1}t^n}{n!} +\ldots
= Se^{\Lambda t} S^{-1}$$
而
$$e^{\Lambda t} = \begin{bmatrix} e^{\lambda_1 t}& 0& \ldots& 0\\
0& e^{\lambda_2 t}& \ldots& 0\\
\vdots& \vdots& \ddots& \vdots\\
0& 0& \ldots & e^{\lambda_n t} \end{bmatrix}$$

## Application

### Markov Matrix, Fourier Series

#### Markov Matrix

- two properties
    - all entries $\geq 0$
    - all columns add to 1
- two corollary
    - $\lambda = 1$ is an eigenvalue, and the eigenvector corresponding to it
    is a steady state
    - all other $|\lambda_i| < 1$
- $u_k = A^k u_0 = S\Lambda^k S^{-1}Sc = S\Lambda^kc = c_1\lambda_1^k x_1 + 
c_2\lambda_2^k x_2 + \ldots + c_n\lambda_n^k x_n$

#### Fourier Series

- $f(x) = a_0 + a_1 \cos x + b_1 \sin x + a_2 \cos 2x + b_2 \sin 2x + \ldots$
    - for vectors, $v^Tw = v_1 w_1 + \ldots v_n w_n$
    - for functions, $f^Tg = \int f(x)g(x) \rm dx$
    - $a_i = \int_0^{2\pi} f(x)\cos ix \rm dx$
    - $b_i = \int_0^{2\pi} f(x)\sin ix \rm dx$
