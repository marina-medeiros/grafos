#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <iostream>

/**
 * Classe base abstrata que representa um grafo não direcionado.
 * Define a interface comum para diferentes implementações de grafos,
 * como listas de adjacência, matrizes de adjacência e matrizes de incidência.
 */
class Grafo {
protected:
    int qtd_vertices;
    int qtd_arestas;
    std::vector<std::string> rotulos;

public:
    Grafo(int vertices);
    virtual ~Grafo() = default;

    void incrementar_qtd_arestas();
    void decrementar_qtd_arestas();

    virtual void limpar() = 0;
    virtual void inserir_vertice(const std::string& rotulo = "") = 0;
    virtual void remover_vertice(int v) = 0;
    virtual void inserir_aresta(int u, int v, int peso = 1) = 0;
    virtual void remover_aresta(int u, int v) = 0;
    virtual bool existe_aresta(int u, int v) const = 0;
    virtual std::list<int> get_vizinhos(int v) const = 0;

    int get_grau_vertice(int v) const { return get_vizinhos(v).size(); } 
    int get_qtd_vertices() const { return qtd_vertices; }
    int get_qtd_arestas() const { return qtd_arestas; }
    const std::vector<std::string>& get_rotulos() const { return rotulos; }
    void set_rotulos(const std::vector<std::string>& novos_rotulos) { rotulos = novos_rotulos; }
    int get_indice_do_rotulo(const std::string& rotulo) const;
    virtual bool is_conexo();
    virtual bool is_bipartido();
    virtual void determinar_articulacoes_blocos_lowpt();

    void carregar_de_arquivo(const std::string& filename);
    void exportar_para_dot(const std::string& filename, bool eh_digrafo = false) const;
    virtual void print() const = 0;
};

    void gerar_imagem(const std::string& dotfile, const std::string& imgfile);

#endif