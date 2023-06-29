#ifndef LISTAADJ_H
#define LISTAADJ_H

#include <stdio.h>
#include <stdlib.h>
#include "Adj.h"

typedef struct listaAdj ListaAdj;

ListaAdj* criaListaAjd();

ListaAdj* insereListaAjd(ListaAdj* lista, int vertice, double peso, double velocidade);

void imprimeListaAdj(ListaAdj* lista);

void liberaListaAdj(ListaAdj* lista);

ListaAdj* proxListaAdj(ListaAdj* lista);

int retornaListaVertice(ListaAdj* lista);

double retornaListaPeso(ListaAdj* lista);

Adj* retornaAdjLista(ListaAdj* lista);

void atualizarVelVertice(ListaAdj* lista, int dest, double velocidade);


#endif