// 只有1和2的世界   Over
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define UPPER_BOUND 45

int main(){
    int N, res = 0, value[UPPER_BOUND] = {0, 1, 2, 3, 0};
    scanf("%d", &N);
    if(N < 1 || N > 45){
        printf("Invalid input\n");
        return 0;
    }
    if(N <= 3){
        res = value[N];
    }
    else{
        for(int i = 4; i <= N; i++){
            value[i] = value[i-1] + value[i-2];
        }
    }
    res = value[N];


    printf("%d\n", res);
    return 0;
}