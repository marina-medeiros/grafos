#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-largura-digrafo.h"

bool eh_ancestral(int u_descendente, int v_ancestral, const std::vector<int>& predecessor) {
    int p = u_descendente;
    while (p != -1) {
        if (p == v_ancestral) {
            return true;
        }
        p = predecessor[p];
    }
    return false;
}

void busca_largura_digrafo(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::vector<int> nivel(grafo.get_qtd_vertices(), 0);
    
    std::vector<std::pair<int, int>> arestas_arvore;
    std::vector<std::pair<int, int>> arestas_retorno;
    std::vector<std::pair<int, int>> arestas_avanco;
    std::vector<std::pair<int, int>> arestas_cruzamento;
    
    visitado[verticeInicial] = true;
    
    std::queue<int> fila;

    fila.push(verticeInicial); 

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::cout << "\n--- Iniciando Busca em Largura de um Digrafo a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";

    while(!fila.empty()) { 
        int verticeAtual = fila.front();
        std::cout << verticeAtual + 1 << " ";
        fila.pop(); 
        
        for(int vizinho : lista_adj[verticeAtual]) { 
            if(!visitado[vizinho]) { 
                visitado[vizinho] = true; 
                predecessor[vizinho] = verticeAtual; 
                nivel[vizinho] = nivel[verticeAtual] + 1;
                arestas_arvore.push_back({verticeAtual, vizinho});
                fila.push(vizinho);  
            } else {
                if (eh_ancestral(verticeAtual, vizinho, predecessor)) {
                    // 2a. ARESTA DE RETORNO (para um ancestral)
                    arestas_retorno.push_back({verticeAtual, vizinho});
                } else if (eh_ancestral(vizinho, verticeAtual, predecessor)) {
                    // 2b. ARESTA DE AVANÇO (para um descendente)
                    arestas_avanco.push_back({verticeAtual, vizinho});
                } else {
                    // 2c. ARESTA DE CRUZAMENTO (outros casos)
                    arestas_cruzamento.push_back({verticeAtual, vizinho});
                }
            }
        }
        if(fila.empty()) {
            for(int i = 0; i < grafo.get_qtd_vertices(); i++) {
                if(!visitado[i]) {
                    fila.push(i);
                    visitado[i] = true;
                    break;
                }
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores: ";
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(int i = 0; i < grafo.get_qtd_vertices(); ++i) {
        if(visitado[i]) {
            std::cout << "| " << i+1 << "\t| "
                      << (predecessor[i] == -1 ? "Raiz" : std::to_string(predecessor[i] + 1)) << "\t  | "
                      <<  std::endl;
        }
    }
    std::cout << "---------------------\n";

    exportar_arvore_bfs_para_dot("arvore_bfs.dot", grafo.get_qtd_vertices(), predecessor, arestas_retorno, arestas_retorno, arestas_avanco, arestas_cruzamento);
    gerar_imagem("arvore_bfs.dot", "arvore_bfs.png");
}

void exportar_arvore_bfs_para_dot(const std::string& filename, 
                                    int qtd_vertices,
                                    std::vector<int> predecessores,
                                    const std::vector<std::pair<int, int>>& arestas_arvore,
                                    const std::vector<std::pair<int, int>>& arestas_retorno,
                                    const std::vector<std::pair<int, int>>& arestas_avanco,
                                    const std::vector<std::pair<int, int>>& arestas_cruzamento) {
                                      
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph Arvore_BFS {\n";
    file << "  rankdir=TB;\n"; // Organiza a árvore de cima para baixo
    file << "  node [shape=circle];\n\n";

    for (int i = 0; i < qtd_vertices; ++i) {
        if (predecessores[i] != -1) { // Se o vértice não for uma raiz
            file << "  " << predecessores[i] + 1 << " -> " << i + 1 << " [penwidth=2];\n";
        }
    }

    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkorchid, constraint=false];\n";
    }

    for (const auto& aresta : arestas_avanco) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgreen, constraint=false];\n";
    }

    for (const auto& aresta : arestas_cruzamento) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgoldenrod, constraint=false];\n";
    }

    file << "}\n";
    file.close();

    std::cout << "\nÁrvore BFS exportada para: " << filename << std::endl;
    
}