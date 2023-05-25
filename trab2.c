#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAresta.h"

int main(int argc, char *argv[])
{
    char *entrada = strdup(argv[1]);
    char *saida = strdup(argv[2]);

    int num_vertices, num_arestas;

    FILE *arq_entrada = fopen(entrada, "r");

    fscanf(arq_entrada, "%d;%d\n", &num_vertices, &num_arestas);

    int noh_origem, noh_destino;

    fscanf(arq_entrada, "%d;%d\n", &noh_origem, &noh_destino);

    double velocidade_incial;

    fscanf(arq_entrada, "%lf\n", &velocidade_incial);

    tAresta *vet_arestas = CriaVetorArestas(num_arestas);

    PreencheVetorArestas(arq_entrada, vet_arestas, num_arestas, velocidade_incial);

    return 0;
}