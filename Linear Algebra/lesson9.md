# Independence, Basis and Dimension

## Linear Independence

Suppose A is m by n, with m < n. Then Ax = 0 has non-zero solution.

Reason: there are free variables, so I can assign them to be non-zero values,
and then get the pivot values.

Vectors x1, x2, ..., xn are ***independent*** if no combinations give zero
vector (except the zero combination, namely all the coefficient are 0)

Obviously, if one of them can be represented by other vectors, they must be
dependent.

Repeat when v1, v2, ..., vn are columns of A. They are independent if nullspace
of A is the zero vector, and we also know that rank(A) = n. They are dependent
if Ax=0 for some non-zero vectors, while rank(A) < n.


Vectors v1, ..., vl span a space, means: the space consists of all combinations
of those vectors.

## Basis

Basis for a space is a sequence of vectors v1, v2, ..., vd, with two properties:
1. they're independent
2. they span the space

Example: Space in $R^3$, one basis is $[1,0,0]^T, [0,1,0]^T, [0,0,1]^T$. 
Another basis $[1,1,2]^T, [2,2,5]^T, [3,3,8]^T$

As for $R^n$, n vectors give basis if the $n\times n$ matrix is invertible

Given a space, every basis for the space has the same number of vectors. And
this number is the dimension of the space.

## Dimension

rank(A) = number of pivots ***or*** dimension of C(A), ***Attention, not
the dimension of A***

dim(N(A)) = number of free variables = n - r