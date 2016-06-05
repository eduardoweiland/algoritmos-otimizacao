#include <stdio.h>
#include <stdlib.h>

#include "max_flow.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))

int max_flow(graph_t *graph, graph_node_t *start, graph_node_t *end)
{
    int iteration = 1;

    do {
        printf("\n============================\n");
        printf("   Processando iteração %d\n", iteration++);
        printf("============================\n");
    } while (max_flow_walk(start, end, NULL) == 0);

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

int max_flow_walk(graph_node_t *start, graph_node_t *end, flow_trace_t *backtrace)
{
    graph_edge_t **candidates;
    graph_edge_t **next_candidate, *next_to_follow;
    flow_trace_t *trace;
    flow_trace_t step;
    int i, best, ret = 0;

    if (start == end) {
        printf("Chegou no destino transportando %d\n", backtrace->max);
        for (trace = backtrace; trace != NULL; trace = trace->previous) {
            trace->edge->available -= backtrace->max;
            trace->edge->used += backtrace->max;
        }
        return 0;
    }

    candidates = (graph_edge_t **) malloc(sizeof(graph_edge_t *) * (start->edge_count + 1));

    step.previous = backtrace;
    step.node = start;

    next_candidate = candidates;

    printf("\n");

    for (i = 0; i < start->edge_count; ++i) {
        for (trace = backtrace; (trace != NULL) && (trace->node != start->edges[i].target); trace = trace->previous) {
            /* NOOP */
        }

        if ((trace == NULL) && (start->edges[i].available > 0)) {
            // Nodo ainda não foi visitado e pode ser utilizado, armazena como candidato
            *next_candidate++ = &start->edges[i];
        }
    }

    *next_candidate = NULL;

    do {
        next_to_follow = NULL;

        for (i = 0; candidates[i] != NULL; ++i) {
            printf("Candidato: nodo %d com máximo de %d\n", candidates[i]->target->number, candidates[i]->available);
            if (((next_to_follow == NULL) && (candidates[i]->available > 0))
                    || ((next_to_follow != NULL) && (candidates[i]->available > next_to_follow->available))) {
                next_to_follow = candidates[i];
                best = i;
            }
        }

        if (next_to_follow == NULL) {
            printf("Sem caminho para seguir adiante, volta para nodo anterior\n");
            ret = 1;
            break;
        }

        // Remove o nodo que será seguido dos candidatos
        // Caso não seja encontrado um caminho, ele não será mais uma opção
        // Isso é feito movendo o candidato da última posição do vetor, sobrescrevendo o candidato que será testado agora
        if (--i == 0) {
            candidates[i] = NULL;
        }
        else {
            candidates[best] = candidates[i];
            candidates[i] = NULL;
        }

        step.edge = next_to_follow;
        if (backtrace == NULL) {
            step.max = next_to_follow->available;
        }
        else {
            step.max = MIN(backtrace->max, next_to_follow->available);
        }

        printf("WALK de %d para %d com máximo de %d\n", next_to_follow->source->number, next_to_follow->target->number, step.max);
    } while (max_flow_walk(next_to_follow->target, end, &step) != 0);

    free(candidates);
    return ret;
}

