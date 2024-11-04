// 女巫的圣诞树 Over
#include<stdio.h>
#include<inttypes.h>

#define LOWER 2
#define UPPER 100000


typedef struct Child_Sibling_TreeNode{
    int64_t value;
    int parent;
}Node;

void Eratosthenes(int *list){
    for(int i = LOWER; i*i < UPPER; i++){
        int upper = UPPER / i;
        for(int j = i; j < upper; j++){
            list[i*j] = 1;      // list[i] == 1 means i is not a prime number
        }
    }
}

void Print_Tree(Node *list, int n){
    for(int i = 1; i <= n; i++){
        printf("%d's parent: %d\n", i, list[i].parent);
    }
}

int64_t Traverse_Tree(Node *list, int *is_prime, int n){
    int64_t sum = 0;
    for(int i = n; i > 0; i--){
        int p = list[i].parent;
        if(is_prime[i] == 0 && is_prime[p] == 0){       // both the order of i and his parent are prime number
            list[p].value += list[i].value;
            list[i].value = 0;
        }
    }
    for(int i = 1; i <= n; i++){
        if(list[i].value > 0){
            sum += list[i].value;
        }
    }
    return sum;
}

int main(){
    Node node_list[UPPER];
    int is_prime[UPPER] = {1, 1, 0}, num;
    int64_t happiness = 0;
    Eratosthenes(is_prime);
    scanf("%d", &num);
    for(int i = 1; i <= num; i++){
        node_list[i].parent = 0;
        scanf("%"SCNd64, &node_list[i].value);
    }
    for(int i = 1; i < num; i++){
        int parent, child;
        scanf("%d %d", &parent, &child);
        // child to parent
        node_list[child].parent = parent;
    }
    // Print_Tree(node_list, num);
    happiness = Traverse_Tree(node_list, is_prime, num);
    printf("%"PRId64"\n", happiness);
    return 0;
}