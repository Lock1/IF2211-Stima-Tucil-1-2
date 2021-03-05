// Graph
#include "graph.h"

char is_null_graph(Node graph[]) {
    for (int i = 0; i < MAX_NODE; i++)
        if (graph[i].value[0] != '\0')
            return 0;
    return 1;
}

int edge_length(addrNode array[]) {
    int i = 0;
    while (i < MAX_DEGREE && array[i] != -1)
        i++;
    return i;
}

void remove_edge(addrNode array[], addrNode val) {
    for (int i = 0; i < MAX_DEGREE; i++) {
        if (array[i] == val) {
            for (int j = i; j < (MAX_DEGREE - 1); j++)
                array[j] = array[j+1];
            break;
        }
    }
}
