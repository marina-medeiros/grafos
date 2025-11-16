#ifndef ARVORELARGURA_H
#define ARVORELARGURA_H

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <list>
#include <map>
#include <cstdio>
#include <list>



/** 
 *  Classe que representa uma árvore gerada por um algoritmo de Busca em Largura (BFS).
 *  A árvore mantém uma matriz de adjacência, níveis dos vértices e rótulos.
*/
class ArvoreLargura {
    std::vector<std::vector<int>> matriz_adj;
    std::vector<int> nivel;
    std::vector<std::string> rotulos;
    int qtd_vertices = 0;

    public:
    static const int INF;
    ArvoreLargura() { 
        matriz_adj = std::vector<std::vector<int>> (0, std::vector<int>(0, 0));
    }

    ArvoreLargura(int vertices) {
        this->qtd_vertices = vertices;  
        matriz_adj = std::vector<std::vector<int>> (qtd_vertices, std::vector<int>(qtd_vertices, 0));
        nivel = std::vector<int>(vertices, 0);
        
        rotulos.resize(vertices);
        for (int i = 0; i < vertices; i++) {
            rotulos[i] = std::to_string(i);
        }
    }

    void inserir_vertice();
    void remover_vertice(int v); // Remove linha e coluna correspondente ao vértice na matriz de adjacência
    void inserir_aresta_ndir(int u, int v, int peso);
    void remover_aresta_ndir(int u, int v);
    void exportar_arvore_bfs(ArvoreLargura arvore, const std::string& filename);

    std::vector<std::vector<int>> get_matriz_adj() { return matriz_adj; }
    int get_qtd_vertices() { return qtd_vertices; }
    void set_nivel(int vertice, int nivel_v){
        this->nivel[vertice] = nivel_v;
    }
    int get_nivel(int vertice){
        return this->nivel[vertice];
    }

    const std::vector<std::string>& get_rotulos() const { return rotulos; }
    void set_rotulos(const std::vector<std::string>& novos_rotulos) { rotulos = novos_rotulos; }
};

#endif