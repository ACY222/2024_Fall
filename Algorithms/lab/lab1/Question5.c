// 女巫的魔法树 Over
#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>

#define UPPER 100000

typedef struct MagicTreeNode{
    int id, value;
    int parent, first_child, next_bro;
    int64_t whole_value;
}Node;

int64_t max = - UPPER;
Node list[UPPER];

void Whole_Value(int id){
    list[id].whole_value = list[id].value;
    if(list[id].first_child != 0){      // it has at least one child
        int p = list[id].first_child;
        list[id].whole_value += list[p].whole_value;  // it has more than one child
        while(list[p].next_bro != 0){
            p = list[p].next_bro;
            list[id].whole_value += list[p].whole_value;
        }
    }
}

void Print(int root){
    printf("id:%d, parent:%d, first_child:%d, next_bro:%d, value:%2d, whole_value:%"PRId64"\n",
             list[root].id, list[root].parent, list[root].first_child, list[root].next_bro, list[root].value, list[root].whole_value);
    return;
}

void Find_Max(int id){
    if(max < list[id].whole_value){
        max = list[id].whole_value;
    }
}

void MiddleOrder_Traversal(int root, void(*Func)(int)){
    if(root == 0){
        return;
    }
    MiddleOrder_Traversal(list[root].first_child, Func);
    Func(root);
    MiddleOrder_Traversal(list[root].next_bro, Func);
}

int main(){
    int N;

    // Initialization
    scanf("%d", &N);
    for(int i = 1; i <= N; i++){
        list[i].id = i;
        scanf("%d", &list[i].value);
    }
    for(int i = 1, parent_id, child_id; i < N; i++){
        scanf("%d %d", &parent_id, &child_id);
        list[child_id].parent = parent_id;
        if(list[parent_id].first_child == 0){
            list[parent_id].first_child = child_id;
        }
        else{
            int p = list[parent_id].first_child;
            while(list[p].next_bro != 0){
                p = list[p].next_bro;
            }
            list[p].next_bro = child_id;
        }
    }
    MiddleOrder_Traversal(1, &Whole_Value);
    // MiddleOrder_Traversal(1, &Print);
    MiddleOrder_Traversal(1, &Find_Max);
    printf("%"PRId64"\n", max);
    return 0;

}