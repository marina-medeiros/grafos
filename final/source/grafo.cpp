#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/busca-largura.h"


Grafo::Grafo(int vertices) {
    this->qtd_vertices = vertices;
    // Aqui você pode inicializar suas estruturas de dados.
    // Ex: Se estiver usando matriz de adjacência como no seu Grafo.h original
    matriz_adj.resize(vertices, std::vector<int>(vertices, 0));
}

void Grafo::inserir_vertice() {
    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);

    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, 0);
    }
}

// Remove linha e coluna correspondente ao vértice na matriz de adjacência
void Grafo::remover_vertice(int v) {
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


void Grafo::inserir_aresta(int u, int v, int peso) {
    matriz_adj[u-1][v-1] = peso;
    matriz_adj[v-1][u-1] = peso;
}


void Grafo::remover_aresta(int u, int v) {
    matriz_adj[u-1][v-1] = 0;
    matriz_adj[v-1][u-1] = 0;
}

// Leva em consideração um valor negativo na origem e positivo no destino
void Grafo::gerar_matriz_inc() {
    matriz_inc.clear();
    for (int ii = 0; ii < qtd_vertices; ii++) {
        // Se não for direcionado, não precisa checar todas as linhas,
        // pois acaba duplicando o número de arestas
        for (int jj = ii; jj < qtd_vertices; jj++) {
            if (matriz_adj[ii][jj] != 0) {
                std::vector<int> aresta(qtd_vertices);
                aresta[jj] = matriz_adj[ii][jj];
                aresta[ii] = matriz_adj[ii][jj];
                
                matriz_inc.push_back(aresta);
            }
        }
    }
}

void Grafo::gerar_lista_adj() {
    lista_adj.clear();
    for (int ii = 0; ii < qtd_vertices; ii++) {
        for (int jj = 0; jj < qtd_vertices; jj++) {
            if (matriz_adj[ii][jj] != 0) {
                lista_adj[ii].push_back(jj);
            }
        }
    }
}

void Grafo::print_matriz_adj() {
    std::cout << "    ";
    for (int ii = 0; ii < qtd_vertices; ii++) {
        std::cout << ii+1 << " ";
    }
    std::cout << std::endl << std::endl;
    for (int ii = 0; ii < qtd_vertices; ii++) {
        std::cout << (ii + 1) << "   ";
        for (int jj = 0; jj < qtd_vertices; jj++) {
            std::cout << matriz_adj[ii][jj] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grafo::print_lista_adj() {
    for (auto i : lista_adj) {
        std::cout << (i.first)+1 << " -> ";
        for (auto j : i.second) {
            std::cout << j+1 << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::print_matriz_inc() {
    std::cout << "      ";

    for (int ii = 0; ii < qtd_vertices; ii++) {
        std::cout << ii+1 << "  ";
    }

    std::cout << std::endl << std::endl;

    for (int ii = 0; ii < int(matriz_inc.size()); ii++) {
        std::cout << "a" << (ii + 1) << "   ";

        for (int jj = 0; jj < qtd_vertices; jj++) {
            if (matriz_inc[ii][jj] > -1){
                std::cout << " ";
            }
            std::cout << matriz_inc[ii][jj] << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grafo::exportar_para_dot(const std::string& filename) {
    std::ofstream file(filename);
    
    file << "graph G {\n";
    
    
    for (int i = 0; i < qtd_vertices; i++) {
        file << "  " << i+1 << ";\n"; // declara o vértice
    }

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j = 0; j < qtd_vertices; j++) { 
            if (matriz_adj[i][j] != 0) {
                if (j > i) {
                    file << "  " << i+1 << " -- " << j+1 << ";\n"; 
                }
            }
        }
    }

    file << "}\n";
}

void Grafo::gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}

bool Grafo::isConexo(){

    if (qtd_vertices <= 1) {
        return true;
    }

    std::map<int, int> dfs = busca_profundidade_lista_adj_recursiva(*this, 1);

    int qtd_visitados = dfs.size();

    return qtd_visitados == qtd_vertices;

}

bool Grafo::isBipartido(){

    if (qtd_vertices <= 1) {
        return true;
    }

    std::vector<int> cores(qtd_vertices, -1);

    for (int i = 0; i < qtd_vertices; ++i) {
        
        if (cores[i] == -1) {
            if (!busca_largura_colorida(*this, i, cores)) {
                return false;
            }
        }
    }

    return true;
}