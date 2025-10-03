#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <list>
#include <map>
#include <string>

class Grafo {
protected: // Usamos protected para que a classe filha (Digrafo) possa acessar
    std::map<int, std::list<int>> lista_adj;
    std::vector<std::vector<int>> matriz_adj;
    std::vector<std::vector<int>> matriz_inc;
    int qtd_vertices = 0;

public:
    Grafo(int vertices);
    virtual ~Grafo() {} // Sempre adicione um destrutor virtual em classes base

    void inserir_vertice();
    void remover_vertice(int v); // Remove linha e coluna correspondente ao vértice na matriz de adjacência
    virtual void inserir_aresta(int u, int v, int peso);
    virtual void remover_aresta(int u, int v);
    virtual void gerar_matriz_inc();
    void gerar_lista_adj();
    void print_matriz_adj();
    void print_lista_adj();
    void print_matriz_inc();
    virtual void exportar_para_dot(const std::string& filename);
    
    

    std::vector<std::vector<int>> get_matriz_adj() { return matriz_adj; }
    std::map<int, std::list<int>> get_lista_adj() { gerar_lista_adj(); return lista_adj; }
    int get_qtd_vertices() { return qtd_vertices; }
    bool isConexo();
    void gerar_imagem(const std::string& dotfile, const std::string& imgfile);
};

#endif