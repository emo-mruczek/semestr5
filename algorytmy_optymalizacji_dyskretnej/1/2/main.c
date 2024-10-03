//TODO: wykrywanie skierowanego cyklu

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DFS(void);
void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex); 

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile int8_t tree = 0;
volatile int8_t debug = 1;
uint8_t** G;

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
    //++num_of_edges;
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

    DFS();

    for ( uint32_t i = 0; i < num_of_vertices + 1; ++i ) {
        free(G[i]);
    }
    free(G);
}

void DFS(void) {
    printf("DFS:\n");
    uint32_t* visited_in_order = (uint32_t*)malloc(num_of_vertices * sizeof(uint32_t));
    memset(visited_in_order, 0, (num_of_vertices) * sizeof(uint32_t));
    uint32_t iter = 0;
    uint8_t* visited = (uint8_t*)malloc((num_of_vertices + 1) * sizeof(uint8_t));
    memset(visited, 0, (num_of_vertices + 1) * sizeof(uint8_t));

    /* algorithm starts */
    for ( uint32_t vertex = 1; vertex < num_of_vertices + 1; ++vertex ) {
        if ( !visited[vertex] ) {
            DFS_visit(visited_in_order, &iter, visited, vertex);
        }
    }
    /* algorithm ends */

    if ( debug ) printf("Visiting order:\n");
    for ( int32_t i = num_of_vertices - 1; i >= 0 ; --i ) {
        printf("%" PRIu32 " ", visited_in_order[i]);
    }
    printf("\n");

    free(visited);
    free(visited_in_order);
}

void DFS_visit(uint32_t* visited_in_order, uint32_t* iter, uint8_t* visited, uint32_t vertex) {
    /* algorithm starts */
    visited[vertex] = 1;
    
    for ( uint32_t i = 1; i < num_of_vertices + 1; ++i ) {
        if ( !G[vertex][i] ) continue;
        if ( !visited[i] ) {
            DFS_visit(visited_in_order, iter, visited, i);
        }
    }
    visited_in_order[*iter] = vertex;
    ++(*iter); 

    /* algorithms ends */
}



