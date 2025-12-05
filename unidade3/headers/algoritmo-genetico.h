#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "../../final/headers/DigrafoMatrizAdj.h"
#include "insercao-mais-barata.h"
#include "vizinho-mais-proximo.h"
#include <random>

class AlgoritmoGenetico {
  private:
    const DigrafoMatrizAdj& grafo;
    std::vector<std::pair<std::vector<int>, int>> populacao;
    std::mt19937 gerador_aleatorio;

    int calcula_custo(std::vector<int> caminho);

  public:
    AlgoritmoGenetico(const DigrafoMatrizAdj& g) : grafo(g) {
      std::random_device rd;
      gerador_aleatorio = std::mt19937(rd());
    }
    void gerar_e_avaliar_populacao_inicial(int tamanho_populacao = 100);

    const std::vector<std::pair<std::vector<int>, int>>& get_populacao() const {
        return populacao;
    }
};

#endif