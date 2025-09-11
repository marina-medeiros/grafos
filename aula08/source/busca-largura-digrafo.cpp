#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-largura-digrafo.h"

void busca_largura_digrafo(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    
    // Prepara o vértice inicial
    visitado[verticeInicial] = true;
    
    std::queue<int> fila;

    fila.push(verticeInicial); // ENFILEIRA(F,s) 

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::cout << "\n--- Iniciando Busca em Largura de um Digrafo a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";

    while(!fila.empty()) { 
        int verticeAtual = fila.front();
        std::cout << verticeAtual + 1 << " ";
        fila.pop(); 
        
        for(int vizinho : lista_adj[verticeAtual]) { 
            if(!visitado[vizinho]) { 
                visitado[vizinho] = true; 
                predecessor[vizinho] = verticeAtual; 
                fila.push(vizinho); 
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

    std::cout << "Lista de predecessores: ";
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
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