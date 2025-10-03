#include <stack>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/grafo.h"
#include "../headers/busca-profundidade.h"

/*
    BuscaProfundidade(Grafo G, vértice V) {
        Cria pilha vazia P;
        Empilha (P, v);
        Enquanto P.tamanho > 0 faça {
            u = Consulta(P);
            Se existe aresta uv pertencente ao grafo com v.visitado == 0, então {
                v.visitado = 1
                v.predecessor = u
                Empilha(P, v);
            } Senão {
                Desempilha(P)
            }
        }
    }
*/

std::map<int, int> busca_profundidade_matriz_adj_iterativa(Grafo grafo, int vertice) {
    int qtd_vertices = grafo.get_qtd_vertices();

    if (vertice <= 0 || vertice > qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return {};
    }

    std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();
    
    std::stack<int> pilha;
    std::vector<bool> visitados(qtd_vertices, false);
    std::map<int, int> predecessores;

    pilha.push(vertice - 1);
    visitados[vertice - 1] = true; // Marca o vértice inicial como visitado
    predecessores[vertice - 1] = -1; // -1 para representar que não possui predecessor

    while (!pilha.empty()) {
        int u = pilha.top();
        
        bool encontrou_vizinho = false;

        std::cout << (u + 1) << " ";

        for (int v = 0; v < qtd_vertices; v++) {
            if (matriz_adj[u][v] != 0 && !visitados[v]) {
                visitados[v] = true;
                predecessores[v] = u;
                pilha.push(v);

                encontrou_vizinho = true;
                break;
            }
        }

        if (!encontrou_vizinho) {
            pilha.pop();
        }
    }

    std::cout << std::endl << std::endl;

    std::cout << "Mapa de Predecessores:" << std::endl;
    for (const auto& par : predecessores) {
        std::cout << "Vértice " << (par.first + 1) << " foi descoberto a partir de " << (par.second != -1 ? std::to_string(par.second + 1) : "Ninguém (raiz)") << "\n";
    }

    return predecessores;
}

std::map<int, int> busca_profundidade_lista_adj_recursiva(Grafo& grafo, int vertice) {
    int qtd_vertices = grafo.get_qtd_vertices();

    if (vertice <= 0 || vertice > qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return {};
    }

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::vector<bool> visitados(qtd_vertices, false);
    std::map<int, int> predecessores;

    predecessores[vertice - 1] = -1; 

    
    busca_profundidade_lista_adj_recursiva_util(vertice - 1, visitados, predecessores, lista_adj);

    std::cout << std::endl << std::endl;

    std::cout << "Mapa de Predecessores:" << std::endl;
    for (const auto& par : predecessores) {
        std::cout << "Vértice " << (par.first + 1) << " foi descoberto a partir de " << (par.second != -1 ? std::to_string(par.second + 1) : "Ninguém (raiz)") << "\n";
    }

    return predecessores;
}

void busca_profundidade_lista_adj_recursiva_util(int u, std::vector<bool> &visitados, std::map<int, int> &predecessores, std::map<int, std::list<int>> &lista_adj) {
    visitados[u] = true;
    
    std::cout << (u + 1) << " ";

    for (int v : lista_adj[u]) {
        if (!visitados[v]) {
            predecessores[v] = u;
            busca_profundidade_lista_adj_recursiva_util(v, visitados, predecessores, lista_adj);
        }
    }
}

void exportar_arvore_profundidade_para_dot(const std::string& filename, std::map<int, int> arvore) {
    std::ofstream file(filename);
    file << "digraph Arvore_DFS {\n";
    file << "  rankdir=TB; \n";

    int vertice = 0;
    for (auto it = arvore.begin(); it != arvore.end(); it++, vertice++) {
        file << "  " << vertice + 1 << ";\n";
    }

    for (const auto& par : arvore) {
        if (par.second == -1) continue;
        file << "  " << par.second + 1 << " -> " << par.first + 1 << ";\n";
    }

    file << "}\n";
    file.close();
}
