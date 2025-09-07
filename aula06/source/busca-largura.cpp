#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-largura.h"

// Implemente o algoritmo para a busca em largura com matriz de adjacência e sem recorrência.
void busca_largura_matriz_adj_iterativa(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    visitado[verticeInicial] = true;

    std::queue<int> fila;

    fila.push(verticeInicial);

    std::cout << "Ordem de visitação:" << std::endl;
    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();

        std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();
        for(int v = 0; v < grafo.get_qtd_vertices(); v++){
            if(!visitado[v] && matriz_adj[verticeAtual][v] != 0){
                visitado[v] = true;
                predecessor[v] = verticeAtual;
                fila.push(v);
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores:" << std::endl;
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
}
// Implemente o algoritmo para a busca em largura com lista de adjacência e com recorrência, salvando o predecessor.
void busca_largura_lista_adj_recorrencia(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);

    visitado[verticeInicial] = true;

    std::queue<int> fila;

    fila.push(verticeInicial);

    std::cout << "Ordem de visitação:" << std::endl;

    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();
        std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                predecessor[vizinho] = verticeAtual;
                fila.push(vizinho);
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores:" << std::endl;
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
}

void busca_largura_arestas_retorno(Grafo grafo, int verticeInicial){
    Grafo arvore;

    
}