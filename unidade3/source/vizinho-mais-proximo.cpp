#include <algorithm>
#include <limits>
#include "../../final/headers/DigrafoMatrizAdj.h"

/**
 * @brief Implementação da Heurística Vizinho Mais Próximo
 *
 * Inicia no vértice de origem e, a cada passo, seleciona o vértice não visitado
 * mais próximo ao vértice atual. Repete-se o processo até que todos os vértices
 * sejam visitados. Finaliza na origem.
 *
 * @param grafo Referência constante uma objeto DigrafoMatrizAdj
 * @param origem Índice do vértice inicial
 * @return std::pair<std::vector<int>, int> Um par contendo:
 * 1. Vetor contenddo a sequência de vértices visitados
 * 2. Custo total (soma de pesos)
 */
std::pair<std::vector<int>, int> vizinho_mais_proximo(const DigrafoMatrizAdj &grafo, int origem) {
    int qtd_vertices = grafo.get_qtd_vertices();
    auto matriz_adj = grafo.get_matriz_adj();
    const int INF = GrafoMatrizAdj::INF;
    std::vector<bool> visitado(qtd_vertices, false);

    std::vector<int> percurso;
    percurso.push_back(origem);

    int dist_total = 0;
    int vert_atual = origem;
    visitado[origem] = true;

    for (int i = 1; i < qtd_vertices; ++i){
        int dist_min = INF;
        int prox = -1;

        for (int j = 0; j < qtd_vertices; ++j){
            if (!visitado[j]){
                if (matriz_adj[vert_atual][j] < dist_min){
                    dist_min = matriz_adj[vert_atual][j];
                    prox = j;
                }
            }
        }

        percurso.push_back(prox);
        dist_total += dist_min;
        vert_atual = prox;
        visitado[prox] = true;
    }

    if (matriz_adj[vert_atual][origem] != INF) {
        dist_total += matriz_adj[vert_atual][origem];
    }

    percurso.push_back(origem);
    return {percurso, dist_total};
}