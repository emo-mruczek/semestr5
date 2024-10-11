//TODO: refactor
//TODO: should print scc
//TODO: velgrind
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DFS(void);
void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex);  
void add_edge(uint32_t v, uint32_t u);
void add_edge_T(uint32_t v, uint32_t u);
void transpose(void);
//temp
void DFS_T(void);
uint32_t* DFS_visit_T(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex);

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile int8_t debug = 1;

typedef struct node {
    uint32_t vertex;
    struct node* next;
} node;

struct node** G;
struct node** T;

// temppp
uint32_t* visited_in_order; 


int main(int argc, char** argv) {
    if ( debug ) printf("(D)irected or (U)ndirected?\n");
    char temp;
    scanf("%c", &temp);
    is_directed = ( temp == 'D' ) ? 1 : 0;
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
    //memset?

    uint32_t u, v;
    for ( uint32_t i = 0; i < num_of_edges; ++i ) {
        scanf("%" SCNu32 "%" SCNu32, &u, &v);
        add_edge(u, v);
    }

    if ( debug ) {
        for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
            node* temp = G[i];
            printf("\n %" PRIu32 "\n\t", i);
            while ( temp ) {
                printf("%" PRIu32 " ", temp->vertex);
                temp = temp->next;
            }
        } 
    }

    visited_in_order = (uint32_t*)malloc(num_of_vertices * sizeof(uint32_t));
    memset(visited_in_order, 0, (num_of_vertices) * sizeof(uint32_t));

    DFS();

    transpose();

    if ( debug ) {
        for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
            node* temp = T[i];
            printf("\n %" PRIu32 "\n\t", i);
            while ( temp ) {
                printf("%" PRIu32 " ", temp->vertex);
                temp = temp->next;
            }
        } 
    }

    DFS_T();

    for ( uint32_t i = 0; i <= num_of_vertices; ++i ) {
        node* temp = T[i];
        while ( temp ) {
            node* to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(T);
    for ( uint32_t i = 0; i < num_of_vertices + 1; ++i ) {
        free(G[i]);
    }
    free(G);
    free(visited_in_order);
}

void DFS(void) {
    uint32_t iter = 0;
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));

    /* algorithm starts */
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        if ( !visited[i] ) {
            DFS_visit(visited_in_order, &iter, visited, i);
        }
    }
    /* algorithm ends */

    printf("\nvisited in order:\n");

    for ( uint32_t i = 0; i < num_of_vertices; ++i ) printf("%" PRIu32 " ", visited_in_order[i]);

    free(visited);
}

void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex) {
    /* algorithm starts */
    visited[vertex] = 1;

    node* temp = G[vertex];
    while ( temp ) {
        if ( !visited[temp->vertex] ) DFS_visit(visited_in_order, iter, visited, temp->vertex);
        temp = temp->next;
    }

    visited_in_order[*iter] = vertex;
    ++(*iter); 
    /* algorithms ends */
}

void transpose(void) {
    T = (node**)malloc((num_of_vertices + 1) * sizeof(node*));
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) T[i] = NULL;

    for ( uint32_t i = 1; i <= num_of_vertices; ++i ) {
        node *temp = G[i];
        while ( temp ) {
            add_edge_T(temp->vertex, i); 
            temp = temp->next;
        }
    }
}

/* for transposed */

void DFS_T(void) {
    uint32_t* component_order = (uint32_t*)malloc((num_of_vertices) * sizeof(uint32_t));
    memset(component_order, 0, (num_of_vertices) * sizeof(uint32_t));
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));
    
    uint32_t iter = 0;
    uint32_t num_of_scc = 0;

    /* algorithm starts*/
    for ( int32_t i = num_of_vertices - 1; i >= 0; --i ) { 
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

uint32_t* DFS_visit_T(uint32_t* component_order, uint32_t* iter, uint8_t* visited, uint32_t vertex) {
    visited[vertex] = 1;
    component_order[*iter] = vertex;
    (*iter)++;

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

