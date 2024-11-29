// minimum spanning tree
#include <stdio.h>
#include <inttypes.h>

#define NUM_VERTEX 5001      // number of vertices
#define NUM_EDGE 100001    // number of edges
#define DEBUG 0

typedef struct {
    int start, end;
    int64_t w;
}Edge;

typedef struct {
    Edge E[NUM_EDGE];
    int V[NUM_VERTEX];
    int NUM_V, NUM_E;
}Graph;

void SWAP(Edge *E, int i, int j) {
    if(i == j) {
        return;
    }
    Edge temp;
    temp = E[i];
    E[i] = E[j];
    E[j] = temp;
    return;
}

void Quick_Sort(Edge* E, int l, int r) {
    if(l >= r) {
        return;
    }
    int i = l - 1;
    for(int j = l; j < r; j++) {
        if(E[j].w < E[r].w) {
            SWAP(E, ++i, j);
        }
    }
    SWAP(E, ++i, r);
    Quick_Sort(E, l, i-1);
    Quick_Sort(E, i+1, r);
}

void Make_Graph(Graph *G) {
    scanf("%d %d", &G->NUM_V, &G->NUM_E);
    for(int i = 0; i < G->NUM_E; i++) {
        scanf("%d %d %"SCNd64, &G->E[i].start, &G->E[i].end, &G->E[i].w);
    }
}

int Find_Root(int *parent, int v) {
    while(parent[v] > 0) {
        v = parent[v];
    }
    return v;   // if v is the only node in the set, v.ancient = v;
}

int Kruskal(Graph *G) {
    int parent[NUM_VERTEX] = {0}, u_p, v_p;
    int64_t total_weight = 0;
    for(int i = 0; i < G->NUM_E; i++) {
        u_p = Find_Root(parent, G->E[i].start);
        v_p = Find_Root(parent, G->E[i].end);
        if(u_p != v_p) {
            parent[v_p] = u_p;  // UNION
            total_weight += G->E[i].w;
        }
    }
    printf("%"PRId64"\n", total_weight);
    return total_weight;
}
int main() {
    Graph G;
    Make_Graph(&G);
    if(DEBUG) {
        printf("The input graph\n");
        for(int i = 0; i < G.NUM_E; i++) {
            printf("%d -> %d, %"PRId64"\n", G.E[i].start, G.E[i].end, G.E[i].w);
        }
    }
    Quick_Sort(G.E, 0, G.NUM_E - 1);
    if(DEBUG) {
        printf("The sorted graph\n");
        for(int i = 0; i < G.NUM_E; i++) {
            printf("%d -> %d, %"PRId64"\n", G.E[i].start, G.E[i].end, G.E[i].w);
        }
    }
    Kruskal(&G);
    return 0;
}