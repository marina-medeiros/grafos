#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/GrafoListaAdj.h"
#include "../headers/DigrafoMatrizAdj.h"

/**
 * @brief Verifica se ainda existem vértices não visitados.
 *
 * Percorre o vetor de visitados procurando valores iguais a 0,
 * indicando que o vértice ainda não foi processado pelo algoritmo.
 *
 * @param visitados Vetor onde cada posição indica se o vértice foi visitado (1) ou não (0).
 * @return true Se ainda existe algum vértice não visitado.
 * @return false Se todos os vértices já foram visitados.
 */
bool existem_nao_visitados(std::vector<int>& visitados){
    for(int ii = 0; ii < (int)visitados.size(); ii++){
        if(visitados[ii] == 0){
            return true;
        }
    }
    return false;
}

/**
 * @brief Retorna o índice do vértice com a menor distância entre os não visitados.
 *
 * O algoritmo procura pelo vértice ainda não visitado que possui a menor
 * distância atualmente registrada no vetor de distâncias.
 *
 * @param distancia Vetor contendo as distâncias mínimas conhecidas até o momento.
 * @param visitado Vetor que indica quais vértices já foram visitados.
 * @return int Índice do vértice com menor distância entre os não visitados.
 *         Retorna -1 caso todos os vértices tenham sido visitados.
 */
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
/**
 * @brief Imprime a tabela com os resultados parciais do algoritmo de Dijkstra.
 *
 * Mostra: vértices, estado de visitação, predecessores e distâncias.
 *
 * @param distancia Vetor contendo as distâncias mínimas encontradas.
 * @param visitado Vetor de marcadores indicando quais vértices foram visitados.
 * @param predecessor Vetor com o predecessor de cada vértice no caminho mínimo.
 */
void imprimir_tabela_dijkstra(std::vector<int>& distancia, std::vector<int>& visitado, std::vector<int>& predecessor){
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

/**
 * @brief Executa o algoritmo de Dijkstra calculando as menores distâncias 
 *        do vértice inicial para todos os outros vértices.
 *
 * Esta função implementa a versão "completa" do algoritmo, onde o processo
 * continua até que todos os vértices tenham sido visitados ou não existam
 * mais caminhos possíveis.
 *
 * @param grafoMatrizAdj Objeto representando o grafo (direcionado) em matriz de adjacência.
 * @param vertice_inicial Índice do vértice de origem (base 0).
 * @return std::vector<int> Vetor contendo as menores distâncias até todos os vértices.
 */
std::vector<int> dijkstra_geral(const DigrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial){
    int qtd_vertices = grafoMatrizAdj.get_qtd_vertices();
    std::vector<std::vector<int>> matriz_adj = grafoMatrizAdj.get_matriz_adj();

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
    imprimir_tabela_dijkstra(distancia, visitado, predecessor);

    return distancia;
}

/**
 * @brief Executa o algoritmo de Dijkstra para encontrar o menor caminho
 *        entre dois vértices específicos.
 *
 * Esta função para a execução assim que o vértice final é visitado,
 * tornando-a mais eficiente quando o objetivo é encontrar apenas um caminho mínimo.
 *
 * @param grafoMatrizAdj Grafo direcionado armazenado em matriz de adjacência.
 * @param vertice_inicial Vértice de origem (base 0).
 * @param vertice_final Vértice de destino (base 0).
 *
 * @return std::vector<int> Vetor de distâncias (a posição [vertice_final]
 *         contém a menor distância encontrada).
 *
 * @note Se a distância final for INF, significa que não existe caminho.
 */
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