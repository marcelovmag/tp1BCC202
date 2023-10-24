#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafoPonderado.h"

typedef struct grafoPon GrafoPon {

    int numCidades; // Numero de cidades no dado grafico
    float** matrizAdjacencias; // Matriz que armazena as distancias entre cada cidade
    int* caminho; // Vetor que armazena o melhor caminho pro dado grafo, uma vez que calculado

}

void alocarGrafo(GrafoPon* grafo) {

    // Aloca espaco suficiente para o vetor caminho, considerando que a primeira cidade (da qual se comeca) irá repetir
    grafo-> caminho = (int*) malloc(sizeof(int) * grafo-> numCidade + 1);

    /*
    Alocacao da matriz n*n para armazenar as distancias entre as cidades, sendo armazenados no seguinte padrao:
    Considere a matriz[i][j].
    i: cidade de origem
    j: cidade de destino
    matriz[i][j]: distancia entre essas 2 cidades
    */
    grafo-> matrizAdjacencias = (float*) malloc(sizeof(float*) * grafo-> numCidade);

    for (int i = 0; i < grafo-> numCidade; i++)
    {
        grafo-> matrizAdjacencias[i] = (float*) malloc(sizeof(float));
    }
    
}

void desalocarGrafo(GrafoPon* grafo) {

    // Libera matriz
    for (int i = 0; i < n; i++)
    {
        free(grafo-> matrizAdjacencias[i]);
    }

    free(grafo-> matrizAdjacencias);

    // Libera numCidades
    free(grafo-> numCidades);

    // Libera vetor caminho
    free(grafo-> caminho);

}

void leGrafo(GrafoPon* grafo) {
    
    // Variaveis locais para preenchimento dos atributos do grafo
    int cidadeOrigem, cidadeDestino;
    float distancia;

    // Le e armazena o número de cidades
    scanf("%d", &(grafo-> numCidades));

    // Le e armazena a distancia entre cada cidade, preenchendo a matriz "matrizAdjacencias" conforme o padrao descrito nos comentarios da funcao "alocaGrafo"
    for (int i = 0; i < pow(grafo-> numCidades, 2); i++)
    {
        scanf("%d%d%f", &cidadeOrigem, cidadeDestino, distancia);
        grafo-> matrizAdjacencias[cidadeOrigem, cidadeDestino] = distancia;
    }
    
}

void imprimeCaminho(GrafoPon* grafo) {

    // Imprime numa primeira linha o menor caminho a ser percorrido
    for (int i = 0; i < grafo-> numCidades; i++)
    {
        printf("%d ", grafo-> caminho[i]);
    }

    printf("%d\n", grafo-> caminho[grafo-> numCidades + 1]);

    // Calcula e imprime a distancia percorrida por esse menor caminho
    double soma = 0;
    for (int i = 0; i < grafo-> numCidades; i++)
    {
        soma += grafo-> matrizAdjacencias[grafo-> caminho[i]][grafo-> caminho[i+1]];
    }
    
    printf("%lf\n", soma);
}