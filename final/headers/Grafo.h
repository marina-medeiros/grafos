#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <list>
#include <vector>
#include <memory>
#include <iostream>

class Grafo {
protected:
    int qtd_vertices;
    int qtd_arestas;
    std::vector<std::string> rotulos;

public:
    Grafo(int vertices);
    virtual ~Grafo() = default;

    virtual void limpar() = 0;
    virtual void inserir_vertice() = 0;
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

    virtual bool is_conexo();
    virtual bool is_bipartido();

    void carregar_de_arquivo(const std::string& filename);
    void exportar_para_dot(const std::string& filename) const;
    void gerar_imagem(const std::string& dotfile, const std::string& imgfile);
    virtual void print() const = 0;
};

#endif