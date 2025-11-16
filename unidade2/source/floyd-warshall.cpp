#include "../headers/floyd-warshall.h"

const int INF = std::numeric_limits<int>::max() / 2;

ResultadoFloydWarshall floyd_warshall(const DigrafoMatrizAdj& grafo) {
  int V = grafo.get_qtd_vertices();
  std::vector<std::vector<int>> pesos = grafo.get_matriz_adj();

  std::vector<std::vector<int>> dist(V, std::vector<int>(V));
  std::vector<std::vector<int>> pred(V, std::vector<int>(V));

  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      dist[i][j] = pesos[i][j];
      pred[i][j] = -1;
      if (pesos[i][j] != INF) {
        pred[i][j] = i;
      }
    }
    dist[i][i] = 0;
    pred[i][i] = i;
  }

  for (int k = 0; k < V; k++) {
    for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          pred[i][j] = pred[k][j];
        }
      }
    }
  }

  return {dist, pred};
}