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

void imprimirMatrizDistancias(const std::vector<std::vector<int>>& dist, const std::vector<std::string>& rotulos_digrafo) {
    int N = dist.size();
    if (N == 0) return;

    std::cout << "------- Matriz de distâncias -------" << std::endl;
    // Imprime o cabeçalho das colunas
    std::cout << std::setw(5) << " ";
    for (int j = 0; j < N; ++j) {
        std::string label = rotulos_digrafo[j].empty() ? std::to_string(j + 1) : rotulos_digrafo[j];
        std::cout << std::setw(5) << label;
    }
    std::cout << "\n" << std::setw(5) << "----";
    for (int j = 0; j < N; ++j) {
        std::cout << std::setw(5) << "----";
    }
    std::cout << std::endl;


    // Imprime as linhas
    for (int i = 0; i < N; ++i) {
        std::string linha_label = rotulos_digrafo[i].empty() ? std::to_string(i + 1) : rotulos_digrafo[i];
        std::cout << std::setw(3) << linha_label << " | ";
        
        for (int j = 0; j < N; ++j) {
            if (dist[i][j] == INF) {
                std::cout << std::setw(5) << "INF";
            } else {
                std::cout << std::setw(5) << dist[i][j];
            }
        }
        std::cout << std::endl;
    }
}

/**
 * Imprime uma matriz de predecessores formatada.
 */
void imprimirMatrizPredecessores(const std::vector<std::vector<int>>& pred, const std::vector<std::string>& rotulos_digrafo) {
    int N = pred.size();
    if (N == 0) return;

    std::cout << "------- Matriz de predecessores -------" << std::endl;

    // Imprime o cabeçalho das colunas
    std::cout << std::setw(5) << " ";
    for (int j = 0; j < N; ++j) {
        std::string label = rotulos_digrafo[j].empty() ? std::to_string(j + 1) : rotulos_digrafo[j];
        std::cout << std::setw(5) << label;
    }
    std::cout << "\n" << std::setw(5) << "----";
    for (int j = 0; j < N; ++j) {
        std::cout << std::setw(5) << "----";
    }
    std::cout << std::endl;

    // Imprime as linhas
    for (int i = 0; i < N; ++i) {
        std::string linha_label = rotulos_digrafo[i].empty() ? std::to_string(i + 1) : rotulos_digrafo[i];
        std::cout << std::setw(3) << linha_label << " | ";
        
        for (int j = 0; j < N; ++j) {
            if (pred[i][j] == -1) {
                std::cout << std::setw(5) << "NIL";
            } else {
                std::string val_pred = rotulos_digrafo[pred[i][j]].empty() ? std::to_string(pred[i][j]) : rotulos_digrafo[pred[i][j]];
                std::cout << std::setw(5) << val_pred;
            }
        }
        std::cout << std::endl;
    }
}

DigrafoMatrizAdj gerarArvoreCaminhos(int origem, const ResultadoFloydWarshall& resultado, const DigrafoMatrizAdj& grafoOriginal) {
  int V = grafoOriginal.get_qtd_vertices();
  DigrafoMatrizAdj arvoreCaminhos(V);
  arvoreCaminhos.set_rotulos(grafoOriginal.get_rotulos());

  for (int j = 0; j < V; j++) {
    if (j == origem) {
      continue;
    }

    int p = resultado.pred[origem][j];

    if (p != -1) {
      int pesoAresta = resultado.dist[p][j];
      arvoreCaminhos.inserir_aresta(p, j, pesoAresta);
    }
  }

  return arvoreCaminhos;
}