#ifndef MAX_FLOW_H_
#define MAX_FLOW_H_

#include "graph.h"

typedef struct flow_trace_st {
    struct flow_trace_st *previous;
    graph_edge_t *edge; /** Aresta utilizada para percorrer caminho entre previous->node e node */
    graph_node_t *node; /** Nodo atual */
    int max; /** Valor máximo que pode ser transportado por todo o caminho (mínimo entre todas arestas percorridas) */
} flow_trace_t;

int max_flow(graph_t *graph, graph_node_t *start, graph_node_t *end);
int max_flow_walk(graph_node_t *start, graph_node_t *end, flow_trace_t *backtrace);

#endif /* MAX_FLOW_H_ */
