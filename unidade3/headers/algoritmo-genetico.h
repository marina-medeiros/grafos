#ifndef ALGORITMO_GENETICO_H
#define ALGORITMO_GENETICO_H

#include "../../final/headers/DigrafoMatrizAdj.h"
#include "insercao-mais-barata.h"
#include "vizinho-mais-proximo.h"
#include <random>

class AlgoritmoGenetico {
  protected:
    const DigrafoMatrizAdj& grafo;
    std::vector<std::pair<std::vector<int>, int>> populacao;
    std::mt19937 gerador_aleatorio;

    int calcula_custo(std::vector<int> caminho);
    std::pair<std::vector<int>, int> obter_melhor_solucao();
    std::vector<std::pair<std::vector<int>, int>> selecao_torneio(int num_selecionados);
    std::vector<std::pair<std::vector<int>, int>> selecao_elitismo(int num_selecionados);
    std::vector<std::pair<std::vector<int>, int>> selecao_aleatoria(int num_selecionados);
    std::pair<std::vector<int>, int> cruzamento_1x_reparado(const std::pair<std::vector<int>, int>& pai1, const std::pair<std::vector<int>, int>& pai2);
    std::pair<std::vector<int>, int> cruzamento_ox(const std::pair<std::vector<int>, int>& pai1, const std::pair<std::vector<int>, int>& pai2);

  public:
    AlgoritmoGenetico(const DigrafoMatrizAdj& g) : grafo(g) {
      std::random_device rd;
      gerador_aleatorio = std::mt19937(rd());
    }

    // Etapas (1) Início e (2) Fitness
    void gerar_e_avaliar_populacao_inicial(int tamanho_populacao);

    // Etapa (3) Nova Geração
    // Etapa (3.1) Seleção
    enum class TipoSelecao { TORNEIO, ELITISMO, ALEATORIA };
    std::vector<std::pair<std::vector<int>, int>> selecionar_populacao(int num_selecionados, TipoSelecao tipo_selecao);

    // Etapa (3.2) Cruzamento
    enum class TipoCruzamento { UM_X, OX };
    std::vector<std::pair<std::vector<int>, int>> realizar_cruzamento(std::vector<std::pair<std::vector<int>, int>>& selecionados, double taxa_reproducao, TipoCruzamento tipo_cruzamento);

    // Etapa (3.3) Mutação
    void aplicar_mutacao(std::vector<std::pair<std::vector<int>, int>>& filhos, double taxa_mutacao);

    // Etapa (4) Renovar
    enum class TipoRenovacao { TORNEIO, ELITISMO };
    void renovar_populacao(std::vector<std::pair<std::vector<int>, int>>& filhos, TipoRenovacao tipo_renovacao);

    std::pair<std::vector<int>, int> executar_algoritmo(
      int tamanho_populacao, double taxa_reproducao, double taxa_mutacao, int num_geracoes,
      int num_selecionados_para_cruzamento, int max_geracoes_sem_melhoria,
      TipoSelecao tipo_selecao, TipoCruzamento tipo_cruzamento, TipoRenovacao tipo_renovacao
    );

    const std::vector<std::pair<std::vector<int>, int>>& get_populacao() const {
      return populacao;
    }
};

#endif