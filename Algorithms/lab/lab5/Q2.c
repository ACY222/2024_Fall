// 小花的字串
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

int N, M;   // N, M are the length of Main String S and Pattern String T

void Print_String(char *str, char *state) {
    if(DEBUG) {
        printf("%s:\n%s\n", state, &str[1]);
    }
    return;
}

void Input(char **S, char **T) {
    scanf("%d %d", &N, &M);
    *S = (char *)malloc(sizeof(char) * (N + 2));
    *T = (char *)malloc(sizeof(char) * (M + 2));
    scanf("%s %s", *S + 1, *T + 1);

    Print_String(*S, "Main String");
    Print_String(*T, "Pattern String");
}

int *Compute_Prefix_Function(char *T) {
    int *pi = (int *)malloc(sizeof(int) * (M + 1));
    pi[1] = 0;
    int k = 0;
    for(int i = 2; i <= M; i++) {
        while(k > 0 && T[k + 1] != T[i]) {  // 匹配失败, 尝试更短的段
            k = pi[k];
        }
        if(T[k + 1] == T[i]) {      // 匹配一个字符
            k++;
        }
        pi[i] = k;
    }
    if(DEBUG) {
        printf("Prefix Function pi:");
        for(int i = 1; i <= M; i++) {
            printf("%d, ", pi[i]);
        }
        printf("\n");
    }
    return pi;
}

int *Initialize_Match_Pos() {
    int *match_pos = (int *)malloc(sizeof(int) * (N - M + 2));
    for(int i = 0; i <= N - M + 1; i++) {
        match_pos[i] = 0;
    }
    return match_pos;
}

int *KMP_Match(char *S, char *T) {
    int *pi = Compute_Prefix_Function(T), q = 0;// number of characters matched
    int *match_pos = Initialize_Match_Pos();
    for(int i = 1; i <= N; i++) {    // i is a pointer to S
        while(q > 0 && T[q + 1] != S[i]) {  // 匹配失败, 尝试更短的段
            q = pi[q];
        }
        if(T[q + 1] == S[i]) {      // 匹配一个字符
            q++;
        }
        if(q == M) {
            match_pos[0]++;
            match_pos[match_pos[0]] = i - M;
            q = pi[q];
        }
    }
    return match_pos;
}

void Output(char *S, char *T) {
    int *match_pos = KMP_Match(S, T);
    printf("%d\n", match_pos[0]);
    for(int i = 1; i <= match_pos[0]; i++) {
        printf("%d ", match_pos[i]);
    }
    printf("\n");
    return;
}

int main() {
    char *S, *T;
    Input(&S, &T);
    Output(S, T);
    return 0;
}