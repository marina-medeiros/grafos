#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-profundidade-digrafo.h"


std::map<int, int> busca_profundidade_digrafo_completa(Grafo& grafo, int verticeInicial){
    int qtd_vertices = grafo.get_qtd_vertices();
    std::vector<bool> visitado(qtd_vertices, false);
    std::vector<int> predecessor(qtd_vertices, -1);

    std::vector<std::pair<int, int>> arestas_retorno;
    std::vector<std::pair<int, int>> arestas_avanco;
    std::vector<std::pair<int, int>> arestas_cruzamento;

    std::vector<Cor> cores(qtd_vertices, Cor::BRANCO);
    std::vector<int> tempo_entrada(qtd_vertices, 0);
    std::vector<int> tempo_saida(qtd_vertices, 0);
    int tempo1 = 0;
    int tempo2 = 0;

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    std::cout << "\n--- Iniciando Busca em Profundidade de um Digrafo (com analise de arestas) a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";
    
    if (cores[verticeInicial] == Cor::BRANCO) {
        busca_profundidade_digrafo_rec(verticeInicial, lista_adj, cores, predecessor, tempo_entrada, tempo_saida, arestas_retorno, arestas_avanco, arestas_cruzamento, tempo1, tempo2);
    }
    
    for(int i = 0; i < qtd_vertices; i++){
        if(cores[i] == Cor::BRANCO){
            busca_profundidade_digrafo_rec(i, lista_adj, cores, predecessor, tempo_entrada, tempo_saida, arestas_retorno, arestas_avanco, arestas_cruzamento, tempo1, tempo2);
        }
    }
    std::cout << "\n--- Fim da Execucao da DFS ---\n\n";
    
    std::map<int, int> predecessores;
    std::cout << "Lista de predecessores: ";
        for(int v = 0; v < qtd_vertices; v++){
            std::cout << predecessor[v]+1 << " ";
            predecessores[v] = predecessor[v];
        }

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Vertice | Predecessor | Tempo Entrada (PE) | Tempo Saida (PS)\n";
    std::cout << "----------------------------------------------------------------------\n";
    for(int i = 0; i < qtd_vertices; ++i) {
        std::cout << std::setw(8) << std::left << i + 1 << "| "
                  << std::setw(12) << std::left << (predecessor[i] == -1 ? "Raiz" : std::to_string(predecessor[i] + 1)) << "| "
                  << std::setw(19) << std::left << tempo_entrada[i] << "| "
                  << std::setw(15) << std::left << tempo_saida[i] << std::endl;
    }
    std::cout << "----------------------------------------------------------------------\n";
    
    // Chama a função para gerar o arquivo .dot da árvore
    exportar_arvore_profundidade_para_dot("arvore_dfs.dot", predecessores, arestas_retorno, arestas_avanco, arestas_cruzamento);
    
    gerar_imagem("arvore_dfs.dot", "arvore_dfs.png");

    return predecessores;
}

void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    std::map<int, std::list<int>>& lista_adj,
                                    std::vector<Cor>& cores,
                                    std::vector<int>& predecessor,
                                    std::vector<int>& tempo_entrada,
                                    std::vector<int>& tempo_saida,
                                    std::vector<std::pair<int, int>>& arestas_retorno,
                                    std::vector<std::pair<int, int>>& arestas_avanco,
                                    std::vector<std::pair<int, int>>& arestas_cruzamento,
                                    int& tempo1, int& tempo2){
    cores[ultimoVertice] = Cor::CINZA; // Marca como 'visitando'
    tempo1++;
    tempo_entrada[ultimoVertice] = tempo1;

    std::cout << "Visitando vertice " << ultimoVertice + 1 << " [PE=" << tempo_entrada[ultimoVertice] << "]\n";

                                    
    lista_adj[ultimoVertice].sort();

    if (ultimoVertice == 0) { // Vamos checar apenas para o vértice 1
        std::cout << "\n[PROVA REAL] A ordem de vizinhos para o vertice 1 e: ";
        for (int v : lista_adj[ultimoVertice]) {
            std::cout << v + 1 << " ";
        }
        std::cout << "\n\n";
    }
    
    for(int vizinho : lista_adj[ultimoVertice]) {
        std::cout << "  Aresta (" << ultimoVertice + 1 << " -> " << vizinho + 1 << "): ";

        if (cores[vizinho] == Cor::BRANCO) {
            std::cout << "ARESTA DE ARVORE\n";
            predecessor[vizinho] = ultimoVertice;
            busca_profundidade_digrafo_rec(vizinho, lista_adj, cores, predecessor, tempo_entrada, tempo_saida, arestas_retorno, arestas_avanco, arestas_cruzamento, tempo1, tempo2);
        }
        else if (cores[vizinho] == Cor::CINZA) {
            std::cout << "ARESTA DE RETORNO (Ciclo detectado!)\n";
            arestas_retorno.push_back({ultimoVertice, vizinho});
        }
        else { // Cor::PRETO
            if (tempo_entrada[ultimoVertice] < tempo_entrada[vizinho]) {
                std::cout << "ARESTA DE AVANCO\n";
                arestas_avanco.push_back({ultimoVertice, vizinho});
            } else {
                std::cout << "ARESTA DE CRUZAMENTO\n";
                arestas_cruzamento.push_back({ultimoVertice, vizinho});
            }
        }
    }
    cores[ultimoVertice] = Cor::PRETO; // Marca como 'finalizado'
    tempo2++;
    tempo_saida[ultimoVertice] = tempo2;
    std::cout << "Finalizando vertice " << ultimoVertice + 1 << " [PS=" << tempo_saida[ultimoVertice] << "]\n";
}



void exportar_arvore_profundidade_para_dot(const std::string& filename, std::map<int, int> predecessores, 
                                                std::vector<std::pair<int, int>> arestas_retorno, 
                                                std::vector<std::pair<int, int>> arestas_avanco, 
                                                std::vector<std::pair<int, int>> arestas_cruzamento) {
    std::ofstream file(filename);
    file << "digraph Arvore_DFS {\n";
    file << "  rankdir=TB;\n"; // Organiza a árvore de cima para baixo
    //file << "  node [shape=circle];\n\n";

    int qtd_vertices = predecessores.size();

    for (int i = 0; i < qtd_vertices; i++) {
        file << "  " << i+1 
             << " [label=\"" << i+1 
             << "\", shape=circle];\n";
    }


    // 1. Desenha as arestas normais da árvore (sólidas, em preto)
    for (const auto& par : predecessores) {
        // par.first é o vértice, par.second é o predecessor
        if (par.second != -1) { // Se o vértice não for uma raiz
            file << "  " << par.second + 1 << " -> " << par.first + 1 << " [color=black, penwidth=2];\n";
        }
    }

    // 2. Desenha as arestas de retorno (tracejadas, em vermelho)
    for (const auto& aresta : arestas_retorno) {
        int origem = aresta.first;
        int destino = aresta.second;
        file << "  " << origem + 1 << " -> " << destino + 1 
             << " [color=darkorchid2, style=dashed];\n";
    }
    for (const auto& aresta : arestas_avanco) {
        int origem = aresta.first;
        int destino = aresta.second;
        file << "  " << origem + 1 << " -> " << destino + 1 
             << " [color=darkgreen, style=dashed];\n";
    }
    for (const auto& aresta : arestas_cruzamento) {
        int origem = aresta.first;
        int destino = aresta.second;
        file << "  " << origem + 1 << " -> " << destino + 1 
             << " [color=darkgoldenrod2, style=dashed];\n";
    }

    file << "}\n";
    file.close();
}