#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include "../headers/busca-largura-digrafo.h"

/** 
 * Verifica se o vértice v_ancestral é um ancestral do vértice u_descendente
 * na árvore definida pelo vetor predecessor.
 * 
 * Parâmetros:
 *   u_descendente - Índice do vértice descendente.
 *   v_ancestral - Índice do vértice ancestral.
 *   predecessor - Vetor onde predecessor[i] é o predecessor do vértice i.
 * Retorno:
 *   true se v_ancestral é um ancestral de u_descendente, false caso contrário.
 */
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

/**
 * Realiza a busca em largura (BFS) em um digrafo a partir de um vértice inicial.
 * Constrói uma árvore de busca e classifica as arestas do digrafo. 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao digrafo representado por DigrafoListaAdj.
 *   verticeInicial - Índice do vértice inicial para a BFS.
 * Retorno:
 *   Um objeto ArvoreBusca representando a árvore gerada pela BFS.
 */
ArvoreBusca busca_largura_digrafo(DigrafoListaAdj& grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::vector<int> nivel(grafo.get_qtd_vertices(), 0);
    
    ArvoreBusca arvore(grafo.get_qtd_vertices());
    auto rotulos_grafo = grafo.get_rotulos();
    arvore.set_rotulos(rotulos_grafo);

    visitado[verticeInicial] = true;
    
    std::queue<int> fila;

    fila.push(verticeInicial); 

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::cout << "\n--- Iniciando Busca em Largura de um Digrafo a partir de " << rotulos_grafo[verticeInicial].c_str() << " ---\n";
    std::cout << "Ordem de visitação: ";

    while(!fila.empty()) { 
        int verticeAtual = fila.front();
        std::cout << rotulos_grafo[verticeAtual] << " ";
        fila.pop(); 
        
        for(int vizinho : lista_adj[verticeAtual]) { 
            if(!visitado[vizinho]) { 
                visitado[vizinho] = true; 
                nivel[vizinho] = nivel[verticeAtual] + 1;

                arvore.set_nivel(vizinho, nivel[verticeAtual] + 1);
                arvore.adicionar_predecessor(vizinho, verticeAtual);
                arvore.adicionar_aresta_arvore(verticeAtual, vizinho);
                fila.push(vizinho);  
            } else {
                if (eh_ancestral(verticeAtual, vizinho, arvore.get_predecessores())) {
                    arvore.adicionar_aresta_retorno(verticeAtual, vizinho);
                } else if (eh_ancestral(vizinho, verticeAtual,  arvore.get_predecessores())) {
                    arvore.adicionar_aresta_avanco(verticeAtual, vizinho);
                } else {
                    arvore.adicionar_aresta_cruzamento(verticeAtual, vizinho);
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

   
    std::cout << std::endl;
    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(int i = 0; i < grafo.get_qtd_vertices(); ++i) {
        if(visitado[i]) {
            std::cout << "| " << rotulos_grafo[i] << "\t| "
                      << (arvore.get_predecessores()[i] == -1 ? "Raiz" : rotulos_grafo[arvore.get_predecessores()[i] + 1]) << "\t  | "
                      <<  std::endl;
        }
    }
    std::cout << "---------------------\n";
    return arvore;
}

/**
 * Exporta a árvore gerada pela busca em largura (BFS) para um arquivo DOT.
 * A árvore é representada com diferentes estilos de arestas para indicar relações
 * como pai-filho, irmãos, primos e tios.
 * 
 * Parâmetros:
 *   filename - Nome do arquivo de saída onde o grafo será salvo.
 *   qtd_vertices - Quantidade de vértices na árvore.
 *   arvore - Objeto ArvoreBusca contendo a estrutura da árvore BFS.
 * Retorno:
 *   Nenhum.
 */
void exportar_arvore_bfs_para_dot(const std::string& filename,
                                  int qtd_vertices,
                                  ArvoreBusca& arvore) {

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph Arvore_BFS {\n";
    file << "  rankdir=TB;\n";

    for (int i = 0; i < qtd_vertices; i++) {
    file << "  " << i
            << " [label=\"" << arvore.get_rotulos().at(i)
            << "\", shape=circle];\n";
    }


    // 1. RECONSTRUIR A ÁRVORE PARA TER ACESSO AOS FILHOS DE CADA NÓ
    // A chave é o nó pai, o valor é um vetor com seus filhos.
    std::map<int, std::vector<int>> arvore_adj;
    for (int i = 0; i < qtd_vertices; ++i) {
        if (arvore.get_predecessores()[i] != -1) {
            // Adiciona o vértice 'i' como filho de seu predecessor
            arvore_adj[arvore.get_predecessores()[i]].push_back(i);
        }
    }
    
    // Desenha as arestas da árvore
    for (int i = 0; i < qtd_vertices; ++i) {
        if (arvore.get_predecessores()[i] != -1) {
            file << "  " << arvore.get_predecessores()[i] << " -> " << i << " [penwidth=2];\n";
        }
    }
    file << "\n";

    // Desenha as outras arestas (retorno, avanço, cruzamento)
    for (const auto& aresta : arvore.get_arestas_retorno()) {
        file << "  " << aresta.first << " -> " << aresta.second << " [style=dashed, color=darkorchid, constraint=false];\n";
    }
    for (const auto& aresta : arvore.get_arestas_avanco()) {
        file << "  " << aresta.first << " -> " << aresta.second << " [style=dashed, color=darkgreen, constraint=false];\n";
    }
    for (const auto& aresta : arvore.get_arestas_cruzamento()) {
        file << "  " << aresta.first << " -> " << aresta.second << " [style=dashed, color=darkgoldenrod, constraint=false];\n";
    }
    file << "\n";

    // 2. ADICIONAR RESTRIÇÕES DE ORDENAMENTO COM ARESTAS INVISÍVEIS
    // Isso força os filhos a aparecerem na ordem em que foram adicionados.
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

    std::cout << "\nÁrvore BFS exportada para: " << filename << std::endl;
}