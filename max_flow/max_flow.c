#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int source;
    int target;
    int available;
    int used;
} graph_edge_t;

typedef struct {
    int number;
    int edge_count;
    graph_edge_t *edges;
} graph_node_t;

typedef struct {
    int node_count;
    graph_node_t *nodes;
} graph_t;

void process_input(graph_t *graph);
void destroy_graph(graph_t *graph);
void init_nodes(graph_t *graph, const int max_edges);
void max_flow(const graph_t *const graph, const graph_node_t *const start, const graph_node_t *const end);

int main(void)
{
    graph_t graph;

    process_input(&graph);

    graph_node_t *start = &graph.nodes[0];
    graph_node_t *end = &graph.nodes[graph.node_count];
    max_flow(&graph, start, end);

    destroy_graph(&graph);

    return EXIT_SUCCESS;
}

void process_input(graph_t *graph)
{
    int node_count, edge_count, max_edges;
    int edge_source, edge_target, edge_available;

    scanf("%d %d %d", &node_count, &edge_count, &max_edges);

    printf("lendo %d nodos e %d arestas, máx. %d arestas por nodo\n", node_count, edge_count, max_edges);

    graph->nodes = (graph_node_t *) malloc(sizeof(graph_node_t) * node_count);

    graph->node_count = node_count;
    init_nodes(graph, max_edges);

    while (edge_count--) {
        scanf("%d %d %d", &edge_source, &edge_target, &edge_available);

        graph_node_t *source = &graph->nodes[edge_source - 1];

        printf(
                "Aresta #%d entre %d e %d com disponibilidade de %d\n",
                source->edge_count + 1,
                edge_source,
                edge_target,
                edge_available
        );

        source->edges[source->edge_count].source = edge_source;
        source->edges[source->edge_count].target = edge_target;
        source->edges[source->edge_count].available = edge_available;
        source->edges[source->edge_count].used = 0;
        source->edge_count++;
    }
}

void destroy_graph(graph_t *graph)
{
    int i;

    for (i = 0; i < graph->node_count; ++i) {
        free(graph->nodes[i].edges);
    }

    free(graph->nodes);
}

void init_nodes(graph_t *graph, const int max_edges)
{
    int i;

    for (i = 0; i < graph->node_count; ++i) {
        graph->nodes[i].number = i + 1;
        graph->nodes[i].edge_count = 0;
        graph->nodes[i].edges = (graph_edge_t *) malloc(sizeof(graph_edge_t) * max_edges);
    }
}

void max_flow(const graph_t *const graph, const graph_node_t *const start, const graph_node_t *const end)
{
    //
}
