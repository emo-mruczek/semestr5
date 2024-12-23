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
void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex);
void add_edge(uint32_t v, uint32_t u, node** Graph);
void transpose(void);
void get_inputs(void);
void print_graph(node** Graph);
void clean_up(void);
void DFS_T(void);
uint32_t* DFS_visit_T(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex);

volatile uint32_t num_of_vertices = 0;
volatile uint32_t num_of_edges = 0;
volatile bool debug = false;
volatile bool should_print = false;

node** G;
node** T;

uint32_t* visited_in_order;

int main() {

    setrlimit(RLIMIT_STACK, & (struct rlimit) {
        .rlim_cur = RLIM_INFINITY,
        .rlim_max = RLIM_INFINITY
    });

    get_inputs();

    if (debug) print_graph(G);

    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, & start);

    DFS();

    transpose();

    if (debug) print_graph(T);

    DFS_T();

    clock_gettime(CLOCK_REALTIME, & end);

    long time_spent = (end.tv_sec - start.tv_sec) * 1000000000L +
                      (end.tv_nsec - start.tv_nsec) / 1000;

    printf("\nTime: %ld microseconds\n", time_spent) ;

    clean_up();
}

void DFS(void) {
    uint32_t iter = 0;
    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));

    /* algorithm starts */
    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        if (!visited[i]) {
            DFS_visit(visited_in_order, & iter, visited, i);
        }
    }

    /* algorithm ends */

    free(visited);
}

void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex) {
    /* algorithm starts */
    visited[vertex] = true;

    node* temp = G[vertex];

    while (temp) {
        if ( !visited[temp->vertex] ) DFS_visit(visited_in_order, iter, visited, temp->vertex);

        temp = temp->next;
    }

    visited_in_order[( * iter)++] = vertex;
    /* algorithms ends */
}

void transpose(void) {
    T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));

    for (uint32_t i = 1; i < num_of_vertices + 1; ++i) T[i] = NULL;

    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        node* temp = G[i];

        while (temp) {
            add_edge(temp->vertex, i, T);
            temp = temp->next;
        }
    }
}

/* for transposed */

void DFS_T(void) {

    uint32_t* component_order = (uint32_t*)calloc(num_of_vertices, sizeof(uint32_t));
    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));

    uint32_t iter = 0;
    uint32_t num_of_scc = 0;

    /* algorithm starts*/
    for (int32_t i = num_of_vertices - 1; i >= 0; --i) {
        uint32_t vertex = visited_in_order[i];

        if ( !visited[vertex] ) {
            printf("\nSCC %u: ", ++num_of_scc);
            DFS_visit_T(component_order, & iter, visited, vertex);
            uint32_t num_of_items = 0;

            for (uint32_t j = 0; j < iter; ++j) {
                ++num_of_items;

                if (should_print) printf("%u ", component_order[j]);
            }

            printf(" Number of items in SCC: %" PRIu32 "\n", num_of_items);
            iter = 0;
        }
    }

    /* algorithm ends */

    free(visited);
    free(component_order);
}

uint32_t* DFS_visit_T(uint32_t* component_order, uint32_t* iter, bool* visited, uint32_t vertex) {
    visited[vertex] = 1;
    component_order[( * iter)++] = vertex;

    /* algorithm starts */
    node* temp = T[vertex];

    while (temp) {
        if (!visited[temp->vertex]) {
            DFS_visit_T(component_order, iter, visited, temp->vertex);
        }

        temp = temp->next;
    }

    /* algorithm ends */

    return component_order;
}

void add_edge(uint32_t v, uint32_t u, node** Graph) {
    node* new = (node*)malloc(sizeof(node));
    new->vertex = u;
    new->next = Graph[v];
    Graph[v] = new;
}

void get_inputs() {
    if (debug) printf("(D)irected or (U)ndirected?\n");

    char temp;
    scanf("%c", & temp);
    bool is_directed = ( temp == 'D' ) ? 1 : 0;

    if (!temp) {
        printf("But it is supposed to be directed...\n");
        exit(1);
    }

    if (debug) printf("No. of vertices:\n");

    scanf("%" SCNu32, & num_of_vertices);

    if (debug) printf("No. of edges:\n");

    scanf("%" SCNu32, & num_of_edges);

    if (num_of_edges <= 200) should_print = true;

    if (debug) printf("Vertices:\n");

    G = (node**)malloc((num_of_vertices + 1) * sizeof(node*));

    for (uint32_t i = 1; i <= num_of_vertices; ++i) G[i] = NULL;

    uint32_t u, v;

    for (uint32_t i = 0; i < num_of_edges; ++i) {
        scanf("%" SCNu32 "%" SCNu32, & u, & v);
        add_edge(u, v, G);
    }

    if (debug) {
        printf("\nInput graph:\n");
        print_graph(G);
        printf("\n");
    }

    visited_in_order = (uint32_t*)calloc(num_of_vertices, sizeof(uint32_t));
}

void print_graph(node** Graph) {
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        node* temp = Graph[i];
        printf("\n %" PRIu32 "\n\t", i);

        while (temp) {
            printf("%" PRIu32 " ", temp->vertex);
            temp = temp->next;
        }
    }

    printf("\n");
}

void clean_up(void) {

    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        node* temp = T[i];

        while ( temp ) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }

    free(T);

    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        node* temp = G[i];

        while (temp) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }

    free(G);
    free(visited_in_order);
}
