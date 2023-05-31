#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tAresta.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Erro: argumentos de linha de comando ausentes.\n");
        printf("Uso: ./trab2 <arquivo_entrada> <arquivo_saida>\n");
        return 1;
    }

    char *entrada = malloc(strlen(argv[1]) + 1);
    strcpy(entrada, argv[1]);

    char *saida = malloc(strlen(argv[2]) + 1);
    strcpy(saida, argv[2]);

    int num_vertices, num_arestas;

    FILE *arq_entrada = fopen(entrada, "r");

    fscanf(arq_entrada, "%d;%d\n", &num_vertices, &num_arestas);

    int noh_origem, noh_destino;

    fscanf(arq_entrada, "%d;%d\n", &noh_origem, &noh_destino);

    double velocidade_inicial;

    fscanf(arq_entrada, "%lf\n", &velocidade_inicial);

    tAresta *vet_arestas = CriaVetorArestas(num_arestas);

    PreencheVetorArestas(arq_entrada, vet_arestas, num_arestas, velocidade_inicial);

    AlgoritmoDijkstra(vet_arestas, num_vertices, num_arestas, noh_origem, noh_destino, velocidade_inicial);

    fclose(arq_entrada);

    return 0;
}