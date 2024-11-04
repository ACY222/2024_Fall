// 绩点 Over
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

#define N 10000

int64_t res;
// Merge list A, with length aLen, and B, with length bLen, into list C
void Merge(int *A, int aLen, int *B, int bLen, int *C){
    int i, j, k;
    for(i = 0, j = 0, k = 0; i < aLen &&  j < bLen; k++){
        if(B[j] < A[i]){        // for stability
            res += aLen - i;
            C[k] = B[j];
            j++;
        }
        else{
            C[k] = A[i];
            i++;
        }
    }

    // one of A and B is empty, merge another list into C
    for(; i < aLen; i++, k++){
        C[k] = A[i];
    }
    for(; j < bLen; j++, k++){
        C[k] = B[j];
    }
}

void Merge_Sort(int *A, int p, int r){
    if(p == r){
        return;
    }

    // divide
    int q = (p + r) / 2;
    Merge_Sort(A, p, q);
    Merge_Sort(A, q + 1, r);

    // merge
    int temp[N];
    Merge(A + p, q - p + 1, A + q + 1, r - q, temp + p);
    for(int i = p; i <= r; i++){
        A[i] = temp[i];
    }
    return;
}

int main(){
    // Method 5: Merge Sort
    int n, gpa[N] = {0};
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &gpa[i]);
    }
    Merge_Sort(gpa, 0, n - 1);
    // for(int i = 0; i < n; i++){
    //     printf("%d, ", gpa[i]);
    // }

    // Method 4
    // int n;
    // int64_t res = 0, gpa[N] = {0};
    // scanf("%d", &n);
    // for(int i = 0; i < n; i++){
    //     int j, k;
    //     scanf("%"SCNd64, &gpa[i]);
    //     if(gpa[i] >= gpa[i - 1]){   // LEQ the largest num in the sorted list
    //         continue;
    //     }
    //     else if(gpa[i] <= gpa[0]){   // LT the least num in the sorted list
    //         for(k = 0; gpa[k] == gpa[i]; k++){}
    //         res += i - k;
    //         Insertion(gpa, i, k);
    //     }
    //     else{
    //         for(j = i-1; gpa[i] < gpa[j]; j--){
    //             res++;
    //         }   // pos = j + 1
    //         Insertion(gpa, i, j+1);
    //     }
    // }


    // Method 3
    // int n;
    // int64_t res = 0, gpa[N] = {0}, v[N] = {0};
    // scanf("%d", &n);
    // for(int i = 0; i < n; i++){
    //     scanf("%"SCNd64, &gpa[i]);
    //     for(int j = i - 1; j >= 0; j--){
    //         if(gpa[i] == gpa[j]){
    //             v[i] += v[j];
    //             res += v[j];
    //             break;
    //         }
    //         if(gpa[i] < gpa[j]){
    //             v[i]++;
    //             res++;
    //         }
    //     }
    // }


    // Method 2
    // int n, p = 0;
    // int64_t res = 0, current_gpa, exist_gpa[N] = {0}, num_gpa[RANGE] = {0};
    // scanf("%d", &n);
    // for(int i = 0; i < n; i++){
    //     scanf("%"SCNd64, &current_gpa);
    //     if(num_gpa[current_gpa] == 0){
    //         exist_gpa[p] = current_gpa;
    //         p++;
    //     }
    //     num_gpa[current_gpa]++;
    //     for(int j = 0; j < p; j++){
    //         if(current_gpa < exist_gpa[j]){
    //             res += num_gpa[exist_gpa[j]];
    //         }
    //     }
    // }


    // Method 1
    // int n;
    // int64_t res = 0, gpa[N] = {0};
    // scanf("%d", &n);
    // for(int i = 0; i < n; i++){
    //     scanf("%"SCNd64, &gpa[i]);
    //     for(int j = 0; j < i; j++){
    //         if(gpa[i] < gpa[j]){
    //             res++;
    //         }
    //     }
    // }


    printf("%"PRId64"\n", res);
    return 0;
}