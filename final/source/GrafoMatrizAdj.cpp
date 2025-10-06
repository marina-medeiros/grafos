#include <iostream>
#include <queue>
#include <fstream>

#include "../headers/GrafoMatrizAdj.h"

GrafoMatrizAdj::GrafoMatrizAdj(int vertices) : Grafo(vertices) {
    matriz_adj.resize(vertices, std::vector<int>(vertices, 0));
}

void GrafoMatrizAdj::inserir_vertice() {
    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);

    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, 0);
    }
}

void GrafoMatrizAdj::remover_vertice(int u) {
    // Validação para evitar erros com índices inválidos
    if (u <= 0 || u > qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    }
    
    // 1. Atualiza a contagem de arestas
    for (int i = 0; i < qtd_vertices; ++i) {
        if (matriz_adj[u][i] != 0) {
            qtd_arestas--;
        }
    }
    
    // 2. Remove a linha 'u'
    matriz_adj.erase(matriz_adj.begin() + u);

    // 3. Remove a coluna 'u' de todas as linhas restantes
    for (auto& linha : matriz_adj) {
        linha.erase(linha.begin() + u);
    }
    
    // 4. Atualiza a contagem de vértices
    qtd_vertices--;
}

void GrafoMatrizAdj::inserir_aresta(int u, int v, int peso) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] == 0) {
            qtd_arestas++;
        }
        matriz_adj[u][v] = peso;
        matriz_adj[v][u] = peso; // Grafo não-direcionado
    }
}

void GrafoMatrizAdj::remover_aresta(int u, int v) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] != 0) {
            qtd_arestas--;
        }
        matriz_adj[u][v] = 0;
        matriz_adj[v][u] = 0;
    }
}

bool GrafoMatrizAdj::existe_aresta(int u, int v) const {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        return matriz_adj[u][v] != 0;
    }
    return false;
}

std::list<int> GrafoMatrizAdj::get_vizinhos(int v) const {
    std::list<int> vizinhos;
    if (v >= 0 && v < qtd_vertices) {
        for (int j = 0; j < qtd_vertices; ++j) {
            if (matriz_adj[v][j] != 0) {
                vizinhos.push_back(j);
            }
        }
    }
    return vizinhos;
}