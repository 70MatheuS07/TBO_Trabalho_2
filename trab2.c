#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Grafo.h"
#include "Adj.h"
#include "ListaAdj.h"
#include "ListaInt.h"
#define METROS_SEG 3.6

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

    int num_vertices = 0, num_arestas = 0;

    FILE *arq_entrada = fopen(entrada, "r");
    FILE *arq_saida = fopen(saida, "w");

    fscanf(arq_entrada, "%d;%d\n", &num_vertices, &num_arestas);

    Grafo* grafo = criaGrafo(num_vertices, num_arestas);

    int noh_origem, noh_destino;

    fscanf(arq_entrada, "%d;%d\n", &noh_origem, &noh_destino);

    double velocidade_inicial;

    fscanf(arq_entrada, "%lf\n", &velocidade_inicial);
    //adciona as arestas na ListaAdjs e as atualizaçoes de velocidade na ListaAtu
    preencheGrafo(grafo, arq_entrada, velocidade_inicial/METROS_SEG);
    
    int* predecessores = malloc((retornaNumVertices(grafo)+1)*sizeof(int));
    executaDijstra(grafo, predecessores, noh_origem, noh_destino, arq_saida);

    liberaGrafo(grafo);
    free(entrada);
    free(saida);
    free(predecessores);
    fclose(arq_entrada);
    fclose(arq_saida);

    return 0;
}