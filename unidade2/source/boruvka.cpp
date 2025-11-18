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
const int INF = INT_MAX; 

/**
 * Essa função encontra o conjunto representativo (raiz) de um vértice 'u'
 * utilizando a técnica de compressão de caminho para otimizar futuras buscas.
 * Ela é usada no algoritmo de Boruvka para gerenciar componentes conectadas.
 * 
 */
int find_set(int u, std::vector<int>& parent) {
    if (parent[u] == u) {
        return u;
    }
    return find_set(parent[u], parent);
}

/**
 * Essa função une dois conjuntos representativos (raízes) 'u' e 'v'
 * utilizando a técnica de união por rank para manter a árvore balanceada.
 * Ela é usada no algoritmo de Boruvka para conectar componentes diferentes.
 * 
 */
void unite_sets(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
    int raiz_u = find_set(u, parent);
    int raiz_v = find_set(v, parent);

        if (rank[raiz_u] < rank[raiz_v]) {
            parent[raiz_u] = raiz_v;
        } else if (rank[raiz_u] > rank[raiz_v]) {
            parent[raiz_v] = raiz_u;
        } else {
            parent[raiz_v] = raiz_u;
            rank[raiz_u]++;
        }
}

/**
 * Realiza o algoritmo de Boruvka para encontrar a Árvore Geradora Mínima (AGM) de um grafo.
 * Ela retorna um novo grafo que representa a AGM.
 * Sua lógica baseia-se na união de componentes conectadas através das arestas de menor peso,
 * até que todas as componentes estejam conectadas em uma única árvore.
 * 
 */
GrafoMatrizAdj boruvka(const GrafoMatrizAdj& grafoMatrizAdj) {
    int qtd_vertices = grafoMatrizAdj.get_qtd_vertices();
    GrafoMatrizAdj agm_matriz_adj(qtd_vertices);
    agm_matriz_adj.set_rotulos(grafoMatrizAdj.get_rotulos());

    std::vector<std::vector<int>> cheapest(qtd_vertices, std::vector<int>(3, -1));
    std::vector<int> parent(qtd_vertices);
    std::vector<int> rank(qtd_vertices, 0);
    for (int v = 0; v < qtd_vertices; v++) {
        parent[v] = v;
        rank[v] = 0;
    }
    int num_components = qtd_vertices;
    int custo_total = 0;
    bool aresta_encontrada = false;

    std::cout << "Árvore Geradora Mínima do Grafo:" << std::endl;
    std::cout << "Arestas escolhidas:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "(v1, v2)  | peso " << std::endl;
    while (num_components > 1) {
        for(int i = 0; i < qtd_vertices; i++) {
            cheapest[i] = {-1, -1, INF}; 
        }
        for (int u = 0; u < qtd_vertices; u++) {
            for (int v = u + 1; v < qtd_vertices; v++) { 
                int w = grafoMatrizAdj.get_matriz_adj()[u][v];
                if (w == INF) {
                    continue; 
                }
                int set1 = find_set(u, parent);
                int set2 = find_set(v, parent);

                if (set1 != set2) {
                    aresta_encontrada = true;
                    if (w < cheapest[set1][2]) {
                        cheapest[set1] = {u, v, w};
                    }
                    if (w < cheapest[set2][2]) {
                        cheapest[set2] = {u, v, w};
                    }
                }
            }
        }
        
        for (int i = 0; i < qtd_vertices; i++) {
            if (cheapest[i][2] != -1) {
                int u = cheapest[i][0];
                int v = cheapest[i][1];
                int w = cheapest[i][2];
                if (u < 0 || v < 0) continue;
                int set1 = find_set(u, parent);
                int set2 = find_set(v, parent);

                if (set1 != set2) {
                    agm_matriz_adj.inserir_aresta(u, v, w);
                    unite_sets(set1, set2, parent, rank);
                    custo_total += w;
                    num_components--;
                    std::cout << " ";
                    if(u < 10){ 
                        std:: cout << " ";
                    }
                    std::cout << u  << ", " ;
                    if(v < 10){ 
                        std:: cout << " ";
                    }
                    std::cout << v << "   |  ";
                    if(w < 10){ 
                        std:: cout << " ";
                    }
                    std:: cout << w << std::endl;
                }
            }
        }
        for(int i = 0; i < qtd_vertices; i++) {
            cheapest[i][2] = -1;
        }
    }
    std::cout << "------------------" << std::endl;
    printf("Custo total da AGM (Boruvka): %d\n", custo_total);
    return agm_matriz_adj;
}
