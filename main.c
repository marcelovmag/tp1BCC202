#include "grafoPonderado.h"

int main() {

    GrafoPon grafo;

    alocaGrafo(&grafo);

    leGrafo(&grafo);

    encontraCaminho(&grafo);

    imprimeCaminho(&grafo);

    desalocaGrafo(&grafo);
    
    return 0;
}