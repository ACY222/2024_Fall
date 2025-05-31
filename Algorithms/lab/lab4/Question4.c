// 二分图匹配，匈牙利算法
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct{
    int **link;
    int rows, cols, edges;
}Graph;

int *InitializeMatch(int n) {
    int *match = (int *)malloc((n + 1) * sizeof(int));
    for(int i = 0; i <= n; i++) {
        match[i] = 0;
    }
    return match;
}

void InitializeGraph(Graph *G) {
    scanf("%d %d %d", &G->rows, &G->cols, &G->edges);
    G->link = (int **)malloc((G->rows + 1) * sizeof(int *));
    for(int i = 0; i <= G->rows; i++) {
        G->link[i] = (int *)malloc((G->cols + 1) * sizeof(int));
    }
    for(int i = 0; i < G->edges; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        G->link[x][y] = 1;
    }
    return;
}

int FindAugmentPath(Graph *G, int *match, int x, int *path) {
    for(int i = 1; i <= G->cols; i++) {
        if(G->link[x][i]) {
            if(path[i]) {
                continue;
            }
            path[i] = 1;
            if(match[i] == 0 || FindAugmentPath(G, match, match[i], path)) {
                match[i] = x;
                return 1;
            }
        }
    }
    return 0;
}

void Hungarian(Graph *G, int *match) {
    int maxMatch = 0;
    for(int i = 1; i <= G->rows; i++) {
        int *path = (int *)malloc((G->cols + 1) * sizeof(int));
        for(int j = 1; j <= G->cols; j++) {
            path[j] = 0;
        }
        if(FindAugmentPath(G, match, i, path)) {
            maxMatch++;
        }
    }
    printf("%d\n", maxMatch);
}

int main() {
    Graph G;
    int *match;
    InitializeGraph(&G);
    match = InitializeMatch(G.cols);
    Hungarian(&G, match);
    return 0;

}