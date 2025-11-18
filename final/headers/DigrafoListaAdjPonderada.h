#ifndef DIGRAFO_LISTA_ADJ_PONDERADA_H
#define DIGRAFO_LISTA_ADJ_PONDERADA_H

#include "Grafo.h"
#include <map>
#include <list>
#include <utility>

/**
 * Classe que representa um digrafo (grafo direcionado) ponderado usando uma lista de adjacência.
 * Herda da classe base Grafo e implementa métodos específicos para digrafos.
 * Cada vértice mantém uma lista de seus vizinhos (vértices para os quais há arestas direcionadas).
 * 
 */
class DigrafoListaAdjPonderada : public Grafo {
    std::map<int, std::list<std::pair<int, int>>> lista_adj;
public:
    DigrafoListaAdjPonderada(int vertices);
    virtual ~DigrafoListaAdjPonderada() override = default;

    void limpar() override;
    void inserir_vertice(const std::string& rotulo = "") override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
    int get_grau_saida(int v) const;
    const std::list<std::pair<int, int>>& get_arestas_saindo(int u) const;
    int get_peso(int u, int v) const;
    std::map<int, std::list<std::pair<int, int>>> get_lista_adj()const {return lista_adj;};
};

#endif