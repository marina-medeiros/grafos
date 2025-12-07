#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../../final/headers/GrafoMatrizAdj.h"
#include "../headers/arvore-minima.h"
#include "../headers/prim.h"
#include <climits>

const int INF = INT_MAX;

/**
 * Essa função encontra o vértice com o valor mínimo na chave 'key'
 * que ainda não está incluído na Árvore Geradora Mínima (AGM).
 * Ela é usada no algoritmo de Prim para selecionar o próximo vértice a ser adicionado à AGM.
 */
int findMin(const std::vector<int>& key, const std::vector<bool>& in_agm){
    int min = INT_MAX;
    int min_index = -1;

    for(int i = 0; i < in_agm.size(); i++){
        if(in_agm[i] == false && key[i] < min){
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

/**
 * Realiza o algoritmo de Prim para encontrar a Árvore Geradora Mínima (AGM) de um grafo.
 * Ela retorna um novo grafo que representa a AGM.
 * Sua lógica baseia-se na adição iterativa do vértice com a aresta de menor peso
 * que conecta um vértice fora da AGM a um vértice dentro da AGM, até que todos os vértices estejam incluídos.
 * 
 */
GrafoMatrizAdj prim(const GrafoMatrizAdj& grafoMatrizAdj){
    int qnt_vertices = grafoMatrizAdj.get_qtd_vertices();
    GrafoMatrizAdj agm_matriz_adj(qnt_vertices);
    agm_matriz_adj.set_rotulos(grafoMatrizAdj.get_rotulos());

    std::vector<bool> in_agm(qnt_vertices, false);
    std::vector<int> key(qnt_vertices, INT_MAX);
    std::vector<int> parent(qnt_vertices, -1);
   
    for(int i = 0; i < qnt_vertices; i++){
        key[i] = INT_MAX;
    }
    key[0] = 0;
    parent[0] = -1;
    int custo_total = 0;
    
    for(int count = 0; count < qnt_vertices; count++){
        int u = findMin(key, in_agm);
        in_agm[u] = true;
        for(int v = 0; v < qnt_vertices; v++){
            int peso_aresta = grafoMatrizAdj.get_matriz_adj()[u][v];
            if(!in_agm[v] && peso_aresta != INF && peso_aresta < key[v]){
                if (u != v) {
                    parent[v] = u;
                    key[v] = peso_aresta;
                }
            }
        }
    }
    
    std::cout << "Árvore Geradora Mínima do Grafo:" << std::endl;
    std::cout << "Arestas escolhidas:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "(v1, v2)  | peso " << std::endl;
    for (int i = 1; i < qnt_vertices; i++) {
        if (parent[i] != -1) {
            int peso = grafoMatrizAdj.get_matriz_adj()[i][parent[i]];
            agm_matriz_adj.inserir_aresta(parent[i], i, peso);
            custo_total += peso;
            std::cout << " ";
            if(parent[i] < 10){ 
                std:: cout << " ";
            }
            std::cout << parent[i]  << ", " ;
            if(i < 10){ 
                std:: cout << " ";
            }
            std::cout << i << "   |  ";
            if(peso < 10){ 
                std:: cout << " ";
            }
            std:: cout << peso << std::endl;
        }
    }
    std::cout << "------------------" << std::endl;
    
    printf("Custo total da AGM (Prim): %d\n", custo_total);
    return agm_matriz_adj;
}