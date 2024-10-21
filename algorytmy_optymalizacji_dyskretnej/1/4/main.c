#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

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

typedef struct node {
    uint32_t vertex;
    struct node* next;
} node;

uint32_t dequeue(Queue* Q);
void enqueue(Queue* Q, uint32_t temp);
void BFS(void);
void print_graph(node** Graph);
void add_edge(uint32_t v, uint32_t u, node** Graph);
void get_inputs(void);
void cleanup(void);

volatile bool is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile bool debug = false;
volatile bool should_print = false;

node** G;

int main() {

    get_inputs();

    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, & start);

    BFS();

    clock_gettime(CLOCK_REALTIME, & end);

    long time_spent = (end.tv_sec - start.tv_sec) * 1000000000L +
                      (end.tv_nsec - start.tv_nsec) / 1000;

    printf("\nTime: %ld microseconds\n", time_spent) ;

    cleanup();
}

void BFS(void) {
    Queue Q  = {0, 0, num_of_vertices + 1, (uint32_t*)malloc((num_of_vertices + 1) * sizeof(uint32_t))};
    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));
    COLOR* colors = (COLOR*)malloc((num_of_vertices + 1) * sizeof(COLOR));

    for (uint32_t i = 0; i <= num_of_vertices; i++) {
        colors[i] = NONE;
    }

    /* algorithm starts */
    for (uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex) {
        if (!visited[vertex]) {
            colors[vertex] = GREEN;
            enqueue( & Q, vertex);
            visited[vertex] = true;

            uint32_t u;

            while ((u = dequeue( & Q))) {
                node* neighbor = G[u];

                while (neighbor) {
                    uint32_t v = neighbor->vertex;

                    if (!visited[v]) {
                        visited[v] = true;

                        colors[v] = (colors[u] == GREEN) ? BLUE : GREEN;

                        if (debug) {
                            for ( int k = 0; k <= num_of_vertices; ++k) printf("%d ", colors[k]);

                            printf("\n");
                        }

                        enqueue( & Q, v);
                    } else if (v != u && colors[v] == colors[u]) {
                        printf("It's NOT a bipartite graph! %" PRIu32 " %" PRIu32 "\n", v, u);
                        free(Q.data);
                        free(visited);
                        free(colors);
                        return;
                    }

                    neighbor = neighbor->next;
                }
            }
        }
    }

    /* algorithm ends */

    printf("It's a bipartite graph!\n");


    if (should_print) {
        printf("V0\tV1\n");

        for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
            printf((colors[i] == GREEN ? "%" PRIu32 "\n" : "\t%" PRIu32 "\n"), i);
        }
    }

    free(colors);
    free(Q.data);
    free(visited);
}

void add_edge(uint32_t v, uint32_t u, node** Graph) {
    node* new = (node*)malloc(sizeof(node));
    new->vertex = u;
    new->next = Graph[v];
    Graph[v] = new;
}

/* https://gist.github.com/ryankurte/61f95dc71133561ed055ff62b33585f8 */

uint32_t dequeue(Queue* Q) {
    if (Q->tail == Q->head) return 0;

    uint32_t temp = Q->data[Q->tail];
    Q->data[Q->tail] = 0;
    Q->tail = (Q->tail + 1) % Q->size;
    return temp;
}

void enqueue(Queue* Q, uint32_t temp) {
    if (((Q->head + 1) % Q->size) == Q->tail) {
        printf("Queue overflow!\n");
        exit(EXIT_FAILURE);
    }

    Q->data[Q->head] = temp;
    Q->head = (Q->head + 1) % Q->size;
}

void print_graph(node** Graph) {
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        node* temp = Graph[i];
        printf("\n %" PRIu32 "\n\t", i);

        while ( temp ) {
            printf("%" PRIu32 " ", temp->vertex);
            temp = temp->next;
        }
    }

    printf("\n");
}

void get_inputs(void) {
    if ( debug ) printf("(D)irected or (U)ndirected?\n");

    char temp;
    scanf("%c", & temp);
    is_directed = ( temp == 'D' ) ? 1 : 0;

    if ( debug ) printf("No. of vertices:\n");

    scanf("%" SCNu32, & num_of_vertices);

    if ( debug ) printf("No. of edges:\n");

    scanf("%" SCNu32, & num_of_edges);

    if (num_of_edges <= 200) should_print = true;

    if ( debug ) printf("Vertices:\n");

    G = (node**)malloc((num_of_vertices + 1) * sizeof(node*));

    for (uint32_t i = 1; i <= num_of_vertices; ++i) G[i] = NULL;

    uint32_t u, v;

    for (uint32_t i = 0; i < num_of_edges; ++i) {
        scanf("%" SCNu32 "%" SCNu32, & u, & v);
        add_edge(u, v, G);

        if (!is_directed) add_edge(v, u, G);
    }

    if (debug) {
        printf("\nInput graph:\n");
        print_graph(G);
        printf("\n");
    }
}

void cleanup(void) {
    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        node* current = G[i];

        while (current) {
            node* next = current->next;
            free(current);
            current = next;
        }
    }
}
