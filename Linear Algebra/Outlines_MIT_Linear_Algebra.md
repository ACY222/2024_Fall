# Outlines of Linear Algebra from MIT

[TOC]

## Geometry of Linear Algebra

对于线性方程组, 有两种理解方式(以二元一次方程组为例)

### Row Picture

传统的理解方法, 每个方程都对应 x-y 平面中的一条直线, 直线的交点即为解.

### Column Picture

将线性方程组写成矩阵形式 $Ax=b$, $Ax$ 是 A 中列向量的线性组合.

## Elimination with Matrices

Gaussian Elimination, 即高斯消元法, 将系数矩阵 A 通过行的线性组合(通常
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

## Factorization into $A=LU$

* $A=LU$ 是高斯消元法的另一种求解形式, 其中 L, U 分别代表 lower matrix, upper
    matrix. 但通过 LU 分解, 求解线性方程组的时间复杂度为 $\Theta(n^2)$, 而高斯
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

$A^T_{ij} = A_{ji}$

### Symmetric Matrix

* $A^T = A$
* 对任意矩阵 R, $R^TR$ 均为对称矩阵$$(R^TR)^T = R^T(R^T)^T=R^TR$$

## Vector Space

* 向量空间中任意向量的线性组合也要在该空间中, 即向量空间对加法和数乘是封闭的
    * 因此, 任意向量空间必须包含零向量

### Column Space and Nullspace

我们考虑 $Ax = b$

#### Column Space

* $A_{m\times n}$ 中的 m 说明讨论的向量空间为 $R^n$
* 由 A 的列向量生成的空间为 A 的列空间 C(A), 是 $R^n$ 的子空间
* $Ax = b$ 有解当且仅当 b 属于 A 的列空间
* ***A 的列空间本质是 A 对应的线性映射的值域***

#### Nullspace

* A 的零空间 N(A) 是 $Ax = 0$ 中 x 的解组成的集合. 即对一个线性映射 A,
  使得输出为 0 的所有输入构成零空间.
* 任何与零空间"平行"的空间, 其线性变换的输出均为同一个向量

### Solving $Ax=0$, Pivot Variables, Special Solutions

1. 通过高斯消元法得到 U,找出主变量, 主变量个数即矩阵的秩(rank), 主变量所在的列为主列, 其余列为自由列.
自由列中的变量为自由变量, 自由变量的个数为 $n-r$
2. 对自由变量赋值, 然后求主变量的值. 由此可以求得 $n-r$ 个特解, 特解的线性组合
即为零空间

还可以将 U 矩阵简化为 R 矩阵, 即简化行阶梯形(Reduced row echelon form). $$Ax=0\to Ux=0\to Rx=0$$

在简化行阶梯形中, 主元上下的元素均为 0, 对 R 进行列变换, 将主变量集中在左侧, 得到
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
