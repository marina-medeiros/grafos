#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include "../headers/busca-profundidade-digrafo.h"
#include "../headers/DigrafoListaAdj.h"


/** 
 * Realiza a busca em profundidade (DFS) em um digrafo a partir de um vértice inicial.
 * Constrói uma árvore de busca e classifica as arestas do digrafo. 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao digrafo.
 *   verticeInicial - Índice do vértice inicial para a DFS.
 * Retorno:
 *   Um par contendo:
 *     - Um mapa onde a chave é o índice do vértice e o valor é o índice do predecessor na árvore DFS.
 *     - Um vetor de pares representando as arestas de retorno (ciclos) encontradas durante a DFS.
 */
ArvoreBusca busca_profundidade_digrafo_completa(Grafo& grafo, int verticeInicial){
    int qtd_vertices = grafo.get_qtd_vertices();
    std::vector<bool> visitado(qtd_vertices, false);

    ArvoreBusca arvore(qtd_vertices);
    auto rotulos_grafo = grafo.get_rotulos();
    arvore.set_rotulos(rotulos_grafo);

    std::vector<Cor> cores(qtd_vertices, Cor::BRANCO);
    int tempo1 = 0;
    int tempo2 = 0;

    //std::cout << "\n--- Iniciando Busca em Profundidade de um Digrafo (com análise de arestas) a partir de " << rotulos_grafo[verticeInicial]<< " ---\n";
    
    busca_profundidade_digrafo_rec(verticeInicial, grafo, cores, arvore, tempo1, tempo2);
   
    for(int i = 0; i < qtd_vertices; i++){
        if(cores[i] == Cor::BRANCO){
            busca_profundidade_digrafo_rec(i, grafo, cores, arvore, tempo1, tempo2);
        }
    }
    //std::cout << "\n--- Fim da Execucao da DFS ---\n\n";
    
    

    // std::cout << "----------------------------------------------------------------------\n";
    // std::cout << "Vertice | Predecessor | Tempo Entrada (PE) | Tempo Saida (PS)\n";
    // std::cout << "----------------------------------------------------------------------\n";
    // for(int i = 0; i < qtd_vertices; ++i) {
    //     std::cout << std::setw(8) << std::left << rotulos_grafo[i] << "| "
    //               << std::setw(12) << std::left << (arvore.get_predecessores()[i] == -1 ? "Raiz" : rotulos_grafo[arvore.get_predecessores()[i]]) << "| "
    //               << std::setw(19) << std::left << arvore.get_tempo_entrada()[i] << "| "
    //               << std::setw(15) << std::left << arvore.get_tempo_saida()[i] << std::endl;
    // }
    // std::cout << "----------------------------------------------------------------------\n";
    return arvore;
}

/** 
 * Função recursiva auxiliar para a busca em profundidade (DFS).
 * Marca os vértices conforme são visitados e classifica as arestas.
 * 
 * Parâmetros:
 *   ultimoVertice - Índice do vértice atualmente sendo visitado.
 *   grago - Referência ao digrafo.
 *   cores - Vetor que mantém o estado de cada vértice (BRANCO, CINZA, PRETO).
 *   arvore - Objeto ArvoreBusca onde a estrutura da árvore DFS é armazenada.
 *   tempo1 - Referência para o contador de tempo de entrada.
 *   tempo2 - Referência para o contador de tempo de saída.
 * Retorno:
 *   Nenhum. A função modifica diretamente os parâmetros passados por referência.
 */
