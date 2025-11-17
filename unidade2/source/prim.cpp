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

GrafoMatrizAdj prim(const GrafoMatrizAdj& grafoMatrizAdj){
    int qnt_vertices = grafoMatrizAdj.get_qtd_vertices();
    ArvoreMinima agm(qnt_vertices);
    GrafoMatrizAdj agm_matriz_adj(qnt_vertices);
    agm_matriz_adj.set_rotulos(grafoMatrizAdj.get_rotulos());

    std::vector<bool> in_agm(qnt_vertices, false);
    std::vector<int> key(qnt_vertices, INT_MAX);
    std::vector<int> parent(qnt_vertices, -1);
    //std::vector<int> vertices(qnt_vertices);
   
    for(int i = 0; i < qnt_vertices; i++){
        key[i] = INT_MAX;
        //vertices[i] = i;
    }
    key[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < qnt_vertices; count++){
        int u = findMin(key, in_agm);
        if (u == -1) {
            std::cerr << "Aviso (Prim): Grafo desconexo. Interrompendo.\n";
            break;
        }
        in_agm[u] = true;
        //vertices.erase(std::remove(vertices.begin(), vertices.end(), u), vertices.end());
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
    int custo_total = 0;
    std::cout << "Edge \tWeight\n";
    for (int i = 1; i < qnt_vertices; i++) {
        if (parent[i] != -1) {
            int peso = grafoMatrizAdj.get_matriz_adj()[i][parent[i]];
            std::cout << parent[i] << " - " << i << "\t" << peso << " \n";
            custo_total += peso;
            agm_matriz_adj.inserir_aresta(parent[i], i, peso);
        }
    }
    agm_matriz_adj.print();
    printf("Custo total da AGM (Prim): %d\n", custo_total);
    return agm_matriz_adj;
}