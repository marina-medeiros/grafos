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
    std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();

    std::cout << "Ordem de visitação:" << std::endl;
    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();

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

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    std::cout << "Ordem de visitação:" << std::endl;
    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();
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

// Implemente o algoritmo para a busca em largura com arestas de retorno e classificando as arestas como **pai, tio, irmão ou primo**.
Grafo busca_largura_arestas_retorno(Grafo grafo, int verticeInicial){
    Grafo arvore(grafo.get_qtd_vertices());
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::queue<int> fila;
    int peso = 1;

    visitado[verticeInicial] = true;
    fila.push(verticeInicial);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    while(!fila.empty()){
        int verticeAtual = fila.front();
        fila.pop();
        std::cout<< "Vértice atual: " << verticeAtual+1 << std::endl;
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                std::cout<< "Pai/filho: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, 1);
                predecessor[vizinho] = verticeAtual;
                fila.push(vizinho);
            }else{
                if(arvore.get_matriz_adj()[verticeAtual][vizinho] == 0){
                    if(predecessor[verticeAtual] == predecessor[vizinho]){
                        std::cout << predecessor[verticeAtual]+1 << " " << predecessor[vizinho]+1 << std::endl;
                        std::cout<< "Irmãos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 2; 
                    }
                    if(predecessor[predecessor[verticeAtual]] == predecessor[predecessor[vizinho]] && predecessor[predecessor[verticeAtual]] != -1){
                        std::cout << predecessor[predecessor[verticeAtual]]+1 << " " << predecessor[predecessor[vizinho]]+1 << std::endl;
                        std::cout<< "Primos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 3; 
                    }
                    if(predecessor[verticeAtual] == predecessor[predecessor[vizinho]]){
                        std::cout << predecessor[verticeAtual]+1 << " " << predecessor[predecessor[vizinho]]+1 << std::endl;
                        std::cout<< "Tio/sobrinho: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 4; 
                    }
                    arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, peso);
                }
            }
        }
    }

    return arvore;
}