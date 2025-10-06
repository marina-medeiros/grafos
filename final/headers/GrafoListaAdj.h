#ifndef GRAFO_LISTA_ADJ_H
#define GRAFO_LISTA_ADJ_H

#include "Grafo.h"
#include <map>
#include <algorithm>

class GrafoListaAdj : public Grafo {
private:
    std::map<int, std::list<int>> lista_adj;

public:
    GrafoListaAdj(int vertices);
    virtual ~GrafoListaAdj() override = default;

    void inserir_vertice() override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
};

#endif