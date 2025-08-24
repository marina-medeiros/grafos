#include <iostream>
#include <vector>
#include <utility> // std::pair
#include "../headers/estrela.h"

void Estrela::gerar_estrela(std::vector<std::vector<int>> matriz_adj){
    int qtd_vertices = int(matriz_adj.size());
    
    for(int ii = 0; ii < qtd_vertices; ii++){
        for(int jj = 0; jj < qtd_vertices; jj++){
            if(matriz_adj[ii][jj] != 0){
                pesos.push_back(matriz_adj[ii][jj]);
                inicio_fim.push_back(std::make_pair(ii+1, jj+1));
            }
        }
    }
}

void Estrela::imprimir_estrela(){
    for(int ii = 0; ii < int(pesos.size()); ii++){
        std::cout << pesos[ii] << " | (" << inicio_fim[ii].first << "," << inicio_fim[ii].second << ")" << std::endl;
    }
}