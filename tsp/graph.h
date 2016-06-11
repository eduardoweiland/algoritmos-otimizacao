#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct node_st
{
    int number;
    double pos_x;
    double pos_y;
} node_t;

typedef struct graph_st
{
    node_t *nodes;
    int node_count;
    double **distances;
} graph_t;

void graph_init(graph_t *graph, const int node_count);
void graph_destroy(graph_t *graph);
void graph_calculate_distances(graph_t *graph);
double graph_get_distance(const graph_t *graph, const node_t *src, const node_t *dest);

#endif /* GRAPH_H_ */
