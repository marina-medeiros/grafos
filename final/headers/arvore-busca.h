#ifndef ARVORE_BUSCA_H
#define ARVORE_BUSCA_H

#include <vector>
#include <string>

/**
 * Classe que representa uma árvore gerada por algoritmos de busca em grafos,
 * como Busca em Largura (BFS) e Busca em Profundidade (DFS).
 * A árvore mantém informações sobre predecessores, níveis, tempos de entrada e saída,
 * além de classificar as arestas em diferentes categorias.
 */
class ArvoreBusca {
protected:
    int qtd_vertices;
    std::vector<int> predecessores;
    std::vector<int> niveis; // Usado principalmente pela BFS
    std::vector<int> tempo_entrada; // Usado pela DFS
    std::vector<int> tempo_saida; // Usado pela DFS
    
    std::vector<std::string> rotulos;

    // Classificação das Arestas
    std::vector<std::pair<int, int>> arestas_arvore;
    std::vector<std::pair<int, int>> arestas_retorno;
    std::vector<std::pair<int, int>> arestas_avanco;
    std::vector<std::pair<int, int>> arestas_cruzamento;

public:
    ArvoreBusca(int vertices) : qtd_vertices(vertices) {
        predecessores.assign(vertices, -1);

        rotulos.resize(vertices);
        for (int i = 0; i < vertices; i++) {
            rotulos[i] = std::to_string(i);
        }
    }

    virtual ~ArvoreBusca() = default;

    int get_qtd_vertices() const { return this->qtd_vertices; };
    const std::vector<int>& get_predecessores() const { return predecessores; }
    const std::vector<int>& get_niveis() const { return niveis; }
    const std::vector<int>& get_tempo_entrada() const { return tempo_entrada; }
    const std::vector<int>& get_tempo_saida() const { return tempo_saida; }
    const std::vector<std::pair<int, int>>& get_arestas_arvore() const { return arestas_arvore; }
    const std::vector<std::pair<int, int>>& get_arestas_retorno() const { return arestas_retorno; }
    const std::vector<std::pair<int, int>>& get_arestas_avanco() const { return arestas_avanco; }
    const std::vector<std::pair<int, int>>& get_arestas_cruzamento() const { return arestas_cruzamento; }

    void adicionar_aresta_arvore(int u, int v) {
        arestas_arvore.push_back({u, v});
    }

    void adicionar_aresta_retorno(int u, int v) {
        arestas_retorno.push_back({u, v});
    }

    void adicionar_aresta_avanco(int u, int v) {
        arestas_avanco.push_back({u, v});
    }

    void adicionar_aresta_cruzamento(int u, int v) {
        arestas_cruzamento.push_back({u, v});
    }

    void adicionar_predecessor(int v, int pred) {
        predecessores[v] = pred;
    }

    void set_nivel(int v, int nivel) {
        if (niveis.size() != qtd_vertices) {
            niveis.resize(qtd_vertices, -1);
        }
        niveis[v] = nivel;
    }

    void set_tempo_entrada(int v, int tempo) {
        if (tempo_entrada.size() != qtd_vertices) {
            tempo_entrada.resize(qtd_vertices, 0);
        }
        tempo_entrada[v] = tempo;
    }

    void set_tempo_saida(int v, int tempo) {
        if (tempo_saida.size() != qtd_vertices) {
            tempo_saida.resize(qtd_vertices, 0);
        }
        tempo_saida[v] = tempo;
    }

    const std::vector<std::string>& get_rotulos() const { return rotulos; }
    void set_rotulos(const std::vector<std::string>& novos_rotulos) { rotulos = novos_rotulos; }
};

#endif