#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct heap Heap;
Heap* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(Heap* fila, Item v);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin(Heap* fila);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(Heap* fila, int id, int q,  double dist, double vel); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(Heap* fila);         // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(Heap* fila);       // Retorna True se a PQ não tem elementos
int  PQ_size(Heap* fila);        // Número de elementos na PQ
void PQ_finish(Heap* fila);       // Libera memória
bool PQ_ArestaTensa(Heap* fila, int w, int q, float qw); //verifica se existe um caminho mais curto
double PQ_retornaValorID(Heap* fila, int id);
void PQ_imprimeHeap(Heap* fila);
bool PQ_ITemEstaNaFila(Heap* fila, int id);
int PQ_retornaMapId(Heap* fila, int id);

#endif
