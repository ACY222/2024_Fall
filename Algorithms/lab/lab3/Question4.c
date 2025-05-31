#include<stdio.h>
#include<inttypes.h>

#define UPPER 1000
#define max(x, y)  x > y ? x : y
typedef struct{
    int value, weight;
}ITEM;

int F[UPPER];

// capacity of knapsack, value and weight of current item
void ZeroOnePack(int capacity, int wi, int vi){    
    for(int w = capacity; w >= wi; w--){
        F[w] = max(F[w], F[w - wi] + vi);
    }
    return;
}

int main(){
    ITEM items[UPPER];
    int Value[UPPER] = {0}, Weight[UPPER] = {0}, num, capacity;
    scanf("%d %d", &num, &capacity);
    for(int i = 1; i <= num; i++){
        scanf("%d %d", &items[i].weight, &items[i].value);
    }
    for(int i = 1; i <= num; i++){
        ZeroOnePack(capacity, items[i].weight, items[i].value);
    }
    printf("\n%d\n", F[capacity]);
    return 0;
}