#include "inttypes.h"
#include "stdio.h"
#include "stdlib.h"
volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile uint8_t debug = 1;
uint32_t** G;  


/* reprezantacja listowa, bo jest lepsza dla grafów rzadkich; nie chce mi sie dodatkowo
* robic macierzowej */

int main() {

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

    G = (uint32_t**)malloc(num_of_edges * sizeof(uint32_t*));
    for ( uint32_t i = 0; i < num_of_edges; ++i ) {
        G[i] = (uint32_t*)malloc(num_of_edges * sizeof(uint32_t));
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

    for (uint32_t i = 1; i < num_of_vertices + 1; ++i) {
        for (uint32_t j = 1; j < num_of_vertices + 1; ++j) {
            printf("%" PRIu32 " ", G[i][j] );
        }
        printf("\n");
    }


}
