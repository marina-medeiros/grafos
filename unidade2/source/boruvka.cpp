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
#include "../headers/boruvka.h"
#include <climits>

int find_set(int u, std::vector<int>& parent) {
    if (parent[u] == u) {
        return u;
    }
    return find_set(parent[u], parent);
}

void unite_sets(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
    int root_u = find_set(u, parent);
    int root_v = find_set(v, parent);

        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    
}

GrafoMatrizAdj boruvka(const GrafoMatrizAdj& grafoMatrizAdj) {
    int qtd_vertices = grafoMatrizAdj.get_qtd_vertices();
    ArvoreMinima agm(qtd_vertices);
    GrafoMatrizAdj agm_matriz_adj(qtd_vertices);

    std::vector<std::vector<int>> cheapest(qtd_vertices, std::vector<int>(3, -1));
    std::vector<int> parent(qtd_vertices);
    std::vector<int> rank(qtd_vertices, 0);

    for (int v = 0; v < qtd_vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    int num_components = qtd_vertices;
    int agmWeight = 0;

    while (num_components > 1) {

        for (int i = 0; i < qtd_vertices; i++) {
            int u = grafoMatrizAdj.get_matriz_adj()[i][0];
            int v = grafoMatrizAdj.get_matriz_adj()[i][1];
            int w = grafoMatrizAdj.get_matriz_adj()[i][2];
            int set1 = find_set(u, parent);
            int set2 = find_set(v, parent);
            if (set1 != set2) {
                if (cheapest[set1][2] == -1 || cheapest[set1][2] > w) {
                    cheapest[set1] = {u,v,w};
                }
                if (cheapest[set2][2] == -1 || w < cheapest[set2][2]) {
                    cheapest[set2] = {u,v,w};
                }
            }   
            
        }

        for (int i = 0; i < qtd_vertices; i++) {
            if (cheapest[i][2] != -1) {
                int u = cheapest[i][0];
                int v = cheapest[i][1];
                int w = cheapest[i][2];
                int set1 = find_set(u, parent);
                int set2 = find_set(v, parent);

                if (set1 != set2) {
                    //agm.inserir_aresta(u, v, w);
                    //agm_matriz_adj.inserir_aresta(u, v, w);
                    agmWeight += w;
                    unite_sets(set1, set2, parent, rank);
                    printf("Aresta adicionada à AGM: (%d, %d) com peso %d\n", u, v, w);
                    num_components--;
                }
            }
        }
        for(int i = 0; i < qtd_vertices; i++) {
            cheapest[i][2] = -1;
        }
    }

    return agm_matriz_adj;
}
