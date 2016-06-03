#include <stdlib.h>

#include "graph.h"

void graph_init(graph_t *graph, const int node_count, const int max_edges)
{
    int i;

    graph->node_count = node_count;
    graph->nodes = (graph_node_t *) malloc(sizeof(graph_node_t) * node_count);

    for (i = 0; i < graph->node_count; ++i) {
        graph->nodes[i].number = i + 1;
        graph->nodes[i].edge_count = 0;
        graph->nodes[i].edges = (graph_edge_t *) malloc(sizeof(graph_edge_t) * max_edges);
    }
}

void graph_destroy(graph_t *graph)
{
    int i;

    for (i = 0; i < graph->node_count; ++i) {
        free(graph->nodes[i].edges);
    }

    free(graph->nodes);
}

