#ifndef DIGRAFO_MATRIZ_ADJ_H
#define DIGRAFO_MATRIZ_ADJ_H

#include "GrafoMatrizAdj.h"
#include <vector>

/**
 * Classe que representa um digrafo (grafo direcionado) usando uma matriz de adjacência.
 * Herda da classe base GrafoMatrizAdj e implementa métodos específicos para digrafos.
 * Cada célula na matriz indica a presença e o peso de uma aresta direcionada entre dois vértices.
 */
class DigrafoMatrizAdj : public GrafoMatrizAdj {
public:
    DigrafoMatrizAdj(int vertices) : GrafoMatrizAdj(vertices) {}
    virtual ~DigrafoMatrizAdj() override = default;

    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
};

#endif