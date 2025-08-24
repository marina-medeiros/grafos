#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/grafo.h"

void Grafo::inserir_vertice(){
    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);

    for(auto& row : matriz_adj){
        row.resize(qtd_vertices, 0);
    }
}

//remove linha e coluna correspondente ao vértice na matriz de adjacência
void Grafo::remover_vertice(int v){
    matriz_adj.erase(matriz_adj.begin() + v-1);

    for(int ii = 0; ii < qtd_vertices-1; ii++){
        matriz_adj[ii].erase(matriz_adj[ii].begin() + v-1);
    }

    qtd_vertices--;

    matriz_adj.resize(qtd_vertices);

    for(auto& row : matriz_adj){
        row.resize(qtd_vertices, 0);
    }
}

void Grafo::inserir_aresta_dir(int u, int v, int peso){
    matriz_adj[u-1][v-1] = peso;
}

void Grafo::inserir_aresta_ndir(int u, int v, int peso){
    matriz_adj[u-1][v-1] = peso;
    matriz_adj[v-1][u-1] = peso;
}

void Grafo::remover_aresta_dir(int u, int v){
    matriz_adj[u-1][v-1] = 0;
}

void Grafo::remover_aresta_ndir(int u, int v){
    matriz_adj[u-1][v-1] = 0;
    matriz_adj[v-1][u-1] = 0;
}

void Grafo::gerar_matriz_inc(int dir){
    matriz_inc.clear();
    for(int ii = 0; ii < qtd_vertices; ii++){
        for(int jj = 0; jj < qtd_vertices; jj++){
            if(matriz_adj[ii][jj] != 0){
                std::vector<int> aresta(qtd_vertices);
                aresta[ii] = matriz_adj[ii][jj];
                if(dir){
                    aresta[jj] = -1 * matriz_adj[ii][jj];
                }else{
                    aresta[jj] = matriz_adj[ii][jj];
                }
                matriz_inc.push_back(aresta);
            }
        }
    }
}

void Grafo::gerar_lista_adj(){
    for(int ii = 0; ii < qtd_vertices; ii++){
        for(int jj = 0; jj < qtd_vertices; jj++){
            if( matriz_adj[ii][jj] != 0){
                lista_adj[ii].push_back(jj);
            }
        }
    }
}

void Grafo::print_matriz_adj(){
    std::cout << "    ";
    for(int ii = 0; ii < qtd_vertices; ii++){
        std::cout << ii+1 << " ";
    }
    std::cout << std::endl << std::endl;
    for(int ii = 0; ii < qtd_vertices; ii++){
        std::cout << (ii + 1) << "   ";
        for(int jj = 0; jj < qtd_vertices; jj++){
            std::cout << matriz_adj[ii][jj] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grafo::print_lista_adj(){
    for(auto i : lista_adj){
        std::cout << (i.first)+1 << " -> ";
        for(auto j : i.second){
            std::cout << j+1 << " ";
        }
        std::cout << std::endl;
    }
}

void Grafo::print_matrix_inc(){
    std::cout << "      ";

    for(int ii = 0; ii < qtd_vertices; ii++){
        std::cout << ii+1 << "  ";
    }

    std::cout << std::endl << std::endl;

    for(int ii = 0; ii < int(matriz_inc.size()); ii++){
        std::cout << "a" << (ii + 1) << "   ";

        for(int jj = 0; jj < qtd_vertices; jj++){
            if(matriz_inc[ii][jj] > -1){
                std::cout << " ";
            }
            std::cout << matriz_inc[ii][jj] << " ";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grafo::exportar_para_dot(const std::string& filename, int dir){
    std::ofstream file(filename);
    if(dir){
        file << "digraph G {\n";
    }else{
        file << "graph G {\n";
    }
    
    for(int i = 0; i < qtd_vertices; i++){
        file << "  " << i+1 << ";\n"; // declara o vértice
    }

    for(int i = 0; i < qtd_vertices; i++){
        for(int j = 0; j < qtd_vertices; j++){ 
            if(matriz_adj[i][j] != 0){
                if(dir){
                    file << "  " << i+1 << " -> " << j+1 << ";\n"; // direcionado
                }else if(j > i){
                    file << "  " << i+1 << " -- " << j+1 << ";\n"; // não-direcionado
                }
            }
        }
    }

    file << "}\n";
}