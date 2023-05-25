#ifndef TARESTA_H
#define TARESTA_H

#include "tAresta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Tipo Aresta, possui um ponto de origem e um de destino do tipo inteiro para que para obter
 * um acesso direto aos pontos
 * 
 */
typedef struct Aresta tAresta;

/**
 * @brief Cria-se um vetor de arestas, alocando um vetor dinâmico para aresta com o tamanho(numero de vertices-1),
 * 
 * @param qtdA quantidade de arestas 
 * @return tAresta** 
 */
tAresta *CriaVetorArestas(int qtdA);

/**
 * @brief Ordena o vetor de arestas com qsort
 * 
 * @param VetA Vetor de arestas
 * @param qtdA quantidade de arestas
 */
void OrdenaVetArestas(tAresta *VetA, int qtdA);

/**
 * @brief Compara as distancias  do tipo aresta para utilizar no qsort do OrdenaArestas
 * 
 * @param item1 
 * @param item2 
 * @return int 1,-1 ou 0
 */
int comparaDistancia(const void *item1, const void *item2);

/**
 * @brief Libera Todo o vetor de arestas
 * 
 * @param VetA Vetor de arestas
 * @param qtdA quabntidade de arestas
 */
void LiberaVetArestas(tAresta *VetA);

#endif