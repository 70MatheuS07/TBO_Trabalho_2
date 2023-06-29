#include "ListaInt.h"

struct listaInt{
    int p;
    ListaInt* prox;
};

ListaInt* criaListaInt(){
    return NULL;
}

ListaInt* insereListaInt(ListaInt* lista, int p){
    ListaInt* nova = malloc(sizeof(ListaInt));
    nova->p = p;
    nova->prox = lista;

    return nova;
}

void imprimeListaInt(ListaInt* lista, FILE* saida){
    int cont = 0;
    for(ListaInt* l = lista; l!=NULL; l = l->prox){
        fprintf(saida, "%d", l->p);
        if(l->prox != NULL)
        fprintf(saida, ";");
    }
    fprintf(saida,"\n");
}

void liberaListaInt(ListaInt* lista){
    ListaInt* p = lista;
    ListaInt* t;

    while(p){
        t = p->prox;
        free(p);
        p = t;
    }
}
int proxIntLista(ListaInt* lista){
    if(lista->prox!=NULL)
    return lista->prox->p;

    return 1;
}
