#include<stdio.h>

#define N 12
#define INFTY 100   // make sure that INFTY is bigger than a[i] for every i.

void FIND_MIN(int *list, int *min_id){  // find the id of local minimum in the list
    int i, j = 1;
    for(i = 1; i < N - 1; i++){
        if(list[i] <= list[i + 1] && list[i] <= list[i - 1]){
            min_id[j] = i;
            j++;
            min_id[0]++;
        }
    }
}

void PRINT_THE_LIST(int *list){         // as it's named, print the list
    for(int i = 0; i < N; i++){
        printf("%2d, ", list[i]);
    }
    printf("\n");
}

int main(){
    int list[N] = {INFTY, 1, 3, 4, 5, 3, 2, 6, 6, 6, 7, INFTY}, i, j, num = 1, INDEX[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int min_id[N] = {0};    // min_id[0] means the number of the local minimum in the list, and min_id[1] - min_id[N-1] shows the details.
    int grade[N] = {0};     // grade[i] is c[i], actually
    FIND_MIN(list, min_id);

    for(i = 1; i <= min_id[0]; i++){    // from left to right
        for(j = min_id[i]; list[j] >= list[j - 1] || j == min_id[i]; j++){
            if(list[j] > list[j - 1]){
                grade[j] = ++num;
            }
            else{
                grade[j] = num;
            }
        }
        num = 1;
    }

    for(i = min_id[0]; i > 0; i--){     // from right to left
        for(j = min_id[i]; list[j] >= list[j + 1] || j == min_id[i]; j--){
            if(list[j] > list[j + 1]){
                num++;
                if(grade[j] < num){
                    grade[j] = num;
                }
            }
            else{
                if(grade[j] < num){
                    grade[j] = num;
                }
            }
        }
        num = 1;
    }

    PRINT_THE_LIST(min_id);
    PRINT_THE_LIST(INDEX);
    PRINT_THE_LIST(list);
    PRINT_THE_LIST(grade);
    return 0;
}