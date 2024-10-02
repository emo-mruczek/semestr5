#include "inttypes.h"
#include "stdio.h"

volatile uint8_t is_directed;
volatile uint32_t num_of_vertices;
volatile uint32_t num_of_edges;
volatile uint8_t debug = 1;

int main() {

    if ( debug ) printf("(D)irected or (U)ndirected?\n");
    char temp;
    scanf("%c", &temp);
    //TODO: validation?
    is_directed = ( temp == 'D' ) ? 1 : 0;
    if ( debug ) printf("No. of vertices:\n");
    scanf("%d", &num_of_vertices);
    if ( debug ) printf("No. of edges\n");
    scanf("%d", &num_of_edges);
}
