#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
//temp
void DFS_T(void);
uint32_t* DFS_visit_T(uint32_t* visited_in_order, uint32_t* iter, bool* visited, uint32_t vertex);

volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile bool debug = true;

node** G;
node** T;

uint32_t* visited_in_order; 

int main() {

    get_inputs();

    printf("dupa1\n");
    
    print_graph(G);

    DFS();

    printf("dupa2\n");

    transpose();

    printf("dupa4\n");

    print_graph(T);

    DFS_T();

    clean_up();
}

void DFS(void) {
    uint32_t iter = 0;
    bool* visited = (bool*)calloc(num_of_vertices + 1, sizeof(bool));

    /* algorithm starts */
    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        if (!visited[i]) {
            DFS_visit(visited_in_order, &iter, visited, i);
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

    visited_in_order[(*iter)++] = vertex;
    /* algorithms ends */
}

void transpose(void) {
    T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));
    for (uint32_t i = 1; i < num_of_vertices + 1; ++i) T[i] = NULL;

    for (uint32_t i = 1; i <= num_of_vertices; ++i) {
        node *temp = G[i];
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
            DFS_visit_T(component_order, &iter, visited, vertex);
            for (uint32_t j = 0; j < iter; ++j) {
                printf("%u ", component_order[j]);
            }
            iter = 0;
        }
    }
    /* algorithm ends */

    free(visited);
    free(component_order);
}

uint32_t* DFS_visit_T(uint32_t* component_order, uint32_t* iter, bool* visited, uint32_t vertex) {
    visited[vertex] = 1;
    component_order[(*iter)++] = vertex;

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
    if ( debug ) printf("(D)irected or (U)ndirected?\n");

    char temp;
    scanf("%c", &temp);
    bool is_directed = ( temp == 'D' ) ? 1 : 0;
    if ( !temp ) {
        printf("But it is supposed to be directed...\n");
        exit(1);
    }

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

        while ( temp ) {
            printf("%" PRIu32 " ", temp->vertex);
            temp = temp->next;
        }
    }

    printf("\n");
}

void clean_up(void) {

    for ( uint32_t i = 1; i <= num_of_vertices; ++i ) {
        node* temp = T[i];
        while ( temp ) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(T);

    for ( uint32_t i = 1; i <= num_of_vertices; ++i ) {
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
