#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include "../headers/busca-profundidade-digrafo.h"
#include "../headers/DigrafoListaAdj.h"
// #include "../headers/arvore_busca.h"



ArvoreBusca busca_profundidade_digrafo_completa(DigrafoListaAdj& grafo, int verticeInicial){
    int qtd_vertices = grafo.get_qtd_vertices();
    std::vector<bool> visitado(qtd_vertices, false);
    std::vector<int> predecessor(qtd_vertices, -1);

    ArvoreBusca arvore(qtd_vertices);

    std::map<int, int> predecessores;
    predecessores[verticeInicial - 1] = -1; 
    
    // std::vector<std::pair<int, int>> arestas_retorno;
    // std::vector<std::pair<int, int>> arestas_avanco;
    // std::vector<std::pair<int, int>> arestas_cruzamento;

    std::vector<Cor> cores(qtd_vertices, Cor::BRANCO);
    // std::vector<int> tempo_entrada(qtd_vertices, 0);
    // std::vector<int> tempo_saida(qtd_vertices, 0);
    int tempo1 = 0;
    int tempo2 = 0;

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    std::cout << "\n--- Iniciando Busca em Profundidade de um Digrafo (com analise de arestas) a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";
    
    // if (cores[verticeInicial] == Cor::BRANCO) {
        busca_profundidade_digrafo_rec(verticeInicial, lista_adj, cores, arvore, tempo1, tempo2);
    // }
    
    for(int i = 0; i < qtd_vertices; i++){
        if(cores[i] == Cor::BRANCO){
            busca_profundidade_digrafo_rec(i, lista_adj, cores, arvore, tempo1, tempo2);
        }
    }
    std::cout << "\n--- Fim da Execucao da DFS ---\n\n";
    
    

    std::cout << "----------------------------------------------------------------------\n";
    std::cout << "Vertice | Predecessor | Tempo Entrada (PE) | Tempo Saida (PS)\n";
    std::cout << "----------------------------------------------------------------------\n";
    for(int i = 0; i < qtd_vertices; ++i) {
        std::cout << std::setw(8) << std::left << i + 1 << "| "
                  << std::setw(12) << std::left << (arvore.get_predecessores()[i] == -1 ? "Raiz" : std::to_string(arvore.get_predecessores()[i] + 1)) << "| "
                  << std::setw(19) << std::left << arvore.get_tempo_entrada()[i] << "| "
                  << std::setw(15) << std::left << arvore.get_tempo_saida()[i] << std::endl;
    }
    std::cout << "----------------------------------------------------------------------\n";
    
    // Chama a função para gerar o arquivo .dot da árvore
    // exportar_arvore_dfs_para_dot("arvore_dfs_dirt.dot", arvore);
    
    // gerar_imagem_dsfd("arvore_dfs_dirt.dot", "arvore_dfs_dirt.png");

    return arvore;
}

