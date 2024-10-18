//TODO: free
//TODO:undirected graph??????
//TODO: printing only for small num of ver
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* queue for BFS */

typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t* data;
} Queue;

typedef enum COLOR {
    GREEN,
    BLUE,
    NONE
} COLOR;

uint32_t dequeue(Queue* Q);
void enqueue(Queue* Q, uint32_t temp);
void BFS(void);
void print_tree(void);

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile int8_t tree = 0;
volatile int8_t debug = 1;
uint8_t** G;
uint8_t** T;

int main(int argc, char** argv) {

    if ( argc > 1 && *argv[1] == 'T' ) tree = 1;

    if ( debug ) printf("(D)irected or (U)ndirected?\n");
    char temp;
    scanf("%c", &temp);
    is_directed = ( temp == 'D' ) ? 1 : 0;
    if ( debug ) printf("No. of vertices:\n");
    scanf("%" SCNu32, &num_of_vertices);
    if ( debug ) printf("No. of edges:\n");
    scanf("%" SCNu32, &num_of_edges);
    if ( debug ) printf("Vertices:\n");

    G = (uint8_t**)malloc((num_of_vertices + 1) * sizeof(uint8_t*));
    for ( uint8_t i = 0; i < num_of_vertices + 1; ++i ) {
        G[i] = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
        memset(G[i], 0, (num_of_vertices + 1) * sizeof(uint8_t));
    }

    if ( !G ) {
        printf("Memory allocation error!\n");
        exit(1);
    }

    uint32_t u, v;
    for ( uint32_t i = 0; i < num_of_edges; ++i ) {
        scanf("%" SCNu32 "%" SCNu32, &u, &v);
        G[u][v] = 1;
        if ( !is_directed ) G[v][u] = 1;
    }

    if ( debug ) {
        for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
            for ( uint32_t j = 1; j < num_of_vertices + 1; ++j ) {
                printf("%" PRIu32 " ", G[i][j] );
            }
            printf("\n");
        }
    }

    if ( tree ) {
        T = (uint8_t**)malloc((num_of_vertices + 1) * sizeof(uint8_t*));
        for ( uint8_t i = 0; i < num_of_vertices + 1; ++i ) {
            T[i] = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
            memset(T[i], 0, (num_of_vertices + 1) * sizeof(uint8_t));
        }
    }

    BFS();

    for ( uint32_t i = 0; i < num_of_vertices + 1; ++i ) {
        free(G[i]);
    }
    free(G);
}

//TODO: tree

void BFS(void) {
    printf("BFS:\n");
    // size of Q is number of vertices + 1
    Queue Q  = {0, 0, num_of_vertices + 1, (uint32_t*)malloc((num_of_vertices + 1) * sizeof(uint32_t))};
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));
    COLOR* colors = (COLOR*)malloc((num_of_vertices + 1) * sizeof(COLOR));
    for (uint32_t i = 0; i < num_of_vertices + 1; i++) {
        colors[i] = NONE;
    }

    /* algorithm starts */
    for ( uint32_t vertex = 1; vertex < num_of_vertices + 1; ++vertex ) {
        if ( !visited[vertex] ) {
            colors[vertex] = GREEN;
            enqueue(&Q, vertex);
            visited[vertex] = 1;

            uint32_t u;
            while ( (u = dequeue(&Q)) != 0 ) {
                for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
                    if ( !G[u][i] ) continue;

                    if ( !visited[i] ) {
                        visited[i] = 1;
                        colors[i] = (colors[u] == GREEN) ? BLUE : GREEN;
                        if (tree) T[u][i] = 1;
                        enqueue(&Q, i);
                        for ( int k = 0; k < num_of_vertices + 1; ++k) printf("%d ", colors[k]);
                        printf("\n");
                    } else if ( i != u && colors[i] == colors[u] ) {
                        printf("It's NOT a bipartite graph! %" PRIu32 " %" PRIu32 "\n", i, u);
                        free(Q.data);
                        free(visited);
                        free(colors);
                        return;
                    }
                }
            }
        }
    }
    /* algorithm ends */

    printf("It's a bipartite graph!\n");
    printf("V0\tV1\n");
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        printf((colors[i] == GREEN ? "%" PRIu32 "\n" : "\t%" PRIu32 "\n"), i);
    }

    free(colors);
    free(Q.data);
    free(visited);
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
        exit(EXIT_FAILURE);
    }
    Q->data[Q->head] = temp;
    Q->head = (Q->head + 1) % Q->size;
}

void print_tree(void) {
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        for ( uint32_t j = 1; j < num_of_vertices + 1; ++j ) {
                printf("%" PRIu32 " ", T[i][j] );
            }
            printf("\n");
        }

}
