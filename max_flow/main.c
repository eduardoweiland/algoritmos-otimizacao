#include <stdio.h>
#include <stdlib.h>

#include "max_flow.h"

static void process_input(graph_t *graph);

int main(void)
{
    graph_t graph;

    process_input(&graph);

    graph_node_t *start = &graph.nodes[0];
    graph_node_t *end = &graph.nodes[graph.node_count - 1];
    int max = max_flow(&graph, start, end);

    printf("\n\n> Fluxo máximo entre %d e %d: %d\n", start->number, end->number, max);

    graph_destroy(&graph);

    return EXIT_SUCCESS;
}

void process_input(graph_t *graph)
{
    int node_count, edge_count, max_edges;
    int edge_source, edge_target, edge_available;

    scanf("%d %d %d", &node_count, &edge_count, &max_edges);

    graph_init(graph, node_count, max_edges);

    while (edge_count--) {
        scanf("%d %d %d", &edge_source, &edge_target, &edge_available);

        graph_node_t *source = &graph->nodes[edge_source - 1];
        graph_node_t *target = &graph->nodes[edge_target - 1];

        graph_add_edge(source, target, edge_available, 0);
    }
}

