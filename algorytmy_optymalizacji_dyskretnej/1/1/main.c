//TODO: tests (gotfryd's graphs)
//TODO: free in different function
//TODO: formatting
#include <inttypes.h>
#include <stdint.h>
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

uint32_t dequeue(Queue* Q);
void enqueue(Queue* Q, uint32_t temp);
void BFS(void);
void DFS(void);
void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex); 
void print_tree(void);
void add_edge(uint32_t v, uint32_t u);
void add_edge_T(uint32_t v, uint32_t u);

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile int8_t tree = 0;
volatile int8_t debug = 0;

typedef struct node {
    uint32_t vertex;
    struct node* next;
} node;

struct node** G;
struct node** T;

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

    G = (node**)malloc((num_of_vertices + 1) * sizeof(node*));
    for (uint32_t i = 1; i <= num_of_vertices; ++i) G[i] = NULL;

    uint32_t u, v;
    for ( uint32_t i = 0; i < num_of_edges; ++i ) {
        scanf("%" SCNu32 "%" SCNu32, &u, &v);
        add_edge(u, v);
        if ( !is_directed ) add_edge(v, u);
    }

     if ( debug ) {
        for ( uint32_t i = 1; i <= num_of_vertices; ++i ) {
            node* temp = G[i];
            printf("\n %" PRIu32 "\n\t", i);
            while ( temp ) {
                printf("%" PRIu32 " ", temp->vertex);
                temp = temp->next;
            }
        }
        printf("\n");
    }

    if (tree) {
        T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));
        for (uint32_t i = 1; i <= num_of_vertices; ++i) T[i] = NULL;
    }

    BFS();

    if ( tree ) {print_tree();

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
    }

    if ( tree ) {
T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));
        for (uint32_t i = 1; i <= num_of_vertices; ++i) T[i] = NULL;

    }

    DFS();

    if ( tree ) print_tree();

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

    return 0;
}

void BFS(void) {
    printf("BFS:\n");
    Queue Q  = {0, 0, num_of_vertices + 1, (uint32_t*)malloc((num_of_vertices + 1) * sizeof(uint32_t))};

    uint32_t* visited_in_order = (uint32_t*)malloc(num_of_vertices * sizeof(uint32_t));
    memset(visited_in_order, 0, (num_of_vertices) * sizeof(uint32_t));
    uint32_t iter = 0;
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));

    /* algorithm starts */
    for ( uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex ) {
        if ( !visited[vertex] ) {
            enqueue(&Q, vertex);
            visited[vertex] = 1;
            visited_in_order[iter] = vertex;
            ++iter;

            uint32_t u;
            while ( (u = dequeue(&Q)) != 0 ) {
                node* neighbor = G[u];
                while ( neighbor ) {
                    uint32_t v = neighbor->vertex;
                    if ( !visited[v] ) {
                        visited[v] = 1;
                        visited_in_order[iter] = v;
                        ++iter;

                        if ( tree ) add_edge_T(u, v);

                        enqueue(&Q, v);
                    }
                    neighbor = neighbor->next;
                }


                }
            }
        }
    
    /* algorithm ends */

    if ( debug ) {
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
    uint32_t* visited_in_order = (uint32_t*)malloc(num_of_vertices * sizeof(uint32_t));
    memset(visited_in_order, 0, (num_of_vertices) * sizeof(uint32_t));
    uint32_t iter = 0;
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));

    /* algorithm starts */
    for ( uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex ) {
        if ( !visited[vertex] ) {
            DFS_visit(visited_in_order, &iter, visited, vertex);
        }
    }
    /* algorithm ends */

    if ( debug ) {
        printf("Visiting order:\n");
        for ( uint32_t i = 0; i < num_of_vertices; ++i ) {
            printf("%" PRIu32 " ", visited_in_order[i]);
        }
        printf("\n\n");
    }

    free(visited);
    free(visited_in_order);
}

void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex) {
    /* algorithm starts */
    visited[vertex] = 1;

    node* temp = G[vertex];
    while ( temp ) {
        if ( !visited[temp->vertex] ) {
            if ( tree ) add_edge_T(vertex, temp->vertex);
            DFS_visit(visited_in_order, iter, visited, temp->vertex);
        }
        temp = temp->next;
    }

    visited_in_order[*iter] = vertex;
    ++(*iter);

    /* algorithms ends */
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
            node* temp = T[i];
            printf("\n %" PRIu32 "\n\t", i);
            while ( temp ) {
                printf("%" PRIu32 " ", temp->vertex);
                temp = temp->next;
            }
        }
        printf("\n");
}


void add_edge_T(uint32_t v, uint32_t u) {
    node* new = (node*)malloc(sizeof(node));
    new->vertex = u;
    new->next = T[v];
    T[v] = new;
}

void add_edge(uint32_t v, uint32_t u) {
    node* new = (node*)malloc(sizeof(node));
    new->vertex = u;
    new->next = G[v];
    G[v] = new;
}
