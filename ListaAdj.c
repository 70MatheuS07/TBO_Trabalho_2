
#include "ListaAdj.h"

struct listaAdj
{
    Adj* adj;
    ListaAdj* prox;

};

ListaAdj* criaListaAjd(){
        return NULL;
}


ListaAdj* insereListaAjd(ListaAdj* lista, int vertice, double peso, double velocidade){
    ListaAdj* nova = malloc(sizeof(ListaAdj));
    Adj* adj = criaAjd(vertice, peso, velocidade);
    nova->adj = adj;
    nova->prox = NULL;
  
    ListaAdj* p = lista;
    ListaAdj* ant;
        

    //mais de uma celula
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


void imprimeListaAdj(ListaAdj* lista){
        int cont = 0;
        for(ListaAdj* p = lista; p!=NULL; p = p->prox){
            imprimeAdj(p->adj);
        }
        printf("\n");
}

void liberaListaAdj(ListaAdj* lista){
    ListaAdj* p = lista;
    ListaAdj* t;

    while(p){
        t = p->prox;
        liberaAdj(p->adj);
        free(p);
        p = t;
    }
}

ListaAdj* proxListaAdj(ListaAdj* lista){
    return lista->prox;
}

int retornaListaVertice(ListaAdj* lista){
    return idAdj(lista->adj);
}

double retornaListaPeso(ListaAdj* lista){
    return valueAdj(lista->adj);
}

Adj* retornaAdjLista(ListaAdj* lista){
    return lista->adj;
}

void atualizarVelVertice(ListaAdj* lista, int dest, double velocidade){
    for(ListaAdj* p = lista->prox; p!=NULL; p = p->prox){
        if(idAdj(p->adj) == dest){
            mudarVelAdj(p->adj, velocidade);
            break;
        }
    }   
}