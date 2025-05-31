// 小花的斐波那契数列
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define longint int64_t
#define DEBUG 1
#define MOD 1000000007

longint **Matrix_Multiply(longint **a, longint **b) {
    longint **c = (longint **)malloc(2 * sizeof(longint *));
    for(int i = 0; i < 2; i++) {
        c[i] = (longint *)malloc(2 * sizeof(longint));
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            c[i][j] = (a[i][0] * b[0][j] + a[i][1] * b[1][j]) % MOD;
        }
    }
    return c;
}

longint **Matrix_Initialize(longint a11, longint a12, longint a21, longint a22) {
    longint **matrix = (longint **)malloc(2 * sizeof(longint *));
    for(int i = 0; i < 2; i++) {
        matrix[i] = (longint *)malloc(2 * sizeof(longint));
    }
    matrix[0][0] = a11; matrix[0][1] = a12; matrix[1][0] = a21; matrix[1][1] = a22;
    return matrix;
}

longint Fibonacci(longint n) {
    longint **main = Matrix_Initialize(1, 1, 1, 0);
    longint **residual = Matrix_Initialize(1, 0, 0, 1);
    while(n > 0) {
        if(n % 2 == 1) {
            residual = Matrix_Multiply(residual, main);
        }
        main = Matrix_Multiply(main, main);
        n /= 2;
    }
    return residual[0][0];

}

int main() {
    longint n, res;
    scanf("%"SCNd64, &n);
    res = Fibonacci(n - 1);
    printf("%"PRId64"\n", res);
    return 0;
}