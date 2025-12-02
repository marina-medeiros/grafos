#include <iostream>
#include <queue>
#include <fstream>

#include "../headers/DigrafoMatrizAdj.h"

/**
 * Descrição:
 *  Insere ou atualiza a aresta u -> v com o peso informado.
 *
 * Parâmetros:
 *  u     - Vértice de origem.
 *  v     - Vértice de destino.
 *  peso  - Peso da aresta.
 *
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizAdj::inserir_aresta(int u, int v, int peso) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] == INF) {
            qtd_arestas++;
        }

        matriz_adj[u][v] = peso;
    }
}

/**
 * Remove uma aresta direcionada do vértice u para o vértice v.
 * Se a aresta não existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizAdj::remover_aresta(int u, int v) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] != INF) {
            qtd_arestas--;
        }
        matriz_adj[u][v] = INF;
    }
}

/**
 * Exporta o grafo para um arquivo no formato DOT, adequado para visualização com Graphviz.
 * 
 * Parâmetros:
 *  filename - Nome do arquivo de saída.
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizAdj::exportar_para_dot_com_pesos(const std::string& filename, bool peso_eh_decimal) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        return;
    }

    file << "digraph G {\n";
    file << "  rankdir=TB;\n"; 
    file << "  overlap=false;\n";


    for (int i = 0; i < qtd_vertices; i++) {
        if (rotulos.at(i).empty()){
            file << "    " << i << " [label=\"" << i+1 << "\"];\n";
        } else {
            file << "    " << i << " [label=\"" << rotulos.at(i) << "\"];\n";
        }
    }
    file << "\n";

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j : get_vizinhos(i)) {
            if (peso_eh_decimal) {
                double peso_long = static_cast<double>(matriz_adj[i][j]);
                peso_long /= 10;
                file << "  " << i << " -> " << j << "[label=\"" << peso_long << "\"];\n"; 
            } else {
                file << "  " << i << " -> " << j << "[label=\"" << matriz_adj[i][j] << "\"];\n"; 
            }
            
        }
    }

    file << "}\n";
    file.close();
}
