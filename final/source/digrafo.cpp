#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/digrafo.h"


void Digrafo::inserir_aresta(int u, int v, int peso) {
    matriz_adj[u-1][v-1] = peso;
}

void Digrafo::remover_aresta(int u, int v) {
    matriz_adj[u-1][v-1] = 0;
}

// Leva em consideração um valor negativo na origem e positivo no destino
void Digrafo::gerar_matriz_inc() {
    matriz_inc.clear();
    for (int ii = 0; ii < qtd_vertices; ii++) {
        // Se não for direcionado, não precisa checar todas as linhas,
        // pois acaba duplicando o número de arestas
        for (int jj = 0; jj < qtd_vertices; jj++) {
            if (matriz_adj[ii][jj] != 0) {
                std::vector<int> aresta(qtd_vertices);
                aresta[jj] = matriz_adj[ii][jj];
                aresta[ii] = -1 * matriz_adj[ii][jj];
                
                matriz_inc.push_back(aresta);
            }
        }
    }
}


void Digrafo::exportar_para_dot(const std::string& filename) {
    std::ofstream file(filename);
    
    file << "digraph G {\n";
    
    
    for (int i = 0; i < qtd_vertices; i++) {
        file << "  " << i+1 << ";\n"; // declara o vértice
    }

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j = 0; j < qtd_vertices; j++) { 
            if (matriz_adj[i][j] != 0) {
                file << "  " << i+1 << " -> " << j+1 << ";\n"; // direcionado
            }
        }
    }

    file << "}\n";
}