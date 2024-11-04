#include<stdio.h>

#define N 8
#define M 13

float EXCEPTION(int *list){
    int i, j, sum = 0;
    float res;
    for(j = 0; j < N; j++){
        for(i = 1; i < list[j]; i++){
            sum += j + 1 + i;
        }
    }
    res = (float)sum / 128;
    return res;
}

int main(){
    int list1[N] = {64, 32, 16, 8, 4, 2, 1, 1}, list2[M] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 2};
    float res1, res2;
    // for(int i = 0; i < N; i++){
    //     sum1 = sum1 + (list[i] - 1) * (list[i] + 2 * i + 2);
    // }
    // res1 = (float)sum1 / 256;
    // for(int j = 0; j < N; j++){
    //     for(int i = 1; i < list[j]; i++){
    //         sum2 += j + 1 + i;
    //     }
    // }
    res1 = EXCEPTION(list1);
    res2 = EXCEPTION(list2);
    printf("%f, %f", res1, res2);
    return 0;

}