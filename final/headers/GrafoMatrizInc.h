#ifndef GRAFO_MATRIZ_INC_H
#define GRAFO_MATRIZ_INC_H

#include "Grafo.h"
#include <utility>
#include <vector>

class GrafoMatrizInc : public Grafo {
private:
    std::vector<std::vector<int>> matriz_inc;
    std::vector<std::pair<int, int>> arestas_info;

public:
    GrafoMatrizInc(int vertices);
    virtual ~GrafoMatrizInc() override = default;

    void limpar() override;
    void inserir_vertice() override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
};

#endif