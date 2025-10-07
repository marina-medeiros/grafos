#ifndef ARVORE_DE_BUSCA_H
#define ARVORE_BUSCA_H

#include <vector>
#include <string>

class ArvoreBusca {
protected:
    //std::vector<int> nivel;
    int qtd_vertices = 0;
    std::vector<int> predecessores;

    std::vector<std::pair<int, int>> arestas_retorno;
    std::vector<std::pair<int, int>> arestas_avanco;
    std::vector<std::pair<int, int>> arestas_cruzamento;

    void exportar_arestas_nao_arvore(std::ofstream& file) const;

public:
    ArvoreBusca(int vertices);

    virtual ~ArvoreBusca();

    void set_predecessor(int vertice, int predecessor);
    int get_predecessor(int vertice) const;

    void adicionar_aresta_retorno(int u, int v);
    void adicionar_aresta_avanco(int u, int v);
    void adicionar_aresta_cruzamento(int u, int v);
    
    int get_qtd_vertices() { return qtd_vertices; }

    

    //virtual void exportar_para_dot(const std::string& filename) const = 0;
    //virtual void exportar_para_dot(ArvoreBusca arvore, std::string& filename) const = 0;
    void gerar_imagem(const std::string& dotfile, const std::string& imgfile);
};

#endif