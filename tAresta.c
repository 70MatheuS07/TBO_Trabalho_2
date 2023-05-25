#include "tAresta.h"

#include <stdio.h>
#include <stdlib.h>

struct Aresta
{
  int po;                // Ponto origem.
  int pd;                // Ponto destino.
  double dist;           // Distancia entre os pontos.
  double velocidade_via; // Velocidade da via.
};

tAresta *CriaVetorArestas(int num)
{
  tAresta *vet = malloc(sizeof(tAresta) * num);
  return vet;
}

void PreencheVetorArestas(FILE *arq_entrada, tAresta *vet, int num, double velocidade_inicial)
{
  int po, pd;
  double dist;
  for (int i = 0; i < num; i++)
  {
    fscanf(arq_entrada, "%d;%d;%lf\n", &po, &pd, &dist);

    vet[i].po = po;
    vet[i].pd = pd;
    vet[i].dist = dist;
    vet[i].velocidade_via = velocidade_inicial;
  }
}

void OrdenaVetArestas(tAresta *vet, int num)
{
  qsort(vet, num, sizeof(tAresta), comparaDistancia);
}

void LiberaVetArestas(tAresta *vet)
{
  free(vet);
}
