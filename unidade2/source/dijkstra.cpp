#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/GrafoListaAdj.h"
#include "../headers/DigrafoMatrizAdj.h"

bool existem_nao_visitados(std::vector<int>& visitados){
    for(int ii = 0; ii < (int)visitados.size(); ii++){
        if(visitados[ii] == 0){
            return true;
        }
    }
    return false;
}

int vertice_com_menor_distancia(std::vector<int>& distancia, std::vector<int>& visitado){
    int indice_menor_distancia = -1;
    for(int ii = 0; ii < (int)visitado.size(); ii++){
        if(visitado[ii] == 0){
            indice_menor_distancia = ii;
            break;
        }
    }

    for(int ii = 0; ii < (int)distancia.size(); ii++){
        if(visitado[ii] == 0){
            if(distancia[ii] < distancia[indice_menor_distancia]){
                indice_menor_distancia = ii;
            }
        }
    }

    return indice_menor_distancia;
}

void imprimir_tabela_dijkstra(std::vector<int>& distancia, std::vector<int>& visitado, std::vector<int>& predecessor, const std::vector<std::string>& rotulos){
    std::cout << std::endl << "Vértices     | ";
    for(int ii = 0; ii < (int)visitado.size(); ii++){
        if((ii+1) < 10 && (ii+1) >= 0){ std::cout << " ";}
        if((ii+1) < 100){ std::cout << " ";}
        std::cout << ii+1 << " ";
    }
    std::cout << std::endl;
    std::cout << "Visitado     | ";
    for(int ii = 0; ii < (int)visitado.size(); ii++){
        if(visitado[ii] < 10 && visitado[ii] >= 0){ std::cout << " ";}
        if(visitado[ii] < 100){ std::cout << " ";}
        std::cout << visitado[ii] << " ";
    }
    std::cout << std::endl;
    std::cout << "Predecessor  | ";
    for(int ii = 0; ii < (int)predecessor.size(); ii++){
        if (predecessor[ii]+1 == 0) {
            std::cout << "  - ";
        }else{
        if(predecessor[ii]+1 < 10 && predecessor[ii]+1 >= 0){ std::cout << " ";}
        if(predecessor[ii]+1 < 100){ std::cout << " ";}
            std::cout << predecessor[ii]+1 << " ";
        }
    }
    std::cout << std::endl;
    std::cout << "Distância    | ";
    for(int ii = 0; ii < (int)distancia.size(); ii++){

        if (distancia[ii] == GrafoMatrizAdj::INF) {
            std::cout << " INF ";
        } else {
            if(distancia[ii] < 10 && distancia[ii] >= 0){ std::cout << " ";}
            if(distancia[ii] < 100){ std::cout << " ";}
            std::cout << distancia[ii] << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

std::vector<int> dijkstra_geral(const DigrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial){
    int qtd_vertices = grafoMatrizAdj.get_qtd_vertices();
    std::vector<std::vector<int>> matriz_adj = grafoMatrizAdj.get_matriz_adj();
    const std::vector<std::string>& rotulos = grafoMatrizAdj.get_rotulos();

    std::vector<int> distancia(qtd_vertices, GrafoMatrizAdj::INF);
    std::vector<int> predecessor(qtd_vertices, -1);
    std::vector<int> visitado(qtd_vertices, 0);

    visitado[vertice_inicial] = 1;
    distancia[vertice_inicial] = 0;

    for(int ii = 0; ii < qtd_vertices; ii++){
        if(matriz_adj[vertice_inicial][ii] != GrafoMatrizAdj::INF){
            predecessor[ii] = vertice_inicial;
            distancia[ii] = matriz_adj[vertice_inicial][ii];
        }
    }

    while(existem_nao_visitados(visitado)){
        int vertice = vertice_com_menor_distancia(distancia, visitado);
        if(vertice == -1){
            break;
        }

        if (distancia[vertice] == GrafoMatrizAdj::INF) {
            break;
        }

        visitado[vertice] = 1;

        for(int ii = 0; ii < qtd_vertices; ii++){
            if(matriz_adj[vertice][ii] != GrafoMatrizAdj::INF){
                if(visitado[ii] == 0){
                    if(distancia[ii] > (distancia[vertice] + matriz_adj[vertice][ii])){
                        distancia[ii] = (distancia[vertice] + matriz_adj[vertice][ii]);
                        predecessor[ii] = vertice;
                    }
                }
            }
        } 
    }

    std::cout << "Dijkstra: menor distância do vértice " << (vertice_inicial+1) << " para os demais" << std::endl;
    imprimir_tabela_dijkstra(distancia, visitado, predecessor,rotulos);

    return distancia;
}

std::vector<int> dijkstra_especifico(const DigrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial, int vertice_final){
    int qtd_vertices = grafoMatrizAdj.get_qtd_vertices();
    std::vector<std::vector<int>> matriz_adj = grafoMatrizAdj.get_matriz_adj();
    const std::vector<std::string>& rotulos = grafoMatrizAdj.get_rotulos();

    std::vector<int> distancia(qtd_vertices, GrafoMatrizAdj::INF);
    std::vector<int> predecessor(qtd_vertices, -1);
    std::vector<int> visitado(qtd_vertices, 0);

    visitado[vertice_inicial] = 1;
    distancia[vertice_inicial] = 0;

    for(int ii = 0; ii < qtd_vertices; ii++){
        if(matriz_adj[vertice_inicial][ii] != GrafoMatrizAdj::INF){
            predecessor[ii] = vertice_inicial;
            distancia[ii] = matriz_adj[vertice_inicial][ii];
        }
    }

    while(visitado[vertice_final] == 0){
        int vertice = vertice_com_menor_distancia(distancia, visitado);

        if(distancia[vertice] == GrafoMatrizAdj::INF){
            break;
        }

        visitado[vertice] = 1;
        for(int ii = 0; ii < qtd_vertices; ii++){
            if(matriz_adj[vertice][ii] != GrafoMatrizAdj::INF){
                if(visitado[ii] == 0){
                    if(distancia[ii] > (distancia[vertice] + matriz_adj[vertice][ii])){
                        distancia[ii] = (distancia[vertice] + matriz_adj[vertice][ii]);
                        predecessor[ii] = vertice;
                    }
                }
            }
        }
    }

    std::cout << "Dijkstra: menor distância do vértice " << vertice_inicial+1 << " para " << vertice_final+1 << std::endl;

    if(distancia[vertice_final] == GrafoMatrizAdj::INF){
        std::cout << "Não há caminho entre os dois vértices." << std::endl;
    }else{
        std::cout << "Menor distância encontrada: " << distancia[vertice_final] << std::endl << std::endl;
    }

    return distancia;
}