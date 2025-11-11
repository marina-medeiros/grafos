#ifndef ARVORE_MINIMA_H
#define ARVORE_MINIMA_H

#include <vector>
#include <string>
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"

/**
 * Classe que representa uma árvore geradora mínima de um Grafo
 * Uma árvore geradora de um grafo G = (V,A) é um sub-grafo gerador, T(V,At), conexo e acíclico. 
**/ 

class ArvoreMinima;

/**
 * Classe que representa um grafo não direcionado usando uma lista de adjacência.
 * Herda da classe base Grafo e implementa métodos específicos para grafos.
 * Cada vértice mantém uma lista de seus vizinhos (vértices conectados por arestas).
 */
class ArvoreMinima : public Grafo {
private:
    std::map<int, std::list<int>> lista_adj;

public:
    ArvoreMinima(int vertices);
    virtual ~ArvoreMinima() override = default;

    std::map<int, std::list<int>> get_lista_adj() const { return lista_adj; }

    void limpar() override;
    void inserir_vertice(const std::string& rotulo = "") override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
};

#endif