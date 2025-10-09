#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/GrafoListaAdj.h"


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

std::map<int, int> busca_em_profundidade_grafo(const Grafo& grafo, int vertice_inicial) {
    int qtd_vertices = grafo.get_qtd_vertices();
    std::map<int, int> predecessores;

    if (vertice_inicial < 0 || vertice_inicial >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return predecessores;
    }

    std::stack<int> pilha;
    std::vector<bool> visitados(qtd_vertices, false);

    pilha.push(vertice_inicial);
    visitados[vertice_inicial] = true;
    predecessores[vertice_inicial] = -1;

    while (!pilha.empty()) {
        int u = pilha.top();
        
        bool encontrou_vizinho_nao_visitado = false;
        for (int v : grafo.get_vizinhos(u)) {
            if (!visitados[v]) {
                visitados[v] = true;
                predecessores[v] = u;
                pilha.push(v);
                
                encontrou_vizinho_nao_visitado = true;
                break;
            }
        }

        if (!encontrou_vizinho_nao_visitado) {
            pilha.pop();
        }
    }

    return predecessores;
}


std::pair<std::map<int, int>, std::vector<std::pair<int, int>>> busca_profundidade_lista_adj_recursiva(GrafoListaAdj grafo, int vertice) {
    int qtd_vertices = grafo.get_qtd_vertices();

    if (vertice < 0 || vertice > qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return {};
    }

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::vector<bool> visitados(qtd_vertices, false);
    std::map<int, int> predecessores;
    for (int i = 0; i < qtd_vertices; i++) {
        predecessores[i] = -1;
    }
    std::vector<std::pair<int, int>> arestas_retorno;

    busca_profundidade_lista_adj_recursiva_util(vertice, visitados, predecessores, lista_adj, arestas_retorno);

    std::cout << std::endl;

    // std::cout << "Mapa de Predecessores:" << std::endl;
    // for (const auto& par : predecessores) {
    //     std::cout << "Vértice " << (par.first + 1) << " foi descoberto a partir de " << (par.second != -1 ? std::to_string(par.second + 1) : "Ninguém (raiz)") << "\n";
    // }

    std::cout << std::endl;
    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(const auto& par : predecessores) {
        std::cout << "| " << (par.first + 1) << "\t| "
                << (par.second != -1 ? std::to_string(par.second + 1) : "Raiz") << "\t  | "
                <<  std::endl;
    }
    std::cout << "---------------------\n";

    std::cout << "\nArestas de Retorno Encontradas:" << std::endl;
    for (const auto& aresta : arestas_retorno) {
        std::cout << "(" << aresta.first + 1 << ", " << aresta.second + 1 << ")" << std::endl;
    }

    return {predecessores, arestas_retorno};
}

void busca_profundidade_lista_adj_recursiva_util(int u,
                                                std::vector<bool>& visitados,
                                                std::map<int, int>& predecessores,
                                                std::map<int, std::list<int>>& lista_adj,
                                                std::vector<std::pair<int, int>>& arestas_retorno) {
    visitados[u] = true;
    
    std::cout << (u + 1) << " ";

    

    for (int v : lista_adj[u]) {
        if (!visitados[v]) {
            predecessores[v] = u;
            busca_profundidade_lista_adj_recursiva_util(v, visitados, predecessores, lista_adj, arestas_retorno);
        } else if (predecessores[u] != v) {
            if (u < v) {
                arestas_retorno.push_back({u, v});
            }
        }
    }
}

void exportar_arvore_profundidade_para_dot(const std::string& filename,
                                            std::map<int, int> arvore, 
                                            const std::vector<std::pair<int, int>>& arestas_retorno) {
    std::ofstream file(filename);
    file << "graph Arvore_DFS {\n";
    file << "  rankdir=TB; \n";

    int vertice = 0;
    for (auto it = arvore.begin(); it != arvore.end(); it++, vertice++) {
        file << "  " << vertice + 1 << ";\n";
    }

    for (const auto& par : arvore) {
        if (par.second == -1) continue;
        file << "  " << par.second + 1 << " -- " << par.first + 1 << ";\n";
    }

    file << "\n  // Arestas de Retorno\n";
    for (const auto& aresta : arestas_retorno) {
        // MODIFICADO: '--' e estilo tracejado/colorido
        file << "  " << aresta.first + 1 << " -- " << aresta.second + 1
             << " [style=dashed, color=darkorchid, constraint=false];\n";
    }

    file << "}\n";
    file.close();
}