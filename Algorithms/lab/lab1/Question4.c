// 女巫的魔药瓶 Over
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

#define UPPER 1000000

void swap(int64_t *x, int64_t *y){
    int64_t temp;
    temp = *y;
    *y = *x;
    *x = temp;
}

// the folling two functions are used to find the i-th largest number
int Randomized_Partition(int64_t *A, int p, int r){
    int64_t pivot = A[r];
    int i = p;
    for(int j = p; j < r; j++){
        if(A[j] <= pivot){
            swap(&A[i], &A[j]);
            i++;
        }
    }
    swap(&A[i], &A[r]);
    return i;
}

int64_t Randomized_Selection(int64_t *A, int p, int r, int i){
    int q, k;
    if(p == r){
        return A[p];
    }
    q = Randomized_Partition(A, p, r);
    k = r - q + 1;
    if(i == k){
        return A[q];
    }
    else if(i < k){
        return Randomized_Selection(A, q+1, r, i);
    }
    else{           // i > k
        return Randomized_Selection(A, p, q-1, i-k);
    }
}

int main(){
    int64_t content[UPPER] = {0}, sum = 0, value, res;
    int N, num;
    scanf("%d", &N);
    num = (N + 1) / 2;
    for(int i = 0; i < N; i++){
        scanf("%"SCNd64, &content[i]);
        sum += content[i];
    }
    value = Randomized_Selection(content, 0, N - 1, num);
    // printf("%"PRId64"\n", value);

    if(num == 1){   // when N == 1 || N == 2
        res = -1;
    }
    else{
        res = value * N * 2 - sum + 1;
    }

    if(res < 0){
        printf("-1\n");
    }
    else{
        printf("%"PRId64"\n", res);
    }
    return 0;
}