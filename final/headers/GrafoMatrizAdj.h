#ifndef GRAFO_MATRIZ_ADJ_H
#define GRAFO_MATRIZ_ADJ_H

#include "Grafo.h"
#include <vector>

class GrafoListaAdj;

/**
 * Classe que representa um grafo não direcionado usando uma matriz de adjacência.
 * Herda da classe base Grafo e implementa métodos específicos para grafos.
 * Cada célula na matriz indica a presença e o peso de uma aresta entre dois vértices.
 */
class GrafoMatrizAdj : public Grafo {
protected:
    std::vector<std::vector<int>> matriz_adj;

public:
    GrafoMatrizAdj(int vertices);
    virtual ~GrafoMatrizAdj() override = default;

    void limpar() override;
    void inserir_vertice(const std::string& rotulo = "") override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
    GrafoListaAdj converter_para_lista_adj() const;

    std::vector<std::vector<int>> get_matriz_adj() const {return matriz_adj;};
    int get_peso(int u, int v) const;
};

#endif