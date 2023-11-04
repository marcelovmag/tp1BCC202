#include "grafoPonderado_tad.h"

int main() {

    GrafoPon grafo;

    leGrafo(&grafo);

    encontraCaminho(&grafo);

    imprimeCaminho(&grafo);

    desalocarGrafo(&grafo);
    
    return 0;
}