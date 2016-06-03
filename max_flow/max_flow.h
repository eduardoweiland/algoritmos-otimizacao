#ifndef MAX_FLOW_H_
#define MAX_FLOW_H_

#include "graph.h"

int max_flow(const graph_t *const graph, const graph_node_t *const start, const graph_node_t *const end);
int max_flow_walk(const graph_node_t *const start, const graph_node_t *const end, graph_node_t **backtrace);

#endif /* MAX_FLOW_H_ */
