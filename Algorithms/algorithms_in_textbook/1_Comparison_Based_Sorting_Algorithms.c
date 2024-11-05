#include<stdio.h>
#include<stdbool.h>

#define N 10
int list[N] = {3, 7, 2, 9, 15, 11, 6, 22, 4, 8};

void SWAP(int *A, int i, int j){
    if(i == j){
        return;
    }
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
    return;
}

void Print_Result(int *A){
    for(int i = 0; i < N; i++){
        printf("%2d, ", A[i]);
    }
    printf("\n");
    return;
}

// Over
// 向有序数组中插入元素
void Insertion_Sort(int *A){
    for(int i = 1; i < N; i++){
        int current_num = A[i];
        for(int j = 0; j < i; j++){
            int k = i;
            if(current_num < A[j]){
                for(; k > j; k--){
                    A[k] = A[k-1];
                }
                A[k] = current_num;
                break;              // 插入后要立刻看后面的一个数, 即需要跳出 j 所在循环
            }
        }
    }
    return;
}

// Over
// 依次选择当前最小的元素放到前面
void Selection_Sort(int *A){
    for(int i = 0; i < N; i++){
        int min_sub = i;
        for(int j = i + 1; j < N; j++){
            if(A[min_sub] > A[j]){
                min_sub = j;
            }
        }
        SWAP(A, i, min_sub);
    }
}

// Over
// 通过一次次移动将最小的移到最前面
void Bubble_Sort_New(int *A){
    bool noswap = true;
    for(int i = 0; i < N; i++){
        noswap = true;
        for(int j = N - 1; j > i; j--){
            if(A[j] < A[j-1]){
                SWAP(A, j, j-1);
                noswap = false;
            }
        }
        if(noswap){
            return;
        }
    }
}

void Bubble_Sort(int *A){
    for(int i = 0; i < N; i++){
        for(int j = N - 1; j > i; j--){
            if(A[j] < A[j-1]){
                SWAP(A, j, j-1);
            }
        }
    }
}

// Over
// Merge list A and B into C
void Merge(int *A, int aLen, int *B, int bLen, int *C){
    int i = 0, j = 0, k = 0;
    while(i < aLen && j < bLen){
        if(A[i] <= B[j]){
            C[k++] = A[i++];
        }
        else{
            C[k++] = B[j++];
        }
    }
    while(i < aLen){
        C[k++] = A[i++];
    }
    while(j < bLen){
        C[k++] = B[j++];
    }
    return;
}

void Merge_Sort(int *A, int p, int r){
    if(p >= r){         // Already sorted.
        return;
    }
    int q = (p + r) / 2;
    Merge_Sort(A, p, q);
    Merge_Sort(A, q+1, r);
    // Merge_Sort(A, p, q-1);           // 这种方式出问题可能是因为 q 的计算中会向下取整
    // Merge_Sort(A, q, r);

    int temp[N];
    Merge(A + p, q - p + 1, A + q + 1, r - q, temp + p);
    // Merge(A + p, q - p, A + q, r - q + 1, temp + p);
    for(int i = p; i <= r; i++){
        A[i] = temp[i];
    }
    return;
}

// Over
void Shell_Pass(int *A, int d){     // 和 Insertion_Sort 几乎一模一样
    for(int i = d; i < N; i++){
        int current_num = A[i];
        for(int j = i - d; j >= 0; j -= d){
            int k = i;
            if(current_num < A[j]){
                for(; k > j; k -= d){
                    A[k] = A[k - d];
                }
                A[k] = current_num;
                break;
            }
        }
    }
}

void Shell_Sort(int *A){
    int gap_sequence[3] = {3, 2, 1};
    for(int i = 0; i < 3; i++){
        Shell_Pass(A, gap_sequence[i]);
        Print_Result(A);
    }
    return;
}


// Over
// 构造最大堆, 取根作为最大值后修复大根堆, 以此循环即完成排序.
#define Parent(x)   (x-1)/2
#define Left(x)     x*2 + 1
#define Right(x)    x*2 + 2

void Max_Heapify(int *A, int i, int heap_size){     // O(log n)
    int l = Left(i), r = Right(i), max = i;
    if(l <= heap_size && A[l] > A[i]){
        max = l;
    }
    if(r <= heap_size && A[r] > A[max]){
        max = r;
    }
    if(i != max){
        SWAP(A, i, max);
        Max_Heapify(A, max, heap_size);     // 需要再次最大堆化的情况需要注意
    }
    return;
}

void Build_Max_Heap(int *A){                        // O(n), 每个节点 Max_Heapify 所需时间与节点高度有关, 累加后错位相减即可
    Print_Result(A);
    printf("\n");
    for(int i = (N-1)/2; i >= 0; i--){
        Max_Heapify(A, i, N);
    }
    return;
}

void Heap_Sort(int *A, int heap_size){              // O(n), 但 Max_Heapify O(log n), 故总时间为 O(n log n)
    Build_Max_Heap(A);
    for(int i = heap_size - 1; i > 0; i--){
        SWAP(A, 0, i);
        Max_Heapify(A, 0, i-1);
    }
}

// Over
// 选择一个元素, 将数组分为两部分, 其中一部分均比它小, 另一部分均比它大. 对这两部分分别调用 Quick_Sort
void Quick_Sort(int *A, int p, int r){
    if(p >= r){                     // 终止条件需要想清楚
        return;
    }
    int i = p - 1;                  // i is the pointer to the last number that less than A[r]
    for(int j = p; j < r; j++){     // j is the pointer to current number
        if(A[j] < A[r]){
            SWAP(A, ++i, j);
        }
    }
    SWAP(A, ++i, r);
    Quick_Sort(A, p, i-1);
    Quick_Sort(A, i+1, r);
    return;
}



int main(){
    printf("The list before sorting:");
    Print_Result(list);
    Bubble_Sort_New(list);
    printf("The list after sorting: ");
    Print_Result(list);
    return 0;
}