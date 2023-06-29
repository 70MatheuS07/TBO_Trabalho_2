#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"
#include <limits.h>

struct heap{
    
    Item *pq;
    int *map;
    int N;   
};

static void swap(Heap* fila,int i, int j) {
    exch(fila->pq[i], fila->pq[j]);
    fila->map[id(fila->pq[i])] = i;
    fila->map[id(fila->pq[j])] = j;
}

void fix_up(Heap* fila, Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(fila, k, k/2);
        k = k/2;
    }
}

void fix_down(Heap* fila, Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(fila, k, j);
    k = j;
  }
}

Heap* PQ_init(int maxN) {
    Heap* fila = malloc(sizeof(Heap));
    fila->pq = (Item *) malloc((maxN+1) * sizeof (Item));
    fila->map = (int *) malloc((maxN+1) * sizeof (int));
    fila->N = 0;
    return fila;
}

void PQ_insert(Heap* fila, Item v) {
    fila->N++;
    fila->pq[fila->N] = v;
    fila->map[id(v)] = fila->N;
    fix_up(fila, fila->pq, fila->N);
}

Item PQ_delmin(Heap* fila) {
    Item min = fila->pq[1];
    swap(fila, 1, fila->N);
    fila->N--;
    fix_down(fila, fila->pq, fila->N, 1);
    return min;
}

Item PQ_min(Heap* fila) {
    return fila->pq[1];
}

void PQ_decrease_key(Heap* fila, int id, int q,  double dist, double vel) {
    int i = fila->map[id];
    int idq = fila->map[q];
    value(fila->pq[i]) = value(fila->pq[idq]) + (dist/vel);
    distancia(fila->pq[i]) = distancia(fila->pq[idq]) + dist;

    fix_up(fila, fila->pq, i);
}

bool PQ_empty(Heap* fila) {
    return fila->N == 0;
}

int  PQ_size(Heap* fila) {
    return fila->N;
}

void PQ_finish(Heap* fila) {
    free(fila->pq);
    free(fila->map);
    free(fila);
}

bool PQ_ArestaTensa(Heap* fila, int w, int q, float qw) {
    int idw = fila->map[w];
    int idq = fila->map[q];
    if(value(fila->pq[idw]) > value(fila->pq[idq]) + qw)
        return true;
    return false;
}

double PQ_retornaValorID(Heap* fila, int id) {
    double valor =  value(fila->pq[id]);
    return valor;
}

void PQ_imprimeHeap(Heap* fila) {
     if(PQ_empty(fila)){
        printf("\nHEAP VAZIA!\n");
        return;
     }
        printf("\nHEAP\n");
    for(int cont = 1; cont <= fila->N; cont++){
        printf("vertice %d, dist ", id(fila->pq[cont]));
        if(value(fila->pq[cont]) == INT_MAX/2){
            printf("INFINITO");
        }
        else{
            printf("%lf", value(fila->pq[cont]));
        }

        printf(" idMap: %d\n", fila->map[id(fila->pq[cont])]);
    }
}

bool PQ_ITemEstaNaFila(Heap* fila, int id) {
    for(int cont = 1; cont <= fila->N; cont++){
        if(id(fila->pq[cont]) == id)
            return true;
    }
    return false;
}

int PQ_retornaMapId(Heap* fila, int id) {
       int i = fila->map[id];
       return id(fila->pq[i]); 
}