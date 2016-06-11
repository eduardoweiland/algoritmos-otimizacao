#ifndef PATH_H_
#define PATH_H_

#include "graph.h"

typedef struct path_st
{
    node_t **nodes;
    double distance;
    graph_t *graph;
} path_t;

void path_init(path_t *path, graph_t *graph);
void path_copy(path_t *dest, const path_t *src);
void path_destroy(path_t *path);

void path_find_greedy(path_t *path, const int origin);
void path_rotate(path_t *path, const int size, const int start);

#endif /* PATH_H_ */
