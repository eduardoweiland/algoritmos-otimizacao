#ifndef GRAPH_H_
#define GRAPH_H_

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


void graph_init(graph_t *graph, const int node_count, const int max_edges);
void graph_destroy(graph_t *graph);

#endif /*  GRAPH_H_ */
