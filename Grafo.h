#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "Adj.h"
#include "ListaAdj.h"
#include "PQ.h"
#include "ListaAtu.h"
#include "ListaInt.h"

typedef struct grafo Grafo;

Grafo* criaGrafo(int v, int a);

void ImprimeGrafo(Grafo* grafo);

void liberaGrafo(Grafo* grafo);

void preencheGrafo(Grafo* grafo, FILE* arq_entrada, double velocidadeInicial);

void executaDijstra(Grafo* grafo, int* p, int s, int f, FILE* saida);

void relaxamento(Heap* fila, int* p, ListaAdj* s);

int retornaNumVertices(Grafo* grafo);

void atualizarVel(int vertice, double tempoAtual, Grafo* grafo);

void imprimeTempoFormato(double seg, FILE* saida);

#endif