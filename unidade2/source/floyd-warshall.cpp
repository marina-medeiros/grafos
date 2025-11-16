#include "../headers/floyd-warshall.h"
#include <iomanip>

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

void imprimirMatrizDistancias(const std::vector<std::vector<int>>& dist) {
    int N = dist.size();
    if (N == 0) return;

    std::cout << "--- Matriz de Distancias ---" << std::endl;

    // Imprime o cabeçalho das colunas
    std::cout << std::setw(5) << " ";
    for (int j = 0; j < N; ++j) {
        std::cout << std::setw(5) << j;
    }
    std::cout << "\n" << std::setw(5) << "----";
    for (int j = 0; j < N; ++j) {
        std::cout << std::setw(5) << "----";
    }
    std::cout << std::endl;


    // Imprime as linhas
    for (int i = 0; i < N; ++i) {
        std::cout << std::setw(3) << i << " | ";
        
        for (int j = 0; j < N; ++j) {
            if (dist[i][j] == INF) {
                std::cout << std::setw(5) << "Inf";
            } else {
                std::cout << std::setw(5) << dist[i][j];
            }
        }
        std::cout << std::endl;
    }
}