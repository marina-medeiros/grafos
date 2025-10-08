#ifndef GRAFO_MATRIZ_ADJ_H
#define GRAFO_MATRIZ_ADJ_H

#include "Grafo.h"
#include <vector>

class GrafoListaAdj;

class GrafoMatrizAdj : public Grafo {
private:
    std::vector<std::vector<int>> matriz_adj;

public:
    GrafoMatrizAdj(int vertices);
    virtual ~GrafoMatrizAdj() override = default;

    void limpar() override;
    void inserir_vertice() override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
    GrafoListaAdj converter_para_lista_adj() const;
};

#endif