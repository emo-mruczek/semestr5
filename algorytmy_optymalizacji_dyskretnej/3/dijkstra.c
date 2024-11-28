// TODO:  stack limits
#include "sys/types.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

volatile bool debug = true;

typedef struct Node {
    uint64_t vertex;
    struct Node* next;
    struct Node* pre; // must be set NULL initially
    uint64_t d; // must be set MAX initially
    uint64_t w; // w(node, next)    
} Node;

typedef struct Graph {
    uint64_t num_of_vertices;
    uint64_t num_of_edges;
    Node** G;
} Graph;


int main(int argc, char* argv[]) {
    
    // for init vertex set d = 0
   

    

    return EXIT_SUCCESS;
}
