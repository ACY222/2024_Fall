// 女巫的项链 Over
#include<stdio.h>

#define N 10000
#define M 10000

int c[N][M];

int Length_LCS(char *S,int n, char* T, int m, int c[N][M]){   // length of longest ccommon sequence
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(S[i-1] == T[j-1]){
                c[i][j] = c[i-1][j-1] + 1;
            }
            else {
                if(c[i-1][j] >= c[i][j-1]){
                    c[i][j] = c[i-1][j];
                }
                else{
                    c[i][j] = c[i][j-1];
                }
            }
        }
    }
    return c[n][m];
}

void Print_C(int n, int m){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

int main(){
    char S[N], T[M];
    int n, m, max_length;
    scanf("%d %s", &n, S);
    scanf("%d %s", &m, T);
    // Print_C(n, m);
    max_length = Length_LCS(S, n, T, m, c);
    // Print_C(n, m);
    printf("%d\n", max_length);

}