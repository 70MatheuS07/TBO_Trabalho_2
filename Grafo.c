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

void RodaDijstra(Grafo* grafo, int* p, int s, int f, FILE* saida, double* dist){
    int cont = 0;
    int verticeAtual = s;
    double tempoAtual = 0.0, acumulado = 0.0; 
    Item itemFinal;
    dist = malloc( (grafo->vertices + 1)*sizeof(double));
    while(1){
        if(cont == 10) break;
        cont++;

        itemFinal = executaDijstra(grafo, p, verticeAtual, f, dist);

        ListaInt* caminho = criaListaInt();
        int i = f;
        caminho = insereListaInt(caminho, f);
        while(p[i]!=-1){
            caminho = insereListaInt(caminho, p[i]);
            i = p[i];
        }
        liberaListaInt(caminho);

        atualizarVelocidades(tempoAtual, grafo);

        verticeAtual = proxIntLista(caminho);
        printf("\n\natual %d = prox %d\n\n", verticeAtual, proxIntLista(caminho));
        if(verticeAtual == f) break;
    }
    imprimeResultado(grafo, p, s, f, saida, dist, itemFinal);
}

Heap* inicializaDijstra(Grafo* grafo, int s, int f, int* p){
    Heap* fila = PQ_init(grafo->vertices);
    //inicializa vetor de predecessores
    for(int cont = 0; cont < grafo->vertices; cont++){
        p[cont] = -1;
    }
    //insere na fila todos os vertices
    for(int cont = 0; cont < grafo->vertices; cont++){
        Adj* aux = retornaAdjLista(grafo->VetorAdjs[cont]);
        int id = idAdj(aux);

        if(id != s){
            PQ_insert(fila, make_item(id, INT_MAX/2));
        }
        else{
            PQ_insert(fila, make_item(id, 0));
        }
    }
    return fila;
}

void imprimeResultado(Grafo* grafo, int* p, int s, int f, FILE* saida, double* dist, Item verticeAnalisado){
   //faz a impressão
    //Lista int serve para imprimir o caminho de acordo com o dados coletados no vetor de predecessores p
    ListaInt* caminho = criaListaInt();
    int i = f;
    caminho = insereListaInt(caminho, f);
    while(p[i]!=-1){
        caminho = insereListaInt(caminho, p[i]);
        i = p[i];
    }
    imprimeListaInt(caminho, saida);
    liberaListaInt(caminho);
    //imprime a distancia percorrida em km até f
    fprintf(saida, "%lf\n", dist[id(verticeAnalisado)]/1000.0);
    //imprime tempo no formato HH:MM:SS.fff
    imprimeTempoFormato(value(verticeAnalisado), saida);
}

Item executaDijstra(Grafo* grafo, int* p, int s, int f, double* dist){
    Heap* fila = inicializaDijstra(grafo, s, f, p);
    Item verticeAnalisado;
    int idv;

    while(!PQ_empty(fila)){
        //pega o menor vertice
        Item q = PQ_min(fila);

        atualizarVel(id(q),value(q), grafo);

        relaxamento(fila, p, grafo->VetorAdjs[id(q)-1]);

        verticeAnalisado = PQ_delmin(fila);

        idv = id(verticeAnalisado);
        dist[idv] = distancia(verticeAnalisado);
        //caso já tenha feito o relaxamento do vertice f sai do while
        if(idv == f)
            break;
    }
    PQ_finish(fila);
    return verticeAnalisado;
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

void atualizarVelocidades(double tempoAtual, Grafo* grafo){
    for(ListaAtu* p = grafo->atualizacoes; p!=NULL; p = proxListaAtu(p)){
            //enquando o tempo da lista for menor que o tempoAtual 
            if(retornaSeg(p) < tempoAtual){
                //se a variavel vertice for igual ao vertice de origem da lista
                atualizarVelVertice(grafo->VetorAdjs[retornaOri(p)-1], retornaDest(p), retornaVelo(p)/3.6);
            }
            //pode sair uma vez que a lista está organizada de maneira cronologica
            else{
                break;
            }
    }
}

void atualizarVel(int vertice, double tempoAtual, Grafo* grafo){
    for(ListaAtu* p = grafo->atualizacoes; p!=NULL; p = proxListaAtu(p)){
            //enquando o tempo da lista for menor que o tempoAtual 
            if(retornaSeg(p) < tempoAtual){
                //se a variavel vertice for igual ao vertice de origem da lista
                if(vertice == retornaOri(p)){
                    //atualiza a adj da lista de adj do vertice com a nova velocidade 
                    atualizarVelVertice(grafo->VetorAdjs[vertice-1], retornaDest(p), retornaVelo(p)/3.6);
                }
            }
            //pode sair uma vez que a lista está organizada de maneira cronologica
            else{
                break;
            }
    }
}