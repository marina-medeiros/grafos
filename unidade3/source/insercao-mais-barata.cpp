#include <algorithm>
#include <limits>
#include "../../final/headers/DigrafoMatrizAdj.h"

/**
 * @brief Implementação da Heurística Construtiva da Inserção Mais Barata
 *
 * Inicia com um subciclo origem -> vizinho mais próximo -> origem. E iterativamente vai selecionando
 * o vértice não visitado de menor impacto no custo total. Avalia globalmente o custo de inserção.
 *
 * @param grafo Referência constante uma objeto DigrafoMatrizAdj
 * @param origem Índice do vértice inicial
 * @return std::pair<std::vector<int>, int> Um par contendo:
 * 1. Vetor de int contendo a rota construída
 * 2. Custo total final da rota
 */
std::pair<std::vector<int>, int> insercao_mais_barata(const DigrafoMatrizAdj &grafo, int origem){
    int qtd_vertices = grafo.get_qtd_vertices();
    auto matriz_adj = grafo.get_matriz_adj();

    const int INF = GrafoMatrizAdj::INF;
    std::vector<int> rota;
    std::vector<bool> visitado(qtd_vertices, false);

    int custo = 0;
    int vizinho = -1;
    int dist_min = INF;

    for (int i = 0; i < qtd_vertices; ++i) {
        if (i != origem && matriz_adj[origem][i] < dist_min){
            dist_min = matriz_adj[origem][i];
            vizinho = i;
        }
    }

    if (vizinho == -1){
        return {rota, 0};
    }

    rota.push_back(origem);
    rota.push_back(vizinho);
    rota.push_back(origem);

    visitado[origem] = true;
    visitado[vizinho] = true;

    custo = matriz_adj[origem][vizinho] + matriz_adj[vizinho][origem];
    int qtd_visitados = 2;

    while (qtd_visitados < qtd_vertices){
        int melhor_vertice = -1;
        int melhor_posicao = -1;
        int menor_aumento = INF;

        for (int j = 0; j < qtd_vertices; ++j){
            if (visitado[j]){
                continue;
            }

            for (size_t i = 0; i < rota.size() - 1; ++i) {
                int u = rota[i];
                int v = rota[i + 1];

                if (matriz_adj[u][j] != INF && matriz_adj[j][v] != INF && matriz_adj[u][v] != INF){
                    int aumento = matriz_adj[u][j] + matriz_adj[j][v] - matriz_adj[u][v];

                    if (aumento < menor_aumento)
                    {
                        menor_aumento = aumento;
                        melhor_vertice = j;
                        melhor_posicao = i;
                    }
                }
            }
        }

        if (melhor_vertice != -1){
            rota.insert(rota.begin() + melhor_posicao + 1, melhor_vertice);
            visitado[melhor_vertice] = true;
            custo += menor_aumento;
            qtd_visitados++;
        }
        else {
            break;
        }
    }
    return {rota, custo};
}