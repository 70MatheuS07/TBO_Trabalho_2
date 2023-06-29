#include "Adj.h"

struct adj{

    int id;
    double velocidade;
    double value;
};

Adj* criaAjd(int id, double peso, double velocidade){
    Adj* novo = malloc(sizeof(Adj));
    novo->id = id;
    novo->value = peso;
    novo->velocidade = velocidade;
    return novo;
}

void imprimeAdj(Adj* a){
    if(a->value == 0)
        printf("v%d: ", a->id);
    else
        printf("v%d(%.2lf) ",a->id, a->value/a->velocidade);
}

void liberaAdj(Adj* a){
    free(a);
}

int idAdj(Adj* a){
    return a->id;
}

double valueAdj(Adj* a){
    return a->value;
}

double velocidadeAdj(Adj* a){
    return a->velocidade;
}

void mudarVelAdj(Adj* a, double velocidade){
    a->velocidade = velocidade;
}