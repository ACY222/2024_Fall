#include<stdio.h>
#include<inttypes.h>

#define UPPER 10000
#define max(x, y)  (x > y ? x : y)
#define min(x, y)  (x < y ? x : y)
typedef struct{
    int value, weight, number;
}ITEM;

int F[UPPER];

// capacity of knapsack, value and weight of current item
void ZeroOnePack(int capacity, int ni, int wi, int vi){   
    if(wi == 0){
        for(int w = 0; w <= capacity; w++){
            F[w] = F[w] + ni * vi;
        }
    } 
    else{
        for(int k = 1; k <= min(ni, capacity / wi); k++){
            for(int w = capacity; w >= k * wi; w--){
                F[w] = max(F[w], F[w - wi] + vi);
            }
        }
        return;
    }
}

int main(){
    ITEM items[UPPER];
    int num, capacity;
    scanf("%d %d", &num, &capacity);
    for(int i = 1; i <= num; i++){
        scanf("%d %d %d", &items[i].number, &items[i].weight, &items[i].value);
    }
    for(int i = 1; i <= num; i++){
        ZeroOnePack(capacity, items[i].number, items[i].weight, items[i].value);
    }
    printf("\n%d\n", F[capacity]);
    return 0;
}