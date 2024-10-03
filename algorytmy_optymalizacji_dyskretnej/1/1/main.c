//TODO: header
//TODO: make it faster
#include "inttypes.h"
#include "stdio.h"
#include "stdlib.h"

/* queue for BFS */

typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t* data;
} Queue;

uint32_t dequeue(Queue* Q);
void enqueue(Queue* Q, uint32_t temp);
void BFS();

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile int8_t tree = 0;
volatile int8_t debug = 1;
uint8_t** G;


int main(int argc, char** argv) {

    if ( argc > 1 ) if ( *argv[2] == 'T' ) tree = 1;

    if ( debug ) printf("(D)irected or (U)ndirected?\n");
    char temp;
    scanf("%c", &temp);
    is_directed = ( temp == 'D' ) ? 1 : 0;
    if ( debug ) printf("No. of vertices:\n");
    scanf("%" SCNu32, &num_of_vertices);
    if ( debug ) printf("No. of edges\n");
    scanf("%" SCNu32, &num_of_edges);
    ++num_of_edges;
    if ( debug ) printf("Vertices:\n");

    G = (uint8_t**)malloc((num_of_vertices + 1) * sizeof(uint8_t*));
    for ( uint8_t i = 0; i < num_of_vertices + 1; ++i ) {
        G[i] = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    }

    if ( !G ) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    uint32_t u, v;
    for (uint32_t i = 0; i < num_of_edges; ++i) {
        scanf("%" SCNu32 "%" SCNu32, &u, &v);
        G[u][v] = 1;
        if ( !is_directed ) G[v][u] = 1;
    }

    if ( debug ) {
        for (uint32_t i = 1; i < num_of_vertices + 1; ++i) {
            for (uint32_t j = 1; j < num_of_vertices + 1; ++j) {
                printf("%" PRIu32 " ", G[i][j] );
            }
            printf("\n");
        }
    }

    BFS();

    for (uint32_t i = 0; i < num_of_vertices + 1; ++i) {
        free(G[i]);
    }
    free(G);
}

//TODO: tree

void BFS() {
    // size of Q is number of vertices + 1
    Queue Q  = {0, 0, num_of_vertices + 1, (uint32_t*)malloc((num_of_vertices + 1) * sizeof(uint32_t))};

    uint32_t* visited_in_order = (uint32_t*)malloc(num_of_vertices * sizeof(uint32_t));
    uint32_t iter = 0;
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));

    for (uint32_t vertice = 1; vertice < num_of_vertices + 1; ++vertice) {
        if ( !visited[vertice] ) {
            enqueue(&Q, vertice);
            visited_in_order[iter] = vertice;
            ++iter;
            visited[vertice] = 1;

            uint32_t u;
            while ( (u = dequeue(&Q)) != 0 ) {
            for ( uint32_t i = 1; i < num_of_vertices + 1; ++i) {
                if ( !G[u][i] ) continue;
                    if ( !visited[i] ) {
                    visited_in_order[iter] = i;
                    ++iter;
                    visited[i] = 1;
                    enqueue(&Q, i);
                    }
                }
            }
        }
    }

    if ( debug ) printf("Order of visiting:\n");
    for (uint32_t i = 0; i < num_of_vertices; ++i) {
        printf("%" PRIu32 " ", visited_in_order[i]);
    }
    printf("\n");

    free(Q.data);
    free(visited);
    free(visited_in_order);
}

/* https://gist.github.com/ryankurte/61f95dc71133561ed055ff62b33585f8 */

uint32_t dequeue(Queue *Q) {
    if (Q->tail == Q->head) return 0;
    uint32_t temp = Q->data[Q->tail];
    Q->data[Q->tail] = 0;
    Q->tail = (Q->tail + 1) % Q->size;
    return temp;
}

void enqueue(Queue *Q, uint32_t temp) {
    if (((Q->head + 1) % Q->size) == Q->tail) {
        printf("Queue overflow!\n");
        exit(1);
    }
    Q->data[Q->head] = temp;
    Q->head = (Q->head + 1) % Q->size;
}
