#ifndef LISTAATUA_H
#define LISTAATUA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct listaAtu ListaAtu;

ListaAtu* criaListaAtu();

ListaAtu* insereListaAtu(ListaAtu* lista, double seg, int ori, int dest, double vel);

void liberaListaAtu(ListaAtu* lista);

int retornaOri(ListaAtu* lista);

int retornaDest(ListaAtu* lista);

double retornaSeg(ListaAtu* lista);

double retornaVelo(ListaAtu* lista);

ListaAtu* proxListaAtu(ListaAtu* lista);

void imprimeListaAtu(ListaAtu* lista);

#endif