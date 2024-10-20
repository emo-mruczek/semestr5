#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/resource.h>
#include <time.h>

typedef struct node {
    uint32_t vertex;
    struct node* next;
} node;

void DFS(void);
bool DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex, bool* stack);
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

    setrlimit(RLIMIT_STACK, &(struct rlimit) {
        .rlim_cur = RLIM_INFINITY,
        .rlim_max = RLIM_INFINITY
    });

    get_inputs();

    struct timespec start, end;
 
    clock_gettime(CLOCK_REALTIME, &start);

    DFS();

    clock_gettime(CLOCK_REALTIME, &end);
    
    long time_spent = (end.tv_sec - start.tv_sec) * 1000000000L + 
                     (end.tv_nsec - start.tv_nsec) / 1000;

    printf("\nTime: %ld microseconds\n", time_spent) ;


    for (uint32_t i = 0; i <= num_of_vertices; ++i) {
        node* current = G[i];

        while (current) {
            node* next = current->next;
            free(current);
            current = next;
        }
    }

    free(G);
    return 0;
}

void DFS(void) {
    printf("\nDFS:\n");

    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));
    uint32_t* visited_in_order = (uint32_t*)calloc(num_of_vertices, sizeof(uint32_t));
    bool* stack = (bool*)calloc(num_of_vertices + 1, sizeof(bool));
    uint32_t iter = 0;

    /* algorithm starts */
    for ( uint32_t vertex = 1; vertex <= num_of_vertices; ++vertex ) {
        if (!visited[vertex]) {
            if (DFS_visit(visited_in_order, & iter, visited, vertex, stack) ) {
                printf("This graph has a cycle!!!\n");
                free(stack);
                free(visited);
                free(visited_in_order);
                return;
            }
        }
    }

    /* algorithm ends */

    printf("This graph is acyclic\n");

    if (should_print) {
        printf("Visiting order:\n");

        for (uint32_t i = 0; i < num_of_vertices; ++i) {
            printf("%" PRIu32 " ", visited_in_order[i]);
        }

        printf("\n\n");
    }

    free(stack);
    free(visited);
    free(visited_in_order);
}

bool DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex, bool* stack) {
    /* algorithm starts */
    visited[vertex] = true;
    stack[vertex] = true;

    node* temp = G[vertex];

    while (temp) {
        if (!visited[temp->vertex]) {
            if (DFS_visit(visited_in_order, iter, visited, temp->vertex, stack)) return true;
        } else if (stack[temp->vertex]) return true;

        temp = temp->next;
    }

    stack[vertex] = false;
    visited_in_order[( * iter)++] = vertex;
    return false;
    /* algorithms ends */
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

    if (debug) printf("(D)irected or (U)ndirected?\n");

    char temp;
    scanf("%c", & temp);
    is_directed = ( temp == 'D' ) ? 1 : 0;

    if (!temp) {
        printf("But it is supposed to be directed...\n");
        exit(EXIT_FAILURE);
    }

    if (debug) printf("No. of vertices:\n");

    scanf("%" SCNu32, & num_of_vertices);
    if (num_of_vertices <= 200) should_print = true;

    if (debug) printf("No. of edges:\n");

    scanf("%" SCNu32, & num_of_edges);

    if (debug) printf("Vertices:\n");

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

