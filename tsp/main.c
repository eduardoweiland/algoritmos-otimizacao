#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "path.h"

void process_input(graph_t *graph);
void print_path(const path_t *path);

int main(int argc, char **argv)
{
    graph_t graph;
    path_t best, candidate, best_candidate;
    int rot_size, rot_start;
    int verbose = 0;

    if ((argc == 2) && (strncmp(argv[1], "-v", sizeof("-v")) == 0)) {
        verbose = 1;
    }
    else if (argc > 1) {
        fprintf(stderr, "\n");
        fprintf(stderr, "  Parâmetros inválidos!\n");
        fprintf(stderr, "\n");
        fprintf(stderr, "Uso: %s [-v]\n", argv[0]);
        fprintf(stderr, " -v     Ativa modo verbose (exibe detalhes da "
                        "execução do algoritmo)\n");
        return EXIT_FAILURE;
    }

    process_input(&graph);
    graph_calculate_distances(&graph);

    path_init(&best, &graph);
    path_find_greedy(&best, 1);

    if (verbose) {
        printf("1o. caminho: ");
        print_path(&best);
    }

    for (rot_size = 2; rot_size < graph.node_count; ++rot_size) {
        if (verbose) {
            printf("\n\n===== Trocando caminhos com tamanho %2d =====\n", rot_size);
        }

        path_copy(&best_candidate, &best);

        for (rot_start = 1; rot_start <= graph.node_count - rot_size; ++rot_start) {
            path_copy(&candidate, &best);
            path_rotate(&candidate, rot_size, rot_start);
            if (verbose) {
                printf("Troca # %3d: ", rot_start);
                print_path(&candidate);
            }

            if (candidate.distance < best_candidate.distance) {
                path_copy(&best_candidate, &candidate);
            }

            path_destroy(&candidate);
        }

        if (best_candidate.distance < best.distance) {
            path_copy(&best, &best_candidate);
        }

        if (verbose) {
            printf("\n   MELHOR  : ");
            print_path(&best);
        }
    }

    if (verbose) {
        printf("\n============================================\n");
    }

    printf("Melhor caminho encontrado:\n");
    print_path(&best);

    path_destroy(&best);
    path_destroy(&best_candidate);
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

    printf(" ->  Distância: %lf\n", path->distance);
}
