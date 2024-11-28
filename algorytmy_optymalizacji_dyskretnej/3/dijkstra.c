// TODO:  stack limits
#include "sys/types.h"
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h> 

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

    // TODO: more checks
    // TODO: stderr?
    
    const char* data = NULL;
    const char* in = NULL;
    const char* res = NULL;

    bool is_data = false;
    bool is_in = false;
    bool is_res = false;

    static struct option long_options[] = {
            {"ss",  required_argument,  0,  's' }, // sources from a file
            {"oss",  required_argument, 0,  'o' }, // returned file
            {"p2p", required_argument,  0,  'p' }, // shortest path between pairs
            {"op2p",  required_argument, 0, 'r'}, // returned file
            {"d", required_argument, 0, 'd'},
            {0,         0,                 0,  0 }
    };

    int c;
    while (( c = getopt_long_only(argc, argv, "s:o:p:r:d:", long_options, NULL)) != -1) {
      

        switch (c) {
            case 's':
                printf("Option ss with value '%s'\n", optarg);
                in = optarg;
                is_in = true;
                break;
            case 'o':
                printf("Option oss with value '%s'\n", optarg);
                res = optarg;
                is_res = true;
                break;
            case 'p':
                printf("Option p2p with value '%s'\n", optarg);
                in = optarg;
                is_in = true;
                break;
            case 'r':
                printf("Option op2p with value '%s'\n", optarg);
                res = optarg;
                is_res = true;
                break;
            case 'd':
                printf("Option d with value '%s'\n", optarg);
                data = optarg;
                is_data = true;
                break;
            case '?':
                printf("unknown option/missing argument\n");
                break;

            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }

    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
    }

    if (!(is_res && is_in && is_data)) {
        printf("Not enough arguments!\n");
        return(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
