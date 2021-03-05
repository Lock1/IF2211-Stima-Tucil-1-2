// Graph
#ifndef _GRAPH_H
#define _GRAPH_H

#define MAX_VAL 32
#define MAX_DEGREE 128
#define MAX_NODE 128

typedef int addrNode;
typedef struct node {
    char value[MAX_VAL];
    addrNode in[MAX_DEGREE];
    addrNode out[MAX_DEGREE];
} Node;

#include <stdio.h>
#include <stdlib.h>

char is_null_graph(Node graph[]);

int edge_length(addrNode array[]);

void remove_edge(addrNode array[], addrNode val);

#endif
