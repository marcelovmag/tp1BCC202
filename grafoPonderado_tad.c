#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "grafoPonderado_tad.h"

typedef struct grafoPon {

    int numCidades; // Numero de cidades no dado grafico
    float** matrizAdjacencias; // Matriz que armazena as distancias entre cada cidade
    int* caminho; // Vetor que armazena o melhor caminho pro dado grafo, uma vez que calculado
    int* caminhoTemp; // Vetor que armazena os caminhos em tempo de teste
    double distancia;
    int n;

} GrafoPon;

void alocarGrafo(GrafoPon* grafo) {

    // Aloca espaco suficiente para o vetor caminho, considerando que a primeira cidade (da qual se comeca) irá repetir
    grafo-> caminho = (int*) malloc(sizeof(int) * grafo-> numCidades + 1);
    grafo-> caminhoTemp = (int*) malloc(sizeof(int) * grafo-> numCidades + 1);
    
    for (int i = 0; i < grafo-> numCidades; i++)
    {
        grafo-> caminhoTemp[i] = i;
    }
    grafo-> caminhoTemp[grafo-> numCidades] = 0;
    
    grafo-> distancia = INT_MAX;

    /*
    Alocacao da matriz n*n para armazenar as distancias entre as cidades, sendo armazenados no seguinte padrao:
    Considere a matriz[i][j].
    i: cidade de origem
    j: cidade de destino
    matriz[i][j]: distancia entre essas 2 cidades
    */
    grafo-> matrizAdjacencias = (float**) malloc(sizeof(float*) * grafo-> numCidades);

    for (int i = 0; i < grafo-> numCidades; i++)
    {
        grafo-> matrizAdjacencias[i] = (float*) malloc(sizeof(float));
    }
    
}

void desalocarGrafo(GrafoPon* grafo) {

    // Libera matriz
    for (int i = 0; i < grafo-> numCidades; i++)
    {
        free(grafo-> matrizAdjacencias[i]);
    }

    free(grafo-> matrizAdjacencias);

    // Libera vetor caminho
    free(grafo-> caminho);

}

void leGrafo(GrafoPon* grafo) {
    
    // Variaveis locais para preenchimento dos atributos do grafo
    int cidadeOrigem, cidadeDestino;
    float distancia;

    // Le e armazena o número de cidades
    scanf("%d", &(grafo-> numCidades));
    grafo-> n = grafo->numCidades + 1;

    alocarGrafo(grafo);

    // Le e armazena a distancia entre cada cidade, preenchendo a matriz "matrizAdjacencias" conforme o padrao descrito nos comentarios da funcao "alocaGrafo"
    for (int i = 0; i < pow(grafo-> numCidades, 2); i++)
    {
        scanf("%d%d%f", &cidadeOrigem, &cidadeDestino, &distancia);
        grafo-> matrizAdjacencias[cidadeOrigem][cidadeDestino] = distancia;
    }
    
}

// Funcao que calcula e retorna a distancia percorrida pra um dado caminho
float calculaDistancia(int* caminho, float** matrizAdjacencias, int n) {
    float distancia = 0;

    for (int i = 1; i < n; i++)
    {
        if (!matrizAdjacencias[caminho[i-1]][caminho[i]])
            return INT_MAX;
        
        distancia += matrizAdjacencias[caminho[i-1]][caminho[i]];
    }
    
    return distancia;
}

// Funcao simples que troca 2 numeros de um vetor de lugar
void swap(int** v, int i1, int i2) {
    int temp = *v[i1];
    *v[i1] = *v[i2];
    *v[i2] = temp;
}

void encontraCaminho(GrafoPon* grafo) {
    
    // Caso de parada, quando numCidades (variavel em decrescimento) chega a 1, faz o calculo da distancia para o caminho temporario atual
    if (grafo-> numCidades == 1)
    {

        // Se a distancia do caminho novo for menor que a menor calculada ate agora, substitui o caminho e distancia novos
        if (calculaDistancia(grafo-> caminhoTemp, grafo-> matrizAdjacencias, grafo-> n) < grafo-> distancia)
        {
            for (int i = 0; i < grafo-> n; i++)
            {
                grafo-> caminho[i] = grafo-> caminhoTemp[i];
            }

            grafo-> distancia = calculaDistancia(grafo-> caminho, grafo-> matrizAdjacencias, grafo-> n);
            
        }
        
        return;
    }

    for (int i = 1; i < grafo-> numCidades; i++)
    {
        // Reduz em 1 o numCidades (variavel em decrescimento)
        grafo-> numCidades--;

        // Recursao ate chegar no caso de parada
        encontraCaminho(grafo);

        // Volta a incrementar numCidades apos voltar do caso de parada
        grafo-> numCidades++;

        // Em caso de numCidades par, faz um swap de vetor[i] e vetor[numCidades - 1]
        if (grafo-> numCidades % 2 == 0)
            swap(&(grafo-> caminhoTemp), grafo-> caminhoTemp[i], grafo-> caminhoTemp[grafo-> numCidades]);

        // Em caso de numCidades impar, faz um swap de vetor[0] e vetor[numCidades - 1]
        else   
            swap(&(grafo-> caminhoTemp), grafo-> caminhoTemp[1], grafo-> caminhoTemp[grafo-> numCidades]);

        /*
        *   Essa lógica de ifs para numCidades impar e par garante que os swaps chamados ao fim de um for (voltando pra um for "maior"),
        *   seja irrelevante, sendo um swap de vet[a] pra vet[a], ja que ao voltar pro for "maior", havera um novo swap, dessa vez relevante.
        * 
        *   Dessa forma, garante-se que percorra todas as numCidades! possibilidades
        */
    }
    
}

void imprimeCaminho(GrafoPon* grafo) {

    // Imprime numa primeira linha o menor caminho a ser percorrido
    for (int i = 0; i <= grafo-> numCidades; i++)
    {
        printf("%d ", grafo-> caminho[i]);
    }

    // Calcula e imprime a distancia percorrida por esse menor caminho
    printf("\n%lf\n", calculaDistancia(grafo-> caminho, grafo-> matrizAdjacencias, grafo->n));
}
