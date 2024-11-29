// Topological Sort
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define NUM_VERTEX 6000
#define NUM_EDGE 200000
#define MOD 1000000007
#define DEBUG 0

typedef struct{
    int head, rear;
    int *data;
}Queue;

typedef struct Edge{
    int vex;
    struct Edge* next_edge;
}Edge;

typedef struct{
    int64_t num_ways;
    int in_degree, out_degree;
    Edge *first_edge;
}Node;

typedef struct{
    Node *V;
    int First_Generation[NUM_VERTEX], Last_Generation[NUM_VERTEX];
    int num_first, num_last;
    int NUM_V, NUM_E;
}Graph;

void AddNewEdge(Graph *G, int u, int v) {
    Edge *first_edge = G->V[u].first_edge;
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->vex = v;
    new_edge->next_edge = NULL;
    if(first_edge != NULL) {
        new_edge->next_edge = first_edge;
    }
    G->V[u].first_edge = new_edge;
    G->V[u].out_degree++;
    G->V[v].in_degree++;
    return;
}

void MakeGraph(Graph *G) {
    int N, M;
    scanf("%d %d", &N, &M);
    G->V = (Node*)malloc(sizeof(Node) * (N + 1));
    G->NUM_V = N;
    G->NUM_E = M;
    G->num_first = 0;
    G->num_last = 0;
    for (int i = 1; i <= N; i++) {
        G->V[i].first_edge = NULL;
        G->V[i].in_degree = 0;
        G->V[i].out_degree = 0;
        G->V[i].num_ways = 0;
    }
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        AddNewEdge(G, u, v);
    }
    for (int i = 1; i <= G->NUM_V; i++) {
        // in_degree equals 0 means it's the first generation
        if(G->V[i].in_degree == 0) {
            G->V[i].num_ways = 1;
            G->First_Generation[G->num_first++] = i;
        }
        // out_degree equals 0 means it's the last generation
        if(G->V[i].out_degree == 0) {
            G->Last_Generation[G->num_last++] = i;
        }
    }
    return;
}

void PrintGraph(Graph *G) {
    for(int i = 1; i <= G->NUM_V; i++) {
        Edge *first_edge = G->V[i].first_edge;
        while(first_edge != NULL) {
            printf("(%d, %d)\n", i, first_edge->vex);
            first_edge = first_edge->next_edge;
        }
    }
    return;
}
Queue *InitializeQueue(int size) {
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    Q->data = (int *)malloc(sizeof(int) * size);
    // head == rear means the queue is empty
    Q->head = 0;
    Q->rear = 0;
    return Q;
}

void EnQueue(Queue *Q, int v) {
    Q->data[Q->rear] = v;
    Q->rear++;
    return;
}

int DeQueue(Queue *Q) {
    return Q->data[Q->head++];
}

void BFS(Graph *G) {
    Queue *Q = InitializeQueue(G->NUM_V);
    for(int i = 0; i < G->num_first; i++) {
        EnQueue(Q, G->First_Generation[i]);
    }
    while(Q->head != Q->rear) { // The queue is not empty
        int u = DeQueue(Q);
        Edge *adj_edge = G->V[u].first_edge;
        while(adj_edge != NULL) {
            int v = adj_edge->vex;
            G->V[v].num_ways = (G->V[v].num_ways + G->V[u].num_ways) % MOD;
            G->V[v].in_degree--;
            if(G->V[v].in_degree == 0) {
                EnQueue(Q, v);
            }
            adj_edge = adj_edge->next_edge;
        }
    }
    free(Q);
    int64_t total_ways = 0;
    for(int i = 0; i < G->num_last; i++) {
        total_ways += G->V[G->Last_Generation[i]].num_ways % MOD;
    }
    printf("%"PRId64"\n", total_ways);
    return;
}

int main() {
    Graph G;
    MakeGraph(&G);
    if(DEBUG) {
        PrintGraph(&G);
    }
    BFS(&G);
    return 0;
}