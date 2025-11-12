#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/GrafoListaAdj.h"

/**
 * Realiza a busca em profundidade (DFS) em um grafo a partir de um vértice inicial.
 * Constrói uma árvore de busca. 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao grafo representado por GrafoListaAdj.
 *   vertice_inicial - Índice do vértice inicial para a DFS.
 * Retorno:
 *   Um mapa onde a chave é o índice do vértice e o valor é o índice do predecessor na árvore DFS.
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

/**
 * Realiza a busca em profundidade (DFS) em um grafo a partir de um vértice inicial.
 * Constrói uma árvore de busca e identifica arestas de retorno (back edges). 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao grafo representado por GrafoListaAdj.
 *   vertice - Índice do vértice inicial para a DFS.
 * Retorno:
 *   Um par contendo:
 *     - Um mapa onde a chave é o índice do vértice e o valor é o índice do predecessor na árvore DFS.
 *     - Um vetor de pares representando as arestas de retorno (ciclos) encontradas durante a DFS.
 * 
 */
std::pair<std::map<int, int>, std::vector<std::pair<int, int>>> busca_profundidade_lista_adj_recursiva(GrafoListaAdj grafo, int vertice) {
    int qtd_vertices = grafo.get_qtd_vertices();

    if (vertice < 0 || vertice > qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return {};
    }

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    auto rotulos = grafo.get_rotulos();
    
    std::vector<bool> visitados(qtd_vertices, false);
    std::map<int, int> predecessores;
    for (int i = 0; i < qtd_vertices; i++) {
        predecessores[i] = -1;
    }
    std::vector<std::pair<int, int>> arestas_retorno;

    busca_profundidade_lista_adj_recursiva_util(vertice, visitados, predecessores, lista_adj, arestas_retorno, rotulos);

    std::cout << std::endl;

    // std::cout << std::endl;
    // std::cout << "---------------------\n";
    // std::cout << "Vértice | Predecessor \n";
    // std::cout << "---------------------\n";
    // for(const auto& par : predecessores) {
    //     std::cout << "| " << rotulos[par.first] << "\t| "
    //             << (par.second != -1 ? rotulos[par.second] : "Raiz") << "\t  | "
    //             <<  std::endl;
    // }
    // std::cout << "---------------------\n";

    // std::cout << "\nArestas de Retorno Encontradas:" << std::endl;
    // for (const auto& aresta : arestas_retorno) {
    //     std::cout << "(" << rotulos[aresta.first] << ", " << rotulos[aresta.second] << ")" << std::endl;
    // }

    return {predecessores, arestas_retorno};
}

/**
 * Função recursiva auxiliar para a busca em profundidade (DFS).
 * Marca os vértices conforme são visitados e identifica arestas de retorno (back edges).
 * 
 * Parâmetros:
 *   u - Vértice atual sendo visitado.
 *   visitados - Vetor booleano indicando se cada vértice foi visitado.
 *   predecessores - Mapa onde a chave é o índice do vértice e o valor é o índice do predecessor na árvore DFS.
 *   lista_adj - Mapa representando a lista de adjacência do grafo.
 *   arestas_retorno - Vetor de pares para armazenar as arestas de retorno encontradas.
 *   rotulos - Vetor de rótulos dos vértices para exibição.
 * Retorno:
 *   Nenhum (os resultados são armazenados nos parâmetros por referência).
 */
void busca_profundidade_lista_adj_recursiva_util(int u,
                                                std::vector<bool>& visitados,
                                                std::map<int, int>& predecessores,
                                                std::map<int, std::list<int>>& lista_adj,
                                                std::vector<std::pair<int, int>>& arestas_retorno,
                                                const std::vector<std::string>& rotulos) {
    visitados[u] = true;
    
    //std::cout << rotulos[u] << " ";

    for (int v : lista_adj[u]) {
        if (!visitados[v]) {
            predecessores[v] = u;
            busca_profundidade_lista_adj_recursiva_util(v, visitados, predecessores, lista_adj, arestas_retorno, rotulos);
        } else if (predecessores[u] != v) {
            if (u < v) {
                arestas_retorno.push_back({u, v});
            }
        }
    }
}

void busca_articulacoes_dfs_recursiva(
    const Grafo& grafo,int u, std::vector<int>& disc, std::vector<int>& low, 
    std::vector<int>& parent, std::stack<std::pair<int, int>>& pilha,
    std::set<int>& ap, std::vector<std::set<int>>& blocos, int& tempo) {

    disc[u] = low[u] = tempo++;
    int filhos = 0;

    for (int v : grafo.get_vizinhos(u)) {
        if (v == parent[u]) continue;

        if (disc[v] != -1) { 
            if (disc[v] < disc[u]) { 
                low[u] = std::min(low[u], disc[v]);
                pilha.push({u, v});
            }
        } else { 
            filhos++;
            parent[v] = u;
            pilha.push({u, v});
            
            busca_articulacoes_dfs_recursiva(grafo,v, disc, low, parent, pilha, ap, blocos, tempo);

            low[u] = std::min(low[u], low[v]);

            if ((parent[u] == -1 && filhos > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                ap.insert(u); 

                std::set<int> aux;
                while (true) {
                    std::pair<int, int> edge = pilha.top();
                    pilha.pop();
                    aux.insert(edge.first);
                    aux.insert(edge.second);
                    if ((edge.first == u && edge.second == v) || (edge.first == v && edge.second == u)) {
                        break;
                    }
                }
                blocos.push_back(aux);
            }
        }
    }
}

/**
 * Exporta a árvore de busca em profundidade (DFS) para um arquivo DOT.
 * A árvore é representada com arestas não direcionadas e inclui arestas de retorno.
 * 
 * Parâmetros:
 *   filename - Nome do arquivo de saída onde o grafo será salvo.
 *   arvore - Mapa onde a chave é o índice do vértice e o valor é o índice do predecessor na árvore DFS.
 *   arestas_retorno - Vetor de pares representando as arestas de retorno (ciclos) encontradas durante a DFS.
 *   rotulos - Vetor de rótulos dos vértices para exibição.
 * Retorno:
 *   Nenhum.
 */
void exportar_arvore_profundidade_para_dot(const std::string& filename,
                                            std::map<int, int> arvore, 
                                            const std::vector<std::pair<int, int>>& arestas_retorno,
                                            const std::vector<std::string>& rotulos) {
    std::ofstream file(filename);
    file << "graph Arvore_DFS {\n";
    file << "  rankdir=TB; \n";

    int vertice = 0;
    for (auto it = arvore.begin(); it != arvore.end(); it++, vertice++) {
        file << "    " << vertice << " [label=\"" << rotulos.at(vertice) << "\"];\n";
    }

    file << "\n";

    for (const auto& par : arvore) {
        if (par.second == -1) continue;
        file << "  " << par.second << " -- " << par.first << ";\n";
    }

    file << "\n  // Arestas de Retorno\n";
    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first << " -- " << aresta.second
             << " [style=dashed, color=darkorchid, constraint=false];\n";
    }

    file << "}\n";
    file.close();
}