#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "max_flow.h"

static void process_input(graph_t *graph);
static void print_connections(const graph_t *graph);

int main(int argc, char **argv)
{
    graph_t graph;
    int verbose = 0;

    if ((argc == 2) && (strncmp(argv[1], "-v", sizeof("-v")) == 0)) {
    	verbose = 1;
    	max_flow_set_verbose(1);
    }
    else if (argc > 1) {
        fprintf(stderr, "\n");
        fprintf(stderr, "  Parâmetros inválidos!\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "Uso: %s [-v]\n", argv[0]);
        fprintf(stderr, " -v     Ativa modo verbose (exibe detalhes da "
                        "execução do algoritmo)\n");
        return EXIT_FAILURE;
    }

    process_input(&graph);

    graph_node_t *start = &graph.nodes[0];
    graph_node_t *end = &graph.nodes[graph.node_count - 1];
    int max = max_flow(&graph, start, end);

    if (verbose) {
        printf("\n\n\n");
    }

    printf("Fluxo máximo entre %d e %d: %d\n", start->number, end->number, max);
    print_connections(&graph);

    graph_destroy(&graph);

    return EXIT_SUCCESS;
}

void process_input(graph_t *graph)
{
    int node_count, edge_count, max_edges;
    int edge_source, edge_target, edge_available;

    scanf("%d %d %d", &node_count, &edge_count, &max_edges);

    graph_init(graph, node_count, max_edges * 2);

    while (edge_count--) {
        scanf("%d %d %d", &edge_source, &edge_target, &edge_available);

        graph_node_t *source = &graph->nodes[edge_source - 1];
        graph_node_t *target = &graph->nodes[edge_target - 1];

        graph_add_edge(source, target, edge_available);
    }
}

void print_connections(const graph_t *graph)
{
    int i, j;

    printf("Estado final das conexões:\n");
    printf("ORIGEM\tVALOR\t\tVALOR\tDESTINO\n");

    for (i = 0; i < graph->node_count; ++i) {
        for (j = 0; j < graph->nodes[i].edge_count; ++j) {
            printf("%d\t%d\t-->\t%d\t%d\n",
                graph->nodes[i].edges[j].source->number,
                graph->nodes[i].edges[j].available,
                graph->nodes[i].edges[j].used,
                graph->nodes[i].edges[j].target->number
            );
        }
    }
}
