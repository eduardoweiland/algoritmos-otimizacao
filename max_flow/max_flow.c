#include <stdio.h>
#include <stdlib.h>

typedef struct graph_edge_st {
    struct graph_node_st *source;
    struct graph_node_st *target;
    int available;
    int used;
} graph_edge_t;

typedef struct graph_node_st {
    int number;
    int edge_count;
    graph_edge_t *edges;
} graph_node_t;

typedef struct graph_st {
    int node_count;
    graph_node_t *nodes;
} graph_t;

void process_input(graph_t *graph);
void destroy_graph(graph_t *graph);
void init_nodes(graph_t *graph, const int max_edges);
int max_flow(const graph_t *const graph, const graph_node_t *const start, const graph_node_t *const end);
int max_flow_walk(const graph_node_t *const start, const graph_node_t *const end, graph_node_t **backtrace);

int main(void)
{
    graph_t graph;

    process_input(&graph);

    graph_node_t *start = &graph.nodes[0];
    graph_node_t *end = &graph.nodes[graph.node_count - 1];
    int max = max_flow(&graph, start, end);

    printf("\n\n> Fluxo máximo entre %d e %d: %d\n", start->number, end->number, max);

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

        source->edges[source->edge_count].source = &graph->nodes[edge_source - 1];
        source->edges[source->edge_count].target = &graph->nodes[edge_target - 1];
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

int max_flow(const graph_t *const graph, const graph_node_t *const start, const graph_node_t *const end)
{
    int iteration = 1;
    graph_node_t **backtrace = (graph_node_t **) malloc(sizeof(graph_node_t *) * graph->node_count);

    do {
        *backtrace = NULL;
        printf("Processando iteração %d\n", iteration++);
    } while (max_flow_walk(start, end, backtrace) == 0);

    int max = 0, i, j;
    for (i = 0; i < graph->node_count; ++i) {
        for (j = 0; j < graph->nodes[i].edge_count; ++j) {
            if (graph->nodes[i].edges[j].target == end) {
                max += graph->nodes[i].edges[j].used;
            }
        }
    }

    return max;
}

int max_flow_walk(const graph_node_t *const start, const graph_node_t *const end, graph_node_t **backtrace)
{
    graph_edge_t *next = NULL;
    graph_node_t **trace;
    int i;

    for (i = 0; i < start->edge_count; ++i) {
        trace = backtrace;

        while ((*trace != start->edges[i].target) && (*(++trace) != NULL)) {
            /* NOOP */
        }

        if ((*trace == NULL) && (((next != NULL) && (start->edges[i].available > next->available)) || ((next == NULL) && (start->edges[i].available > 0)))) {
            next = &start->edges[i];
        }
    }

    if (next == NULL) {
        return 1;
    }

    if (next->target == end) {
        return 0;
    }

    trace = backtrace;
    while(*(++trace) != NULL) {
        /* NOOP */
    }
    *trace = next->source;

    printf("WALK de %d para %d com máximo de %d\n", next->source->number, next->target->number, next->available);

    return max_flow_walk(next->target, end, backtrace);
}

