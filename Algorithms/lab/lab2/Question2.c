// 女巫的糖果堆 Over
#include<stdio.h>

#define N 201
int score[N][N];
int pos[N][N];

void MIN_SCORE(int *num, int n){
    for(int r = 2; r <= n; r++){    // the number of candy piles
        for(int i = 1; i <= n - r + 1; i++){    // pile[i, i + r - 1]
            int sum = 0;
            for(int j = i; j <= i + r - 1; j++){
                sum += num[j];
            }
            int j = i + r - 1;
            score[i][j] = score[i][i] + score[i+1][j] + sum;
            pos[i][j] = i;
            for(int k = i + 1; k < j; k++){
                int temp = score[i][k] + score[k+1][j] + sum;
                if(score[i][j] > temp){
                    score[i][j] = temp;
                    pos[i][j] = k;
                }
            }
        }
    }
}


int main(){
    int n, num[N];
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &num[i]);
    }
    MIN_SCORE(num, n);
    printf("%d\n", score[1][n]);
    return 0;
}