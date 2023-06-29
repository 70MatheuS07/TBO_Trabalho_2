#include "ListaAtu.h"

struct listaAtu{
    double seg;
    double vel;
    int ori;
    int dest;
    ListaAtu* prox;
};

ListaAtu* criaListaAtu(){
    return NULL;
}

ListaAtu* insereListaAtu(ListaAtu* lista, double seg, int ori, int dest, double vel){
    ListaAtu* nova = malloc(sizeof(ListaAtu));
    nova->seg = seg;
    nova->ori = ori;
    nova->dest = dest;
    nova->vel = vel;
    nova->prox = NULL;
  
    ListaAtu* p = lista;
    ListaAtu* ant;

    while(p!=NULL){    
        ant = p;
        p = p->prox;
    }

    if(lista == NULL){
        return nova;
    }
    else{
        ant->prox = nova;
    }
        
    return lista;
   
}

void liberaListaAtu(ListaAtu* lista){
    ListaAtu* p = lista;
    ListaAtu* t;

    while(p){
        t = p->prox;
        free(p);
        p = t;
    }
}

int retornaOri(ListaAtu* lista){
    return lista->ori;
}

int retornaDest(ListaAtu* lista){
    return lista->dest;
}

double retornaSeg(ListaAtu* lista){
    return lista->seg;
}


double retornaVelo(ListaAtu* lista){
    return lista->vel;
}

ListaAtu* proxListaAtu(ListaAtu* lista){
    return lista->prox;
}

void imprimeListaAtu(ListaAtu* lista){
    printf("\n\n");
    for(ListaAtu* p = lista; p; p=p->prox){
        printf("%lf;%d;%d;%lf\n", p->seg, p->ori, p->dest, p->vel);
    }
    printf("\n\n");
}