void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    Grafo& grafo,
                                    std::vector<Cor>& cores,
                                    ArvoreBusca& arvore,
                                    int& tempo1, int& tempo2){
    cores[ultimoVertice] = Cor::CINZA; // Marca como 'visitando'
    tempo1++;
    arvore.set_tempo_entrada(ultimoVertice, tempo1);

    //std::cout << "Visitando vertice " << ultimoVertice << " [PE=" << arvore.get_tempo_entrada()[ultimoVertice] << "]\n";
    
    for(int vizinho : grafo.get_vizinhos(ultimoVertice)) {
        //std::cout << "  Aresta (" << ultimoVertice  << " -> " << vizinho << "): ";

        if (cores[vizinho] == Cor::BRANCO) {
            //std::cout << "ARESTA DE ARVORE\n";
            arvore.adicionar_predecessor(vizinho, ultimoVertice);
            busca_profundidade_digrafo_rec(vizinho, grafo, cores, arvore, tempo1, tempo2);
        }
        else if (cores[vizinho] == Cor::CINZA) {
           // std::cout << "ARESTA DE RETORNO (Ciclo detectado!)\n";
            arvore.adicionar_aresta_retorno(ultimoVertice, vizinho);
        }
        else { // Cor::PRETO
            if (arvore.get_tempo_entrada()[ultimoVertice] < arvore.get_tempo_entrada()[vizinho]) {
              //  std::cout << "ARESTA DE AVANCO\n";
                arvore.adicionar_aresta_avanco(ultimoVertice, vizinho);
            } else {
               // std::cout << "ARESTA DE CRUZAMENTO\n";
                arvore.adicionar_aresta_cruzamento(ultimoVertice, vizinho);
            }
        }
    }
    cores[ultimoVertice] = Cor::PRETO; // Marca como 'finalizado'
    tempo2++;
    arvore.set_tempo_saida(ultimoVertice, tempo2);
}


/**
 * Exporta a árvore gerada pela busca em profundidade (DFS) para um arquivo DOT.
 * A árvore é representada com diferentes estilos de arestas para indicar relações
 * como pai-filho, irmãos, primos e tios.
 * 
 * Parâmetros:
 *   filename - Nome do arquivo de saída onde o grafo será salvo.
 *   arvore - Objeto ArvoreBusca contendo a estrutura da árvore DFS.
 * Retorno:
 *   Nenhum.
 */
void exportar_arvore_dfs_para_dot(const std::string& filename,
                                           ArvoreBusca arvore) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph Arvore_DFS {\n";
    file << "  rankdir=TB;\n";

    for (int i = 0; i < arvore.get_qtd_vertices(); i++) {
    file << "  " << i
            << " [label=\"" << arvore.get_rotulos().at(i)
            << "\", shape=circle];\n";
    }

    const auto& predecessores = arvore.get_predecessores();
    const auto& arestas_retorno = arvore.get_arestas_retorno();
    const auto& arestas_avanco = arvore.get_arestas_avanco();
    const auto& arestas_cruzamento = arvore.get_arestas_cruzamento();
    
    // 1. RECONSTRUIR A ÁRVORE PARA ORDENAÇÃO
    std::map<int, std::vector<int>> arvore_adj;
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
            file << "  " << pai << " -> " << filho << " [color=black, penwidth=2];\n";
        }
    }
    file << "\n";

    // Desenha as outras arestas
    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first << " -> " << aresta.second << " [color=darkorchid, style=dashed, constraint=false];\n";
    }
    for (const auto& aresta : arestas_avanco) {
        file << "  " << aresta.first << " -> " << aresta.second << " [color=darkgreen, style=dashed, constraint=false];\n";
    }
    for (const auto& aresta : arestas_cruzamento) {
        file << "  " << aresta.first << " -> " << aresta.second << " [color=darkgoldenrod, style=dashed, constraint=false];\n";
    }
    file << "\n";
    
    // 2. ADICIONAR RESTRIÇÕES DE ORDENAMENTO
    for (const auto& par : arvore_adj) {
        const std::vector<int>& filhos = par.second;
        if (filhos.size() > 1) {
            file << "  { rank=same; ";
            for (size_t i = 0; i < filhos.size() - 1; ++i) {
                file << filhos[i] << " -> " << filhos[i+1] << " [style=invis]; ";
            }
            file << "}\n";
        }
    }

    file << "}\n";
    file.close();

    std::cout << "\nÁrvore DFS exportada para: " << filename << std::endl;
}