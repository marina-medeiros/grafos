#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-profundidade-digrafo.h"


void busca_profundidade_digrafo_completa(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    std::cout << "\n--- Iniciando Busca em Profundidade de um Digrafo a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";
    
    busca_profundidade_digrafo_rec(verticeInicial, visitado, predecessor, lista_adj);
    
    for(int i = 0; i < grafo.get_qtd_vertices(); i++){
        if(!visitado[i]){
            busca_profundidade_digrafo_rec(i, visitado, predecessor, lista_adj);
        }
    }
    
    std::cout << "Lista de predecessores: ";
        for(int v = 0; v < grafo.get_qtd_vertices(); v++){
            std::cout << predecessor[v]+1 << " ";
        }

    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(int i = 0; i < grafo.get_qtd_vertices(); ++i) {
        if(visitado[i]) {
            std::cout << "| " << i+1 << "\t| "
                      << (predecessor[i] == -1 ? "Raiz" : std::to_string(predecessor[i] + 1)) << "\t  | "
                      <<  std::endl;
        }
    }
    std::cout << "---------------------\n";

}

void busca_profundidade_digrafo_rec(int ultimoVertice, std::vector<bool> &visitado,
                                        std::vector<int> &predecessor, 
                                        std::map<int, std::list<int>> &lista_adj){
    visitado[ultimoVertice] = true;
    std::cout << (ultimoVertice + 1) << " ";

    for(int vizinho : lista_adj[ultimoVertice]) { 
        if(!visitado[vizinho]) { 
            predecessor[vizinho] = ultimoVertice; 
            busca_profundidade_digrafo_rec(vizinho, visitado, predecessor, lista_adj);
        }
    }
}