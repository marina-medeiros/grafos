#ifndef DIGRAFO_MATRIZ_ADJ_H
#define DIGRAFO_MATRIZ_ADJ_H

#include "GrafoMatrizAdj.h"
#include <vector>

class DigrafoMatrizAdj : public GrafoMatrizAdj {

public:
    DigrafoMatrizAdj(int vertices) : GrafoMatrizAdj(vertices) {}
    virtual ~DigrafoMatrizAdj() override = default;

    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
};

#endif