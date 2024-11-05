#include<stdio.h>

#define N1 8
#define N2 7
#define N3 10
int list1[N1] = {2, 5, 3, 0, 2, 3, 0, 3};

// Over
// 遍历数组, 记录每个数出现的次数, 然后得到每个数应出现的最后位置
void Counting_Sort(int *A, int range){
    int B[N1], C[N1] = {0};
    for(int i = 0; i < N1; i++){
        C[A[i]] += 1;
    }
    for(int i = 1; i < range; i++){
        C[i] += C[i-1];
    }

    for(int i = N1 - 1; i >= 0; i--){
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
    for(int i = 0; i < N1; i++){
        A[i] = B[i];
    }
    return;
}

// int list2[N2] = {329, 457, 657, 839, 436, 720, 355};

// void Radix_Sort(int *A, int digit){
//     for(int i = 1; i <= digit; i++){
//         // use a stable sort(counting sort for example) to sort array A on digit i
//     }
// }


// int list3[N3] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

// void Bucket_Sort(int *A){

// }

void Print_Result(int *A, int N, char *list){
    printf("%s", list);
    for(int i = 0; i < N; i++){
        printf("%2d, ", A[i]);
    }
    printf("\n");
    return;
}

int main(){
    Print_Result(list1, N1, "The list before sorting:");
    Counting_Sort(list1, 6);
    Print_Result(list1, N1, "The list after sorting: ");
    return 0;
}