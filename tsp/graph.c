#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "graph.h"

static double calculate_distance(const node_t *a, const node_t *b);

void graph_init(graph_t *graph, const int node_count)
{
    assert(graph != NULL);

    int i;

    graph->node_count = node_count;
    graph->nodes = (node_t *) malloc(sizeof(node_t) * node_count);
    graph->distances = (double **) malloc(sizeof(double **) * node_count);

    for (i = 0; i < node_count; ++i) {
        graph->distances[i] = (double *) malloc(sizeof(double *) * node_count);
    }
}

void graph_destroy(graph_t *graph)
{
    assert(graph != NULL);
    assert(graph->nodes != NULL);
    assert(graph->distances != NULL);

    int i;

    for (i = 0; i < graph->node_count; ++i) {
        free(graph->distances[i]);
    }

    free(graph->distances);
    free(graph->nodes);
}

void graph_calculate_distances(graph_t *graph)
{
    assert(graph != NULL);
    assert(graph->nodes != NULL);
    assert(graph->node_count > 0);
    assert(graph->distances != NULL);

    int i, j;

    for (i = 0; i < graph->node_count; ++i) {
        for (j = 0; j < graph->node_count; ++j) {
            if (i == j) {
                graph->distances[i][j] = INFINITY;
            }
            else {
                graph->distances[i][j] = calculate_distance(&graph->nodes[i], &graph->nodes[j]);
            }
        }
    }
}

double graph_get_distance(const graph_t *graph, const node_t *src, const node_t *dest)
{
    assert(graph != NULL);
    assert(graph->nodes != NULL);
    assert(graph->node_count > 0);
    assert(graph->distances != NULL);
    assert(src != NULL);
    assert((src->number > 0) && (src->number <= graph->node_count));
    assert(dest != NULL);
    assert((dest->number > 0) && (dest->number <= graph->node_count));

    return graph->distances[src->number - 1][dest->number - 1];
}

double calculate_distance(const node_t *a, const node_t *b)
{
    assert((a != NULL) && (b != NULL));

    return sqrt(pow(a->pos_x - b->pos_x, 2) + pow(a->pos_y - b->pos_y, 2));
}
