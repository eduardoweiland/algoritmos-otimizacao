#include <stdio.h>
#include <stdlib.h>

#include "max_flow.h"

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

