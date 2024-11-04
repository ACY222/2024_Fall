// 女巫的魔法阵 Over
#include<stdio.h>
#include<inttypes.h>

#define N 1000000

typedef struct Binary_Tree_Node{
    int64_t dist, l_dist, r_dist;
    int left, right, parent;
    int l_num, r_num;
}Node;

void Print_Tree(Node *list, int n){
    for(int i = 1; i <= n; i++){
        printf("%d: left: %d, l_dist: %"PRId64", l_num: %d",
                i, list[i].left, list[i].l_dist, list[i].l_num);
        printf("; right: %d, r_dist: %"PRId64", r_num: %d",
                list[i].right, list[i].r_dist, list[i].r_num);
        printf("; parent: %d", list[i].parent);
        printf("\n");
    }
    return;
}

// Find root's dist, all nodes' l_num, r_num
void First_Traverse(Node *list, int n){
    for(int i = n; i >= 1; i--){
        int p = list[i].parent;
        if(list[p].left == i){  // i == i.p.left
            list[p].l_num = list[i].l_num + list[i].r_num + 1;
        }
        else{
            list[p].r_num = list[i].l_num + list[i].r_num + 1;
        }
        list[1].dist += list[i].l_dist * (int64_t)list[i].l_num
                      + list[i].r_dist * (int64_t)list[i].r_num;
    }
    return;
}

int Second_Traverse(Node *list, int n){
    int64_t min_dist = list[1].dist;
    int best_pos = 1;
    for(int i = 2; i <= n; i++){
        int p = list[i].parent;
        int64_t closer, further, dist = list[p].left == i ? list[p].l_dist : list[p].r_dist;
        closer = (int64_t)(list[i].l_num + list[i].r_num);
        further = (int64_t)(n - 2 - closer);
        list[i].dist = list[p].dist + (further - closer) * dist;
        if(list[i].dist < min_dist){
            min_dist = list[i].dist;
            best_pos = i;
        }
    }
    return best_pos;
}

int main(){
    Node list[N];
    int num, res;
    scanf("%d", &num);
    for(int i = 1; i < num; i++){
        int parent, child;
        int64_t dist;
        scanf("%d %d %"SCNd64, &parent, &child, &dist);
        if(list[parent].left == 0){
            list[parent].left = child;
            list[parent].l_dist = dist;
        }
        else{
            list[parent].right = child;
            list[parent].r_dist = dist;
        }
        list[child].parent = parent;
    }
    First_Traverse(list, num);
    // Print_Tree(list, num);
    res = Second_Traverse(list, num);
    printf("%d", res);
    return 0;
}