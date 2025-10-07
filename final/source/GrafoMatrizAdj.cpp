#include <iostream>
#include <queue>
#include <fstream>

#include "../headers/GrafoMatrizAdj.h"

GrafoMatrizAdj::GrafoMatrizAdj(int vertices) : Grafo(vertices) {
    matriz_adj.resize(vertices, std::vector<int>(vertices, 0));
}

void GrafoMatrizAdj::limpar() {
    this->matriz_adj.clear();
    this->rotulos.clear();
    this->qtd_vertices = 0;
    this->qtd_arestas = 0;
}

void GrafoMatrizAdj::inserir_vertice() {
    rotulos.push_back(std::to_string(qtd_vertices));

    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);
    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, 0);
    }
}

void GrafoMatrizAdj::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) {
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
    rotulos.erase(rotulos.begin() + u);

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

void GrafoMatrizAdj::print() const {
    std::cout << "\n--- Imprimindo Matriz de Adjacência ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo esta vazio.\n";
        return;
    }

    std::cout << "\t";
    for (int i = 0; i < qtd_vertices; ++i) {
        std::cout << rotulos.at(i) << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < qtd_vertices; ++i) {
        std::cout << rotulos.at(i) << "\t";
        for (int j = 0; j < qtd_vertices; ++j) {
            std::cout << matriz_adj.at(i).at(j) << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------\n";
}