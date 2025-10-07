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
    if (u > 0 && u <= get_qtd_vertices() && v > 0 && v <= get_qtd_vertices()) {
        
        // A LINHA CRUCIAL: converter de base-1 para base-0 antes de acessar a matriz
        // Note que, por ser um dígrafo, só alteramos uma posição.
        matriz_adj[u - 1][v - 1] = peso;

    } else {
        std::cerr << "ERRO (Digrafo): Tentativa de inserir aresta com vertice invalido. u=" 
                  << u << ", v=" << v << std::endl;
    }
}

void Digrafo::remover_aresta(int u, int v) {
    if (u > 0 && u <= get_qtd_vertices() && v > 0 && v <= get_qtd_vertices()) {
        
        // A LINHA CRUCIAL: converter de base-1 para base-0 antes de acessar a matriz
        // Note que, por ser um dígrafo, só alteramos uma posição.
        matriz_adj[u - 1][v - 1] = 0;

    } else {
        std::cerr << "ERRO (Digrafo): Tentativa de inserir aresta com vertice invalido. u=" 
                  << u << ", v=" << v << std::endl;
    }
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
    
    file << "  rankdir=TB;\n"; 
    file << "  overlap=false;\n\n";

    for (int i = 0; i < qtd_vertices; i++) {
        std::string rotulo = rotulos_vertices[i].empty() ? std::to_string(i + 1) : rotulos_vertices[i];
        file << "  \"" << rotulo << "\";\n"; 
    }
    file << "\n";

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j = 0; j < qtd_vertices; j++) { 
            if (matriz_adj[i][j] != 0) {
                std::string rotulo_i = rotulos_vertices[i].empty() ? std::to_string(i + 1) : rotulos_vertices[i];
                std::string rotulo_j = rotulos_vertices[j].empty() ? std::to_string(j + 1) : rotulos_vertices[j];
                file << "  \"" << rotulo_i << "\" -> \"" << rotulo_j << "\";\n";
            }
        }
    }

    file << "}\n";
}