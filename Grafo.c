#include "Grafo.h"

struct grafo{

    int vertices;
    int arestas;
    ListaAdj** VetorAdjs;
    ListaAtu* atualizacoes;
    
};
//cria um Item para adcionar na heap
Item make_item(int id, double value) {
    Item t;
    id(t) = id;
    value(t) = value;
    velocidade(t) = 0;
    distancia(t) = 0;
    return t;
}

void imprimeTempoFormato(double seg, FILE* saida){
    int horas = 0;
    int minutos = 0;
    double resto = 0.0;

    horas = seg/1800;

    minutos = (int)seg%1800;
    minutos = minutos/60;

    resto = seg-(minutos*60.0) - (horas*1800.0);

    if(horas == 0)
        fprintf(saida,"00:");
    else{
        if(horas/10>=1) fprintf(saida,"%d:", horas); 
        else fprintf(saida,"0%d:", horas);
    }

    if(minutos == 0)
        fprintf(saida,"00:");
    else{
        if(minutos/10>=1) fprintf(saida,"%d:", minutos); 
        else fprintf(saida,"0%d:", minutos);
    }

    fprintf(saida,"%.14f", resto);
}

Grafo* criaGrafo(int v, int a){
    Grafo* grafo = malloc(sizeof(Grafo));
    grafo->VetorAdjs = malloc(v*sizeof(ListaAdj*));
    grafo->vertices = v;
    grafo->arestas = a;
    grafo->atualizacoes = criaListaAtu();

    for(int cont = 0; cont<v; cont++){
        grafo->VetorAdjs[cont] = criaListaAjd();
        grafo->VetorAdjs[cont] = insereListaAjd(grafo->VetorAdjs[cont], cont+1, 0, 0); 
    }

    return grafo;
}

void ImprimeGrafo(Grafo* grafo){
        printf("%d vertices, %d arestas \n", grafo->vertices, grafo->arestas);
    for(int cont = 0; cont < grafo->vertices; cont++)
        imprimeListaAdj(grafo->VetorAdjs[cont]);

        imprimeListaAtu(grafo->atualizacoes);
}

void liberaGrafo(Grafo* grafo){
    for(int cont = 0; cont < grafo->vertices; cont++)
        liberaListaAdj(grafo->VetorAdjs[cont]); 
    free(grafo->VetorAdjs);
    liberaListaAtu(grafo->atualizacoes);
    free(grafo);
}

void preencheGrafo(Grafo* grafo, FILE* arq_entrada, double velocidadeInicial){
    int id_v = 0, v_adj = 0;
    double peso = 0.0;

    for(int cont = 0; cont < grafo->arestas; cont++){

        fscanf(arq_entrada, "%d;%d;%lf\n", &id_v, &v_adj, &peso);

        grafo->VetorAdjs[id_v-1] = insereListaAjd(grafo->VetorAdjs[id_v-1], v_adj, peso, velocidadeInicial);
    }
    double seg = 0.0, vel = 0.0;
    int ori = 0, dest = 0;
    while(fscanf(arq_entrada, "%lf;%d;%d;%lf", &seg, &ori, &dest, &vel) == 4){
        fscanf(arq_entrada, "\n");
        grafo->atualizacoes = insereListaAtu(grafo->atualizacoes, seg, ori, dest, vel);
    }
}

void executaDijstra(Grafo* grafo, int* p, int s, int f, FILE* saida) {
    Heap* fila = PQ_init(grafo->vertices);
    // Inicializa vetor de predecessores
    for (int cont = 0; cont < grafo->vertices; cont++) {
        p[cont] = -1;
    }
    // Insere na fila todos os vértices
    for (int cont = 0; cont < grafo->vertices; cont++) {
        Adj* aux = retornaAdjLista(grafo->VetorAdjs[cont]);
        int id = idAdj(aux);

        if (id != s) {
            PQ_insert(fila, make_item(id, INT_MAX / 2));
        } else {
            PQ_insert(fila, make_item(id, 0));
        }
    }

    double* dist = malloc((grafo->vertices + 1) * sizeof(double));
    Item verticeAnalisado;
    int idv;

    while (!PQ_empty(fila)) {
        // Pega o menor vértice
        Item q = PQ_min(fila);

        atualizarVel(id(q), value(q), grafo);

        relaxamento(fila, p, grafo->VetorAdjs[id(q) - 1]);

        verticeAnalisado = PQ_delmin(fila);

        idv = id(verticeAnalisado);
        dist[idv] = distancia(verticeAnalisado);
        // Caso já tenha feito o relaxamento do vértice f, sai do while
        if (idv == f)
            break;
    }

    // Faz a impressão
    // Lista int serve para imprimir o caminho de acordo com os dados coletados no vetor de predecessores p
    ListaInt* caminho = criaListaInt();
    int i = f;
    caminho = insereListaInt(caminho, f);
    while (p[i] != -1) {
        caminho = insereListaInt(caminho, p[i]);
        i = p[i];
    }
    imprimeListaInt(caminho, saida);
    liberaListaInt(caminho);
    // Imprime a distância percorrida em km até f
    fprintf(saida, "%lf\n", dist[idv] / 1000.0);
    // Imprime o tempo no formato HH:MM:SS.fff
    imprimeTempoFormato(value(verticeAnalisado), saida);

    PQ_finish(fila);
    free(dist);
}

void relaxamento(Heap* fila, int* p, ListaAdj* s){
    //vertice analisado
    Adj* q = retornaAdjLista(s);
    for(ListaAdj* adj = proxListaAdj(s); adj!=NULL; adj = proxListaAdj(adj)){
        Adj* w = retornaAdjLista(adj);      
        //if(PQ_ITemEstaNaFila(fila, idAdj(w)) == false){
            //printf("\nNão esta mais na fila ");
            //imprimeAdj(w);
        //}
        //verifica se existe um caminho mais curto
        if(PQ_ArestaTensa(fila, idAdj(w), idAdj(q), valueAdj(w)/velocidadeAdj(w)) == true){
            PQ_decrease_key(fila, idAdj(w), idAdj(q), valueAdj(w), velocidadeAdj(w));
            //atualiza o vetor de predecessores
            p[idAdj(w)] = PQ_retornaMapId(fila, idAdj(q));
        }
    }
}

int retornaNumVertices(Grafo* grafo){
    return grafo->vertices;
}

void atualizarVel(int vertice, double tempoAtual, Grafo* grafo) {
    for (ListaAtu* p = grafo->atualizacoes; p != NULL; p = proxListaAtu(p)) {
        // Enquanto o tempo da lista for menor que o tempoAtual
        if (retornaSeg(p) < tempoAtual) {
            // Se a variável "vertice" for igual ao vértice de origem da lista
            if (vertice == retornaOri(p)) {
                // Atualiza a adj da lista de adjacência do vértice com a nova velocidade
                atualizarVelVertice(grafo->VetorAdjs[vertice - 1], retornaDest(p), retornaVelo(p) / 3.6);
            }
        }
        // Pode sair uma vez que a lista está organizada de maneira cronológica
        else {
            break;
        }
    }
}

