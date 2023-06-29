#ifndef LISTAINT_H
#define LISTAINT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct listaInt ListaInt;

ListaInt* criaListaInt();

ListaInt* insereListaInt(ListaInt* lista, int p);

void imprimeListaInt(ListaInt* lista, FILE* saida);

void liberaListaInt(ListaInt* lista);

int proxIntLista(ListaInt* lista);

#endif