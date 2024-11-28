// TODO:  stack limits
// TODO: error handling?
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

static uint64_t num_of_vertices;
static uint64_t num_of_edges;
static Node** G;

static const char* data = NULL;
static const char* in = NULL;
static const char* res = NULL;

bool get_args(int argc, char* argv[]);
void process_input(const char* filename);
void add_edge(uint64_t v, uint64_t u, uint64_t c,  Node** Graph);
void print_graph(Node** Graph);
void cleanup(void);

int main(int argc, char* argv[]) {
    //TODO: graph allocation

    if (!(get_args(argc, argv))) exit(EXIT_FAILURE);
    process_input(data);

    if (debug) {
        printf("\nInput graph:\n");
        print_graph(G);
        printf("\n");
    }

    cleanup();

    exit(EXIT_SUCCESS);
}

void cleanup(void) {
    for (uint64_t i = 1; i <= num_of_vertices; ++i) {
        Node* current = G[i];

        while (current) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }

    free(G);
}

void print_graph(Node** Graph) {
    for ( uint64_t i = 1; i < num_of_vertices + 1; ++i ) {
        Node* temp = Graph[i];
        printf("\n %" PRIu64 "\n\t", i);

        while ( temp ) {
            printf("(%" PRIu64 ", %" PRIu64 ") ", temp->vertex, temp->w);
            temp = temp->next;
        }
    }

    printf("\n");
}

void add_edge(uint64_t v, uint64_t u, uint64_t c,  Node** Graph) {
    Node* new = (Node*)malloc(sizeof(Node));
    new->vertex = u;
    new->next = Graph[v];
    new->w = c;
    Graph[v] = new;
}

void process_input(const char* filename) {
    FILE* file = fopen(filename, "r");

    if (!file) exit(EXIT_FAILURE);

    // TODO: size?
    char buf[256];

    // TODO: validation?

    while (fgets(buf, sizeof buf, file) != NULL) {
        if (debug) printf("%s\n", buf);
        char b = buf[0];
        uint64_t src = 0;
        uint64_t dst = 0;
        uint64_t cst = 0;

        switch (b) {
            case 'c':
                continue;

            case 'p':
                //TODO: eeee
                sscanf(buf, "p sp %" SCNu64 " %" SCNu64, &num_of_vertices, &num_of_edges);
                G = (Node**)malloc((num_of_vertices + 1) * sizeof(Node*));
                for (uint32_t i = 1; i <= num_of_vertices; ++i) G[i] = NULL;
                break;

            case 'a':
                sscanf(buf, "a %" SCNu64 " %" SCNu64 " %" SCNu64, &src, &dst, &cst);
                add_edge(src, dst, cst, G);
                break;
        }
    }
 
    if (feof(file)) if (debug) printf("End of file reached\n");
}

bool get_args(int argc, char* argv[]) {

    // TODO: more checks
    // TODO: stderr?

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
                if (debug) printf("Option ss with value '%s'\n", optarg);
                in = optarg;
                is_in = true;
                break;
            case 'o':
                if (debug) printf("Option oss with value '%s'\n", optarg);
                res = optarg;
                is_res = true;
                break;
            case 'p':
                if (debug) printf("Option p2p with value '%s'\n", optarg);
                in = optarg;
                is_in = true;
                break;
            case 'r':
                if (debug) printf("Option op2p with value '%s'\n", optarg);
                res = optarg;
                is_res = true;
                break;
            case 'd':
                if (debug) printf("Option d with value '%s'\n", optarg);
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
        return false;
    }

    return true;
}
