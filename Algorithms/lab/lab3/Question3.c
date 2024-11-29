#include<stdio.h>
#include<inttypes.h>

#define M 1000000

typedef struct{
    int start, end;
}Genie;

// swap the positions of two genies
void SWAP(Genie *A, int i, int j){
    if(i == j){
        return;
    }
    Genie temp;
    temp = A[i];
    A[i] = A[j];
    A[j] = temp;
    return; 
}

// sort genies according to their start time
void Quick_Sort(Genie *A, int l, int r{
    if(l >= r){
        return;
    }
    int i = l - 1;
    for(int j = l; j < r; j++){
        if(A[j].start < A[r].start){
            SWAP(A, ++i, j);
        }
    }
    SWAP(A, ++i, r);
    Quick_Sort(A, l, i-1);
    Quick_Sort(A, i+1, r);
    return;
}

void Greedy_Select(Genie* A, int end_time, int num){
    int res = 0, current_time = 0, start, end = current_time, i = 0;
    while(current_time < end_time){
        while(i < num){
            if(A[i].start > current_time + 1){
                break;
            }
            if(A[i].end > end){
                start = A[i].start;
                end = A[i].end;
            }
            i++;
        }
        // No progress are made, so we cann't achieve the goal
        if(end == current_time){
            printf("-1\n");
            return;
        }
        // printf("[%d, %d] ", start, end);
        ++res;
        current_time = end;
    }
    printf("%d\n", res);
    return;
}
int main(){
    Genie list[M];
    int end_time, num;
    scanf("%d %d", &end_time, &num);
    for(int i = 0; i < num; i++){
        scanf("%d %d", &list[i].start, &list[i].end);
    }
    Quick_Sort(list, 0, num - 1);
    Greedy_Select(list, end_time, num);
    return 0;
}
