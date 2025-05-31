#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define NUM_VERTEX 200000
#define NUM_EDGE 200000
#define INFTY 1000000
#define SIZE_QUEUE 200000
#define MOD 1000000007

#define DEBUG 1

typedef struct Edge{
    int vex;
    struct Edge *next_edge;
}Edge;

typedef struct Node{
    int dist;
    int isReachable;   
    Edge *first_edge;
}Node;

typedef struct{
    Node V[NUM_VERTEX];
    int NUM_V, NUM_E;
}Graph;

typedef struct{
    int head, rear;
    int data[SIZE_QUEUE];
}Queue;

// Insert in head
void AddNewEdge(Graph *G, int u, int v) {
    Edge *new_edge = (Edge *)malloc(sizeof(Edge));
    new_edge->vex = v;
    new_edge->next_edge = NULL;
    if(G->V[u].first_edge == NULL) {        // no adjacent edge
        G->V[u].first_edge = new_edge;
        return;
    }
    new_edge->next_edge = G->V[u].first_edge;
    G->V[u].first_edge = new_edge;
    return;
}

Graph Make_Graph() {
    Graph G;
    int u, v;
    scanf("%d %d", &G.NUM_V, &G.NUM_E);
    for(int i = 0; i < G.NUM_E; i++) {
        scanf("%d %d", &u, &v);
        AddNewEdge(&G, u, v);
        AddNewEdge(&G, v, u);
    }
    if(!DEBUG){
        return G;
    }
    for(int i = 1; i <= G.NUM_V; i++) {
        printf("node.id = %d, to: ", i);
        Edge *e = G.V[i].first_edge;
        while(e != NULL) {
            printf("%d, ", e->vex);
            e = e->next_edge;
        }
        printf("\n");
    }
    return G;
}

Queue *CreateQueue() {
    Queue *Q = (Queue *)malloc(sizeof(Queue));
    // head == rear means the queue is empty
    Q->head = 0;        // head points to the first element to be dequeued
    Q->rear = 0;        // rear points to the first empty position
    return Q;
}

void enqueue(Queue* Q, int s) {
    Q->data[Q->rear] = s;
    Q->rear++;
    return;
}

int dequeue(Queue* Q) {
    return Q->data[Q->head++];
}

void FreeQueue(Queue *Q) {
    free(Q);
    return;
}

void BFS(Graph *G) {
    Queue *Q = CreateQueue();
    for(int i = 2; i <= G->NUM_V; i++) {
        G->V[i].dist = INFTY;
    }
    G->V[1].dist = 0;
    G->V[1].isReachable = 1;
    enqueue(Q, 1);
    while(Q->head != Q->rear) { // while the queue is not empty
        int u = dequeue(Q), v;
        Edge *last_edge = G->V[u].first_edge;
        while(last_edge != NULL) {
            v = last_edge->vex;
            if(G->V[v].isReachable == 0) {     // haven't visited v
                G->V[v].dist = G->V[u].dist + 1;
                enqueue(Q, v);
                G->V[v].isReachable = 1;
            }
            last_edge = last_edge->next_edge;
        }
    }
    FreeQueue(Q);

    if(!DEBUG) {
        return;
    }
    printf("The distance to source node is as follows:\n");
    for(int i = 1; i <= G->NUM_V; i++) {
        printf("%d, ", G->V[i].dist);
    }
    printf("\n");
}

void FindShortestPath(Graph *G) {
    Queue *Q = CreateQueue();
    int num[NUM_VERTEX] = {0, 1, 0}, visit[NUM_VERTEX] = {0};
    
    enqueue(Q, 1);
    visit[1] = 1;
    while(Q->head != Q->rear) {         // while the queue is not empty
        int u = dequeue(Q), v;
        Edge *adj_edges = G->V[u].first_edge;
        while(adj_edges != NULL) {
            v = adj_edges->vex;
            if(G->V[u].dist + 1 == G->V[v].dist) {
                if(visit[v] == 0) {
                    enqueue(Q, v);
                    visit[v] = 1;
                }
                num[v] = (num[v] + num[u]) % MOD;
            }
            adj_edges = adj_edges->next_edge;
        }
    }
    if(!DEBUG) {
        for(int i = 2; i <= G->NUM_V; i++) {
            printf("%d\n", num[i]);
        }
        return;
    }
    printf("The shortest path to all vertices are as follows:\n");
    for(int i = 2; i <= G->NUM_V; i++) {
        printf("%d, ", num[i]);
    }
    printf("\n");
    return;
}

int main() {
    Graph G = Make_Graph();
    BFS(&G);
    FindShortestPath(&G);
    return 0;
}