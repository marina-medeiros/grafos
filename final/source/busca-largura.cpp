#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../headers/grafo.h"
#include "../headers/busca-largura.h"
#include "../headers/arvore-largura.h"

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
ArvoreLargura busca_largura_arestas_retorno(Grafo grafo, int verticeInicial){
    ArvoreLargura arvore(grafo.get_qtd_vertices());
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::queue<int> fila;
    int peso = 1;

    visitado[verticeInicial] = true;
    arvore.set_nivel(verticeInicial, 0);
    fila.push(verticeInicial);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    while(!fila.empty()){
        int verticeAtual = fila.front();
        fila.pop();
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                arvore.set_nivel(vizinho, arvore.get_nivel(verticeAtual)+1);
                std::cout<< "Pai: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, 1);
                predecessor[vizinho] = verticeAtual;

                fila.push(vizinho);
            }else{
                if(arvore.get_matriz_adj()[verticeAtual][vizinho] == 0){
                    if(arvore.get_nivel(verticeAtual)+1 == arvore.get_nivel(vizinho) &&
                       verticeAtual != predecessor[vizinho]){
                        std::cout<< "Tio: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 4; 
                    }
                    if(predecessor[verticeAtual] == predecessor[vizinho]){
                        std::cout<< "Irmãos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 2; 
                    }
                    if(arvore.get_nivel(vizinho) == arvore.get_nivel(verticeAtual) &&
                       predecessor[verticeAtual] != predecessor[vizinho]){
                        std::cout<< "Primos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 3; 
                    }
                    arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, peso);
                }
            }
        }
    }

    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        std::cout << arvore.get_nivel(ii) << " ";
    }
    std::cout << std::endl;

    return arvore;
}

bool busca_largura_colorida(Grafo& grafo, int v, std::vector<int>& cores) {
    
    std::queue<int> fila;

    cores[v] = 1;
    fila.push(v);

    auto lista_adj = grafo.get_lista_adj();

    //enquanto tivermos elementos para visitar
    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        //vertice u existe na lista_adj?
        if (lista_adj.count(u) == 0) {
            continue; //sem saida
        }

        //percore vertices adjacentes
        for (int adj_v : lista_adj.at(u)) {
            
            //vertice adjacente nao foi colorido
            if (cores[adj_v] == -1) {
                //vertice adjacente recebe cor oposta
                cores[adj_v] = 1 - cores[u];
                fila.push(adj_v);
            }

            //se vertices adjacentes tiverem a mesma cor, então não é bipartido
            else if (cores[adj_v] == cores[u]) {
                return false;
            }
        }
    }
    return true;
}

