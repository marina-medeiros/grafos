#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/arvore-largura.h"

const int ArvoreLargura::INF = std::numeric_limits<int>::max() / 2;


/** 
 *  Insere um novo vértice na árvore, atualizando a matriz de adjacência.
 *  A nova linha e coluna são inicializadas com zeros.
 *
 *  Parâmetros:
 *    Nenhum.
 *  Retorno:
 *    Nenhum.
 */
void ArvoreLargura::inserir_vertice() {
    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);

    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, INF);
    }
}

/** 
 *  Remove um vértice da árvore, eliminando a linha e coluna correspondente na matriz de adjacência.
 *
 *  Parâmetros:
 *    v - Índice do vértice a ser removido (1-based).
 *  Retorno:
 *    Nenhum.
 */
void ArvoreLargura::remover_vertice(int v) {
    if (v <= 0 || v > qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    }

    matriz_adj.erase(matriz_adj.begin() + v-1);
    
    for (int ii = 0; ii < qtd_vertices-1; ii++){
        matriz_adj[ii].erase(matriz_adj[ii].begin() + v-1);
    }

    qtd_vertices--;
}

/**
 * Insere uma aresta não direcionada entre os vértices u e v com o peso especificado.
 * 
 * Parâmetros:
 *   u - Índice do primeiro vértice (1-based).
 *   v - Índice do segundo vértice (1-based).
 *   peso - Peso da aresta a ser inserida.
 * Retorno: 
 *  Nenhum.
 */
void ArvoreLargura::inserir_aresta_ndir(int u, int v, int peso) {
    matriz_adj[u-1][v-1] = peso;
    matriz_adj[v-1][u-1] = peso;
}

/**
 * Remove a aresta não direcionada entre os vértices u e v.
 * 
 * Parâmetros:
 *   u - Índice do primeiro vértice (1-based).
 *   v - Índice do segundo vértice (1-based).
 * Retorno: 
 *  Nenhum.
 */
void ArvoreLargura::remover_aresta_ndir(int u, int v) {
    matriz_adj[u-1][v-1] = INF;
    matriz_adj[v-1][u-1] = INF;
}

/**
 * Exporta a árvore gerada pela busca em largura (BFS) para um arquivo DOT.
 * A árvore é representada com diferentes estilos de arestas para indicar relações
 * como pai-filho, irmãos, primos e tios.
 * 
 * Parâmetros:
 *   arvore - Objeto ArvoreLargura contendo a estrutura da árvore BFS.
 *   filename - Nome do arquivo de saída onde o grafo será salvo.
 * Retorno:
 *   Nenhum.
 */
void ArvoreLargura::exportar_arvore_bfs(ArvoreLargura arvore, const std::string& filename) {
    std::ofstream file(filename);
    file << "graph BFS_Arvore {\n";
    file << "  rankdir=TB;\n"; 

    int qtd = arvore.get_qtd_vertices();
    for (int i = 0; i < qtd; i++) {
        file << "  " << i
             << " [label=\"" << rotulos.at(i)
             << "\", shape=circle];\n";
    }

    auto matriz = arvore.get_matriz_adj();
    for (int i = 0; i < qtd; i++) {
        for (int j = i+1; j < qtd; j++) {
            if (matriz[i][j] != INF) {
                file << "  " << i << " -- " << j; 
                if (matriz[i][j] == 1) 
                    file << " [color=black, penwidth=2];\n";   // árvore (pai-filho)
                else if (matriz[i][j] == 2) 
                    file << " [color=darkgreen, style=dashed];\n";  // irmãos
                else if (matriz[i][j] == 3) 
                    file << " [color=darkgoldenrod2	, style=dashed];\n"; // primos
                else if (matriz[i][j] == 4) 
                    file << " [color=darkorchid2, style=dashed];\n";     // tios
                else 
                    file << ";\n";
            }
        }
    }

    // Agrupa vértices por nível (rank = same)
    int maxNivel = 0;
    for (int i = 0; i < qtd; i++) {
        maxNivel = std::max(maxNivel, arvore.get_nivel(i));
    }

    for (int d = 0; d <= maxNivel; d++) {
        file << "  { rank = same; ";
        for (int i = 0; i < qtd; i++) {
            if (arvore.get_nivel(i) == d) file << i << "; ";
        }
        file << "}\n";
    }

    file << "}\n";
}