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
    std::vector<std::pair<std::vector<int>, int>> populacao_para_cruzamento;
    std::mt19937 gerador_aleatorio;

    int calcula_custo(std::vector<int> caminho);
    std::vector<std::pair<std::vector<int>, int>> selecao_aleatoria(int num_selecionados);
    std::vector<std::pair<std::vector<int>, int>> selecao_torneio(int num_selecionados);
    std::vector<std::pair<std::vector<int>, int>> selecao_elitismo(int num_selecionados);
    std::pair<std::vector<int>, int> cruzamento_1x_reparado(const std::pair<std::vector<int>, int>& pai1, const std::pair<std::vector<int>, int>& pai2);
    std::pair<std::vector<int>, int> cruzamento_ox(const std::pair<std::vector<int>, int>& pai1, const std::pair<std::vector<int>, int>& pai2);

  public:
    AlgoritmoGenetico(const DigrafoMatrizAdj& g) : grafo(g) {
      std::random_device rd;
      gerador_aleatorio = std::mt19937(rd());
    }

    // Etapas (1) Início e (2) Fitness
    void gerar_e_avaliar_populacao_inicial(int tamanho_populacao = 200);

    // Etapa (3.1) Seleção
    enum TipoSelecao { ALEATORIA = 1, TORNEIO = 2, ELITISMO = 3 };
    std::vector<std::pair<std::vector<int>, int>> selecionar_populacao(TipoSelecao tipo_selecao, int num_selecionados = 100);

    // Etapa (3.2) Cruzamento
    enum TipoCruzamento { UM_X = 1, OX = 2 };
    std::vector<std::pair<std::vector<int>, int>> realizar_cruzamento(std::vector<std::pair<std::vector<int>, int>>& selecionados, TipoCruzamento tipo_cruzamento, double taxa_reproducao);

    // Etapa (3.3) Mutação
    std::vector<std::pair<std::vector<int>, int>> aplicar_mutacao(std::vector<std::pair<std::vector<int>, int>>& filhos, double taxa_mutacao);

    const std::vector<std::pair<std::vector<int>, int>>& get_populacao() const {
      return populacao;
    }
};

#endif