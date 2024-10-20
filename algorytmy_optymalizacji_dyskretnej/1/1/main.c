#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/resource.h>

typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t* data;
} Queue;

typedef struct node {
    uint32_t vertex;
    struct node* next;
} node;

void BFS(void);
void DFS(void);
void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex);
uint32_t dequeue(Queue* Q);
void enqueue(Queue* Q, uint32_t temp);
void print_graph(node** Graph);
void add_edge(uint32_t v, uint32_t u, node** Graph);
void get_inputs(void);
void cleanup(void);

volatile bool is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile bool tree = false;
volatile bool debug = true;

node** G;
node** T;

int main(int argc, char** argv) {

    setrlimit(RLIMIT_STACK, &(struct rlimit) {
        .rlim_cur = RLIM_INFINITY,
        .rlim_max = RLIM_INFINITY
    });

    if (argc > 1 && * argv[1] == 'T') tree = true;

    get_inputs();

    BFS();

    if (tree) {
        print_graph(T);

        for (uint32_t i = 1; i <= num_of_vertices; ++i) {
            node* current = T[i];

            while (current != NULL) {
                node* temp = current;
                current = current->next;
                free(temp);
            }
        }

        free(T);
        T = NULL;
        T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));

        for (uint32_t i = 1; i <= num_of_vertices; ++i) T[i] = NULL;
    }

    DFS();

    if (tree) print_graph(T);

    cleanup();

    return 0;
}

/* relevant part of a program starts */

void BFS(void) {
    printf("BFS:\n");

    Queue Q  = {0, 0, num_of_vertices + 1, (uint32_t*)malloc((num_of_vertices + 1) * sizeof(uint32_t))};
    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));
    uint32_t* visited_in_order = (uint32_t*)calloc(num_of_vertices, sizeof(uint32_t));
    uint32_t iter = 0;

    /* algorithm starts */
    for (uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex) {
        if (!visited[vertex]) {
            enqueue( & Q, vertex);
            visited[vertex] = true;
            visited_in_order[iter++] = vertex;

            uint32_t u;

            while ((u = dequeue( & Q))) {
                node* neighbor = G[u];

                while (neighbor) {
                    uint32_t v = neighbor->vertex;

                    if (!visited[v]) {
                        visited[v] = true;
                        visited_in_order[iter++] = v;

                        if (tree) add_edge(u, v, T);

                        enqueue( & Q, v);
                    }

                    neighbor = neighbor->next;
                }
            }
        }
    }

    /* algorithm ends */

    if (debug) {
        printf("Visiting order:\n");

        for ( uint32_t i = 0; i < num_of_vertices; ++i ) {
            printf("%" PRIu32 " ", visited_in_order[i]);
        }

        printf("\n\n");
    }

    free(Q.data);
    free(visited);
    free(visited_in_order);
}

void DFS(void) {
    printf("DFS:\n");

    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));
    uint32_t* visited_in_order = (uint32_t*)calloc(num_of_vertices, sizeof(uint32_t));
    uint32_t iter = 0;

    /* algorithm starts */
    for (uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex) {
        if (!visited[vertex]) {
            DFS_visit(visited_in_order, & iter, visited, vertex);
        }
    }

    /* algorithm ends */

    if (debug) {
        printf("Visiting order:\n");

        for (uint32_t i = 0; i < num_of_vertices; ++i) {
            printf("%" PRIu32 " ", visited_in_order[i]);
        }

        printf("\n\n");
    }

    free(visited);
    free(visited_in_order);
}

void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex) {
    /* algorithm starts */
    visited[vertex] = true;

    node* temp = G[vertex];

    while (temp) {
        if (!visited[temp->vertex]) {
            if (tree) add_edge(vertex, temp->vertex, T);

            DFS_visit(visited_in_order, iter, visited, temp->vertex);
        }

        temp = temp->next;
    }

    visited_in_order[( * iter)++] = vertex;
    /* algorithms ends */
}

/* relevant part of a program end */

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

void add_edge(uint32_t v, uint32_t u, node** Graph) {
    node* new = (node*)malloc(sizeof(node));
    new->vertex = u;
    new->next = Graph[v];
    Graph[v] = new;
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

    if (tree) {
        T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));

        for (uint32_t i = 1; i <= num_of_vertices; ++i) T[i] = NULL;
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

    free(G);

    if (tree) {
        for (uint32_t i = 1; i <= num_of_vertices; ++i) {
            node* current = T[i];

            while (current) {
                node* next = current->next;
                free(current);
                current = next;
            }
        }

        free(T);
    }
}
