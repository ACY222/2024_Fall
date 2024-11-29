#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 1000
#define DEBUG 0
#define pos(i, j) ((i) * size + (j))   // pos[i][j]

typedef struct{
    int num[BOARD_SIZE * BOARD_SIZE];
    int parent[BOARD_SIZE * BOARD_SIZE];
}DSU;

void input(int *board, int size) {
    for (int i = 1; i <= size; i++) {
        char *row_input = (char *)malloc((size + 1) * sizeof(char));
        scanf("%s", row_input);

        for (int j = 0; j < size; j++) {
            board[pos(i, j + 1)] = row_input[j] - '0';
        }
        free(row_input);
    }
    return;
}

void print_board(int *board, int size) {
    if (!DEBUG) {
        return;
    }
    printf("\nThe numbers on the board are: \n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            printf("%d", board[pos(i, j)]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void print_DSU(DSU *dsu, int *board, int size) {
    if (!DEBUG) {
        return;
    }
    printf("\nThe DSU->num is: \n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            printf("%d ", dsu->num[pos(i, j)]);
        }
        printf("\n");
    }
    printf("\nThe DSU->parent is: \n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            printf("%d ", dsu->parent[pos(i, j)]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

DSU *Init_DSU(int size) {
    DSU *dsu = (DSU *)malloc(sizeof(DSU));
    for(int i = 1; i <= size; i++) {
        for(int j = 1; j <= size; j++) {
            dsu->num[pos(i, j)] = 1;
            dsu->parent[pos(i, j)] = pos(i, j);
        }
    }
    return dsu;
}

int Find(DSU *dsu, int pos) {
    return dsu->parent[pos] == pos ? pos : (dsu->parent[pos] = Find(dsu, dsu->parent[pos]));
}

void Union(DSU *dsu, int x, int y) {
    int x_ancient = Find(dsu, x), y_ancient = Find(dsu, y);
    dsu->parent[y_ancient] = x_ancient;
    dsu->num[x_ancient] += dsu->num[y_ancient];
    return;
}

void make_DSU(DSU *dsu, int *board, int size) {
    int current, right, down;
    for(int i = 1; i < size; i++) {
        for(int j = 1; j < size; j++) {
            current = pos(i, j), right = pos(i, j+1), down = pos(i+1, j);
            if(board[current] != board[right]) {
                if(Find(dsu, current) != Find(dsu, right)) {
                    Union(dsu, current, right);
                }
            }
            if(board[current] != board[down]) {
                if(Find(dsu, current) != Find(dsu, down)) {
                    Union(dsu, current, down);
                }
            }
        }
        current = pos(i, size);
        down = pos(i+1, size);
        if(board[current] != board[down]) {  // 每行的最后一列
            if(Find(dsu, current) != Find(dsu, down)) {
                Union(dsu, current, down);
            }
        }
    }
    // 单独处理最后一行
    for(int j = 1; j < size; j++) {
        current = pos(size, j);
        right = pos(size, j+1);
        if(board[current] != board[right]) {
            if(Find(dsu, current) != Find(dsu, right)) {
                Union(dsu, current, right);
            }
        }
    }
}

void output(DSU *dsu, int num, int size) {
    int x, y;
    for(int i = 1; i <= num; i++) {
        scanf("%d %d", &x, &y);
        printf("%d\n", dsu->num[Find(dsu, pos(x, y))]);
    }
    return;
}

int main() {
    int num_question, size, board[BOARD_SIZE * BOARD_SIZE];
    scanf("%d %d", &size, &num_question);
    input((int *)board, size);
    print_board((int *)board, size);

    DSU *dsu = Init_DSU(size);
    make_DSU(dsu, (int *)board, size);
    print_DSU(dsu, (int *)board, size);
    output(dsu, num_question, size);
    return 0;

}