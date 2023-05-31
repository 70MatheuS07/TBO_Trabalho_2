#ifndef TARESTA_H
#define TARESTA_H

#include "tAresta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INFINITO 99999999

typedef struct Aresta tAresta;

tAresta *CriaVetorArestas(int num);

void OrdenaVetArestas(tAresta *vet, int num);

int ComparaDistancia(const void *item1, const void *item2);

void LiberaVetArestas(tAresta *vet);

void PreencheVetorArestas(FILE *arq_entrada, tAresta *vet, int num, double velocidade_inicial);

int EncontrarMenorDistancia(double *distancias, bool *visitado, int numVertices);

void ImprimirCaminho(int *predecessores, int destino);

void AlgoritmoDijkstra(tAresta *grafo, int numVertices, int numArestas, int origem, int destino, double velocidadeMediaInicial);

#endif