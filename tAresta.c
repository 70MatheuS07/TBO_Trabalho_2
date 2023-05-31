#include "tAresta.h"

struct Aresta
{
  int po;                // Ponto origem.
  int pd;                // Ponto destino.
  double dist;           // Distância entre os pontos.
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

int ComparaDistancia(const void *item1, const void *item2)
{
  const tAresta *A1 = (const tAresta *)item1;
  const tAresta *A2 = (const tAresta *)item2;

  if (A1->dist > A2->dist)
    return 1;

  else if (A1->dist < A2->dist)
    return -1;

  return 0;
}

void OrdenaVetArestas(tAresta *vet, int num)
{
  qsort(vet, num, sizeof(tAresta), ComparaDistancia);
}

void LiberaVetArestas(tAresta *vet)
{
  free(vet);
}

int EncontrarMenorDistancia(double *distancias, bool *visitado, int numVertices)
{
  double minimo = INFINITO;
  int indiceMinimo;

  for (int v = 0; v < numVertices; v++)
  {
    if (visitado[v] == false && distancias[v] <= minimo)
    {
      minimo = distancias[v];
      indiceMinimo = v;
    }
  }

  return indiceMinimo;
}

void ImprimirCaminho(int *predecessores, int destino)
{
  if (predecessores[destino] != -1)
  {
    ImprimirCaminho(predecessores, predecessores[destino]);
  }

  printf("%d;", destino);
}

void AlgoritmoDijkstra(tAresta *grafo, int numVertices, int numArestas, int origem, int destino, double velocidadeMediaInicial)
{
  double *distancias = malloc(numVertices * sizeof(double));
  bool *visitado = malloc(numVertices * sizeof(bool));
  int *predecessores = malloc(numVertices * sizeof(int));

  // Inicialização
    for (int v = 0; v < numVertices; v++) {
        distancias[v] = INFINITO;
        visitado[v] = false;
        predecessores[v] = -1;
    }
    
    distancias[origem] = 0; // A distância da origem até ela mesma é 0
    
    for (int count = 0; count < numVertices - 1; count++) {
        int u = EncontrarMenorDistancia(distancias, visitado, numVertices);
        
        visitado[u] = true;
        
        for (int i = 0; i < numArestas; i++) {
            if (grafo[i].po == u && !visitado[grafo[i].pd] && distancias[u] != INFINITO) {
                double tempo = grafo[i].dist / grafo[i].velocidade_via; // Tempo necessário para percorrer a aresta
                
                if (distancias[u] + tempo < distancias[grafo[i].pd]) {
                    distancias[grafo[i].pd] = distancias[u] + tempo;
                    predecessores[grafo[i].pd] = u;
                }
            }
        }
    }
    
    // Imprimir o caminho mais curto
    printf("Caminho mais curto: ");
    ImprimirCaminho(predecessores, destino);
    
    // Imprimir a distância total
    printf("\nDistância total: %.2lf metros\n", distancias[destino]);
    
    // Calcular e imprimir o tempo estimado
    int horas = (int)(distancias[destino] / velocidadeMediaInicial);
    int minutos = (int)(((distancias[destino] / velocidadeMediaInicial) - horas) * 60);
    double segundos = ((((distancias[destino] / velocidadeMediaInicial) - horas) * 60) - minutos) * 60;
    
    printf("Tempo estimado: %02d:%02d:%lf\n", horas, minutos, segundos);
}