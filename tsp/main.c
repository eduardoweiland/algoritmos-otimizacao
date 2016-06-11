#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "path.h"

void process_input(graph_t *graph);
void print_path(const path_t *path);

int main(void)
{
    graph_t graph;

    process_input(&graph);
    graph_calculate_distances(&graph);

    path_t path, rotate1;
    path_init(&path, &graph);
    path_find_greedy(&path, 1);

    printf("Caminho inicial: ");
    print_path(&path);

    // TODO: gerar todas possibilidades e manter sempre a melhor
    printf("\n");
    for (int i = 1; i < 37; ++i) {
        path_copy(&rotate1, &path);
        path_rotate(&rotate1, 2, i);
        printf("Rotação #%02d    : ", i);
        print_path(&rotate1);
        path_destroy(&rotate1);
    }

    printf("\n");
    for (int i = 1; i < 36; ++i) {
        path_copy(&rotate1, &path);
        path_rotate(&rotate1, 3, i);
        printf("Rotação #%02d    : ", i);
        print_path(&rotate1);
        path_destroy(&rotate1);
    }

    path_destroy(&path);
    graph_destroy(&graph);

    return EXIT_SUCCESS;
}

void process_input(graph_t *graph)
{
    assert(graph != NULL);

    int node_count, i;
    node_t *node;

    scanf("%d", &node_count);

    graph_init(graph, node_count);

    for (i = 0; i < node_count; ++i) {
        node = &graph->nodes[i];
        scanf("%d %lf %lf", &node->number, &node->pos_x, &node->pos_y);
    }
}

void print_path(const path_t *path)
{
    assert(path != NULL);
    assert(path->graph != NULL);
    assert(path->nodes != NULL);

    int i;

    for (i = 0; i <= path->graph->node_count; ++i) {
        printf("%3d ", path->nodes[i]->number);
    }

    printf("-> Distância: %.2lf\n", path->distance);
}
