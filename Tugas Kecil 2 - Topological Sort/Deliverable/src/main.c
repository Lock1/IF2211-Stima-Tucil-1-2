// Tugas Kecil 2

#include "main.h"

int main(int argc, char const *argv[]) {
    // Argument Checking
    if (argc < 2) {
        fprintf(stderr, "Usage : ./w <filename>\n");
        exit(1);
    }

    // Graph Initialize
    Node acyclic_graph[MAX_NODE];
    for (int i = 0; i < MAX_NODE; i++) {
        for (int j = 0; j < MAX_DEGREE; j++) {
            acyclic_graph[i].in[j] = acyclic_graph[i].out[j] = -1;
            acyclic_graph[i].value[0] = '\0';
        }
    }

    // File processing
    // Warning : Assuming test case written consistently with space and newline
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error : Failed to read file \"%s\"\n", argv[1]);
        exit(1);
    }
    printf(START_1, argv[1]);
    puts("--     Input      --");

    char buffer[BUFFER_SIZE];
    int idx = 0;
    // Generate title list
    while (fgets(buffer, BUFFER_SIZE, file)) {
        char title[BUFFER_SIZE];
        printf("%s", buffer);
        if (sscanf(buffer, "%s", title) == 0) {
            fprintf(stderr, "Empty line detected\n");
            exit(1);
        }
        title[strlen(title) - 1] = '\0'; // Cut comma or dot
        strcpy(acyclic_graph[idx].value, title);
        idx++;
    }

    // Forming prerequiste / graph edge list
    file = fopen(argv[1], "r");
    idx = 0;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        int in_idx = 0, last_idx = get_next_stop_index(buffer);
        char prereq[BUFFER_SIZE];
        while (sscanf((buffer+last_idx), "%s", prereq)) {
            if (prereq[0] != '.') {
                prereq[strlen(prereq) - 1] = '\0';
                for (int i = 0; i < MAX_NODE; i++) {
                    if (!strcmp(prereq, acyclic_graph[i].value)) {
                        acyclic_graph[idx].in[in_idx] = i;
                        for (int j = 0; j < MAX_DEGREE; j++) {
                            if (acyclic_graph[i].out[j] == -1) {
                                acyclic_graph[i].out[j] = idx;
                                break;
                            }
                        }
                        in_idx++;
                    }
                }
            }
            else
                break;
            last_idx += get_next_stop_index(buffer + last_idx);
        }
        idx++;
    }

    // Printing all node in graph
    puts("\n --  Node values  --");
    puts(NODE_TABLE_1);
    puts(NODE_TABLE_2);
    puts(NODE_TABLE_3);
    int node_count = 0;
    for (int i = 0; i < MAX_NODE; i++) {
        if (acyclic_graph[i].value[0] != '\0') {
            char in_buffer[BUFFER_SIZE], out_buffer[BUFFER_SIZE], temp_buffer[BUFFER_SIZE];
            in_buffer[0] = '\0';
            for (int j = 0; j < edge_length(acyclic_graph[i].in); j++) {
                if (j != edge_length(acyclic_graph[i].in) - 1)
                    sprintf(temp_buffer,"%d, ", acyclic_graph[i].in[j]);
                else
                    sprintf(temp_buffer,"%d", acyclic_graph[i].in[j]);
                strcat(in_buffer, temp_buffer);
            }
            out_buffer[0] = '\0';
            for (int j = 0; j < edge_length(acyclic_graph[i].out); j++) {
                if (j != edge_length(acyclic_graph[i].out) - 1)
                    sprintf(temp_buffer, "%d, ", acyclic_graph[i].out[j]);
                else
                    sprintf(temp_buffer, "%d", acyclic_graph[i].out[j]);
                strcat(out_buffer, temp_buffer);
            }
            printf(NODE_TABLE_PROC, i, acyclic_graph[i].value, in_buffer, out_buffer);
            node_count++;
        }
    }
    puts(NODE_TABLE_4);

    // Adjecency matrix
    puts("\n -- Adjacency Matrix --");
    char border[BUFFER_SIZE];
    border[0] = '\0';
    strcat(border,"\u250E");
    for (int i = 0; i < node_count; i++)
        strcat(border, "  ");
    strcat(border," \u2512");
    printf("%s\n", border);
    for (int i = 0; i < node_count; i++) {
        char row_buffer[BUFFER_SIZE], temp_element[BUFFER_SIZE];
        row_buffer[0] = '\0';
        for (int j = 0; j < node_count; j++) {
            char match_not_found = 1;
            for (int k = 0; k < edge_length(acyclic_graph[i].out); k++) {
                if (acyclic_graph[i].out[k] == j) {
                    sprintf(temp_element, "\33[92m %d\33\[m", 1);
                    match_not_found = 0;
                    break;
                }
            }

            if (match_not_found)
                sprintf(temp_element, "\33[91m %d\33\[m", 0);
            strcat(row_buffer, temp_element);
        }
        printf("\u2503%s \u2503\n", row_buffer);
    }
    border[0] = '\0';
    strcat(border,"\u2516");
    for (int i = 0; i < node_count; i++)
        strcat(border, "  ");
    strcat(border," \u251A");
    printf("%s\n", border);

    // Sort
    struct timespec start, stop;
    puts("\n --    Output     --");
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int iteration = 1;
    while (!is_null_graph(acyclic_graph)) {
        printf("Semester %3d : ", iteration);

        // Finding all zero degree in node address
        addrNode zero_inbound_addresses[MAX_DEGREE];
        for (int i = 0; i < MAX_DEGREE; i++)
            zero_inbound_addresses[i] = -1;
        int addr_idx = 0;
        for (int i = 0; i < MAX_NODE; i++) {
            if (acyclic_graph[i].value[0] != '\0' && edge_length(acyclic_graph[i].in) == 0)
                zero_inbound_addresses[addr_idx++] = i;
        }

        // Printing
        char is_first_print = 1;
        for (int i = 0; i < MAX_DEGREE; i++) {
            if (zero_inbound_addresses[i] != -1) {
                int zero_idx = zero_inbound_addresses[i];
                if (is_first_print) {
                    printf("%s", acyclic_graph[zero_idx].value);
                    is_first_print = 0;
                }
                else
                    printf(", %s", acyclic_graph[zero_idx].value);
                topological_sort(acyclic_graph, zero_idx);
            }
        }
        printf("\n");
        iteration++;
    }

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    double result = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1e9;

    puts("\n --     Data      --");
    printf("Time elapsed : %f\n\n\n\n", result);
    puts(END_1);

    return 0;
}

int get_next_stop_index(char* val) {
    int i = 1;
    while (val[i] != ' ' && val[i] != '.' && val[i] != '\0')
        i++;
    return i;
}

void topological_sort(Node graph[], addrNode addr) {
    Node selected_node = graph[addr];
    for (int i = 0; i < edge_length(selected_node.out); i++) {
        addrNode receiver_node_addr = selected_node.out[i];
        remove_edge(graph[receiver_node_addr].in, addr);
    }
    graph[addr].value[0] = '\0';
}
