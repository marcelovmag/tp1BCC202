#ifndef grafoPonderado_tad_h
#define grafoPonderado_tad_h

#include <stdio.h>

typedef struct grafoPon GrafoPon;

void alocarGrafo(GrafoPon*);

void desalocarGrafo(GrafoPon*);

void leGrafo(GrafoPon*);

void encontraCaminho(GrafoPon*);

void imprimeCaminho(GrafoPon*);

#endif /* grafoPonderado_tad_h */