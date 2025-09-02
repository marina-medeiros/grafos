#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <list>
#include <map>
#include <cstdio>
#include <list>

class Grafo {
    std::vector<std::vector<int>> matriz_adj;
    std::vector<std::vector<int>> matriz_inc;
    std::map<int, std::list<int>> lista_adj;
    std::vector<std::list<int>> estrela_direta;
    int qtd_vertices = 0;

    public:
    Grafo() { 
        matriz_adj = std::vector<std::vector<int>> (0, std::vector<int>(0, 0));
    }

    void inserir_vertice();
    void remover_vertice(int v); // Remove linha e coluna correspondente ao vértice na matriz de adjacência
    void inserir_aresta_dir(int u, int v, int peso);
    void inserir_aresta_ndir(int u, int v, int peso);
    void remover_aresta_dir(int u, int v);
    void remover_aresta_ndir(int u, int v);
    void gerar_matriz_inc(int dir);
    void gerar_lista_adj();
    void print_matriz_adj();
    void print_lista_adj();
    void print_matriz_inc();
    void exportar_para_dot(const std::string& filename, int dir);

    std::vector<std::vector<int>> get_matriz_adj() { return matriz_adj; }
    std::map<int, std::list<int>> get_lista_adj() { gerar_lista_adj(); return lista_adj; }
    int get_qtd_vertices() { return qtd_vertices; }
};

#endif