void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    std::map<int, std::list<int>>& lista_adj,
                                    std::vector<Cor>& cores,
                                    ArvoreBusca& arvore,
                                    int& tempo1, int& tempo2){
    cores[ultimoVertice] = Cor::CINZA; // Marca como 'visitando'
    tempo1++;
    arvore.set_tempo_entrada(ultimoVertice, tempo1);

    std::cout << "Visitando vertice " << ultimoVertice + 1 << " [PE=" << arvore.get_tempo_entrada()[ultimoVertice] << "]\n";

                                    
    //lista_adj[ultimoVertice].sort();

    // if (ultimoVertice == 0) { // Vamos checar apenas para o vértice 1
    //     std::cout << "\n[PROVA REAL] A ordem de vizinhos para o vertice 1 e: ";
    //     for (int v : lista_adj[ultimoVertice]) {
    //         std::cout << v + 1 << " ";
    //     }
    //     std::cout << "\n\n";
    // }
    
    for(int vizinho : lista_adj[ultimoVertice]) {
        std::cout << "  Aresta (" << ultimoVertice + 1 << " -> " << vizinho + 1 << "): ";

        if (cores[vizinho] == Cor::BRANCO) {
            std::cout << "ARESTA DE ARVORE\n";
            arvore.adicionar_predecessor(vizinho, ultimoVertice);
            busca_profundidade_digrafo_rec(vizinho, lista_adj, cores, arvore, tempo1, tempo2);
        }
        else if (cores[vizinho] == Cor::CINZA) {
            std::cout << "ARESTA DE RETORNO (Ciclo detectado!)\n";
            arvore.adicionar_aresta_retorno(ultimoVertice, vizinho);
        }
        else { // Cor::PRETO
            if (arvore.get_tempo_entrada()[ultimoVertice] < arvore.get_tempo_entrada()[vizinho]) {
                std::cout << "ARESTA DE AVANCO\n";
                arvore.adicionar_aresta_avanco(ultimoVertice, vizinho);
            } else {
                std::cout << "ARESTA DE CRUZAMENTO\n";
                arvore.adicionar_aresta_cruzamento(ultimoVertice, vizinho);
            }
        }
    }
    cores[ultimoVertice] = Cor::PRETO; // Marca como 'finalizado'
    tempo2++;
    arvore.set_tempo_saida(ultimoVertice, tempo2);
    std::cout << "Finalizando vertice " << ultimoVertice + 1 << " [PS=" << arvore.get_tempo_saida()[ultimoVertice] << "]\n";
}



// [REMOVIDO] Versão antiga de exportar_arvore_profundidade_para_dot foi removida para evitar ambiguidade de sobrecarga.

void exportar_arvore_dfs_para_dot(const std::string& filename,
                                           ArvoreBusca arvore) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph Arvore_DFS {\n";
    file << "  rankdir=TB;\n"; // Organiza a árvore de cima para baixo
    file << "  node [shape=circle];\n\n";

    const auto& predecessores = arvore.get_predecessores();
    const auto& arestas_retorno = arvore.get_arestas_retorno();
    const auto& arestas_avanco = arvore.get_arestas_avanco();
    const auto& arestas_cruzamento = arvore.get_arestas_cruzamento();
    
    // 1. RECONSTRUIR A ÁRVORE PARA ORDENAÇÃO (lógica mantida)
    std::map<int, std::vector<int>> arvore_adj;
    // Assumindo que predecessores é um std::vector<int> onde o índice é o filho.
    for (size_t filho = 0; filho < predecessores.size(); ++filho) {
        int pai = predecessores[filho];
        if (pai != -1) {
            arvore_adj[pai].push_back(filho);
        }
    }

    // Desenha as arestas da árvore
    for (size_t filho = 0; filho < predecessores.size(); ++filho) {
        int pai = predecessores[filho];
        if (pai != -1) { // Se o vértice não for uma raiz
            file << "  " << pai + 1 << " -> " << filho + 1 << " [color=black, penwidth=2];\n";
        }
    }
    file << "\n";

    // Desenha as outras arestas (lógica mantida)
    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [color=darkorchid, style=dashed, constraint=false];\n";
    }
    for (const auto& aresta : arestas_avanco) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [color=darkgreen, style=dashed, constraint=false];\n";
    }
    for (const auto& aresta : arestas_cruzamento) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [color=darkgoldenrod, style=dashed, constraint=false];\n";
    }
    file << "\n";
    
    // 2. ADICIONAR RESTRIÇÕES DE ORDENAMENTO (lógica mantida)
    for (const auto& par : arvore_adj) {
        const std::vector<int>& filhos = par.second;
        if (filhos.size() > 1) {
            file << "  { rank=same; ";
            for (size_t i = 0; i < filhos.size() - 1; ++i) {
                file << filhos[i] + 1 << " -> " << filhos[i + 1] + 1 << " [style=invis]; ";
            }
            file << "}\n";
        }
    }

    file << "}\n";
    file.close();

    std::cout << "\nÁrvore DFS exportada para: " << filename << std::endl;
}