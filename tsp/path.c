#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#include "path.h"

#define PATH_NODE_COUNT(graph) ((graph)->node_count + 1)
#define PATH_NODES_SIZE(graph) (sizeof(node_t *) * PATH_NODE_COUNT(graph))

static int path_contains_node(const path_t *path, const node_t *node);
static node_t* path_closest_node(const path_t *path, const int origin);

void path_init(path_t *path, graph_t *graph)
{
    assert(path != NULL);
    assert(graph != NULL);

    path->nodes = (node_t **) malloc(PATH_NODES_SIZE(graph));
    path->distance = 0;
    path->graph = graph;
}

void path_copy(path_t *dest, const path_t *src)
{
    assert(src != NULL);
    assert(dest != NULL);

    dest->graph = src->graph;
    dest->distance = src->distance;
    dest->nodes = (node_t **) malloc(PATH_NODES_SIZE(src->graph));
    memcpy(dest->nodes, src->nodes, PATH_NODES_SIZE(src->graph));
}

void path_destroy(path_t *path)
{
    assert(path != NULL);

    free(path->nodes);
}

void path_find_greedy(path_t *path, const int origin)
{
    assert(path != NULL);
    assert(path->graph != NULL);
    assert((origin > 0) && (origin <= path->graph->node_count));

    int i;
    node_t *previous = &path->graph->nodes[origin - 1];
    node_t *next;

    for (i = 0; i < path->graph->node_count; ++i) {
        path->nodes[i] = previous;
        next = path_closest_node(path, previous->number);

        if (next == NULL) {
            ++i;
            break;
        }

        path->distance += graph_get_distance(path->graph, previous, next);
        previous = next;
    }

    // Se encontrou um caminho válido, adiciona o nodo de volta à origem:
    if (i == path->graph->node_count) {
        path->nodes[i] = &path->graph->nodes[origin - 1];
        path->distance += graph_get_distance(path->graph, previous, path->nodes[i]);
    }
}

// start = 0-indexed
void path_rotate(path_t *path, const int size, const int start)
{
    assert(path != NULL);
    assert(path->graph != NULL);
    assert((size >= 2) && (size <= path->graph->node_count - 1));
    assert((start >= 1) && (start <= path->graph->node_count - size));

    int i, j;
    node_t *tmp;

    for (i = start, j = start + size - 1; i < j; ++i, --j) {
        tmp = path->nodes[i];
        path->nodes[i] = path->nodes[j];
        path->nodes[j] = tmp;
    }

    path->distance = 0;
    for (i = 1; i < PATH_NODE_COUNT(path->graph); ++i) {
        path->distance += graph_get_distance(path->graph, path->nodes[i - 1], path->nodes[i]);
    }
}

node_t* path_closest_node(const path_t *path, const int origin)
{
    assert(path->graph != NULL);
    assert((origin > 0) && (origin <= path->graph->node_count));
    assert(path != NULL);

    int i;
    node_t *closest = NULL;
    double *distances = path->graph->distances[origin - 1];
    double min_distance = INFINITY;

    for (i = 0; i < path->graph->node_count; ++i) {
        if ((distances[i] < min_distance) && !path_contains_node(path, &path->graph->nodes[i])) {
            closest = &path->graph->nodes[i];
            min_distance = distances[i];
        }
    }

    return closest;
}

int path_contains_node(const path_t *path, const node_t *node)
{
    assert(path != NULL);
    assert(path->nodes != NULL);
    assert(path->graph != NULL);
    assert(node != NULL);

    int i;

    for (i = 0; i < PATH_NODE_COUNT(path->graph); ++i) {
        if (path->nodes[i] == node) {
            return 1;
        }
    }

    return 0;
}
