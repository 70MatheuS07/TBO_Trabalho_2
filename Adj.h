#ifndef ADJ_H
#define ADJ_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct adj Adj;

Adj* criaAjd(int id, double peso, double velocidade);

void imprimeAdj(Adj* a);

void liberaAdj(Adj* a);

int idAdj(Adj* a);

double valueAdj(Adj* a);

double velocidadeAdj(Adj* a);

void mudarVelAdj(Adj* a, double velocidade);

#endif