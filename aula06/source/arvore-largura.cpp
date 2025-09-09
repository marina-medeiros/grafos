#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/arvore-largura.h"

void ArvoreLargura::inserir_vertice() {
    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);

    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, 0);
    }
}

// Remove linha e coluna correspondente ao vértice na matriz de adjacência
void ArvoreLargura::remover_vertice(int v) {
    // Validação para evitar erros com índices inválidos
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

void ArvoreLargura::inserir_aresta_ndir(int u, int v, int peso) {
    matriz_adj[u-1][v-1] = peso;
    matriz_adj[v-1][u-1] = peso;
}

void ArvoreLargura::remover_aresta_ndir(int u, int v) {
    matriz_adj[u-1][v-1] = 0;
    matriz_adj[v-1][u-1] = 0;
}

void ArvoreLargura::exportar_arvore_bfs(ArvoreLargura arvore, const std::string& filename) {
    std::ofstream file(filename);
    file << "graph BFS_Arvore {\n";
    file << "  rankdir=TB;\n"; // desenhar árvore de cima para baixo

    int qtd = arvore.get_qtd_vertices();

    // Declara os nós
    for (int i = 0; i < qtd; i++) {
        file << "  " << i+1 
             << " [label=\"" << i+1 
             << "\", shape=circle];\n";
    }

    // Cria arestas da árvore
    auto matriz = arvore.get_matriz_adj();
    for (int i = 0; i < qtd; i++) {
        for (int j = i+1; j < qtd; j++) {
            if (matriz[i][j] != 0) {
                file << "  " << i+1 << " -- " << j+1; // não-direcionado
                // Diferencia tipos de arestas pela cor
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
            if (arvore.get_nivel(i) == d) file << i+1 << "; ";
        }
        file << "}\n";
    }

    file << "}\n";
}