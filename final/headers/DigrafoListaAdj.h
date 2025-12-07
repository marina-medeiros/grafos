#ifndef DIGRAFO_LISTA_ADJ_H
#define DIGRAFO_LISTA_ADJ_H

#include "GrafoListaAdj.h" 

/**
 * Classe que representa um digrafo (grafo direcionado) usando uma lista de adjacência.
 * Herda da classe base Grafo e implementa métodos específicos para digrafos.
 * Cada vértice mantém uma lista de seus vizinhos (vértices para os quais há arestas direcionadas).
 * 
 */
class DigrafoListaAdj : public Grafo{
    std::map<int, std::list<int>> lista_adj;
public:
    DigrafoListaAdj(int vertices);
    virtual ~DigrafoListaAdj() override = default;

    std::map<int, std::list<int>> get_lista_adj() const { return lista_adj; }

    void limpar() override;
    void inserir_vertice(const std::string& rotulo = "") override;
    void remover_vertice(int u) override;
    void inserir_aresta(int u, int v, int peso = 1) override;
    void remover_aresta(int u, int v) override;
    bool existe_aresta(int u, int v) const override;
    std::list<int> get_vizinhos(int v) const override;
    void print() const override;
    int get_grau_saida(int v) const;
    int get_grau_entrada(int v) const;
    GrafoListaAdj obter_grafo_subjacente(const DigrafoListaAdj& digrafo);
};

#endif 