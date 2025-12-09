#include "../../final/headers/DigrafoMatrizAdj.h"
#include "../headers/algoritmo-genetico.h"
#include <algorithm>

/**
 * @brief Calcula o custo total de uma solução (ordem de vértices).
 * A soma é feita considerando o peso das arestas entre vértices consecutivos na ordem.
 * @param ordem_vertices Vetor representando a ordem visitada dos vértices.
 * @return double Custo total da ordem.
 * 
 */
int AlgoritmoGenetico::calcula_custo(std::vector<int> ordem_vertices) {
    int custo = 0;
    int num_vertices = ordem_vertices.size();
    auto pesos = grafo.get_matriz_adj();

    for (int ii = 0; ii < num_vertices - 1; ii++) {
        int v1 = ordem_vertices[ii];
        int v2 = ordem_vertices[ii + 1];
        custo += pesos[v1][v2];
    }

    int ultimo = ordem_vertices[num_vertices - 1];
    int primeiro = ordem_vertices[0];
    custo += pesos[ultimo][primeiro];

    return custo;
}

/**
 * @brief Obtém a melhor solução da população atual.
 * @return std::pair<std::vector<int>, int> Melhor solução (ordem de vértices e custo).
 */
std::pair<std::vector<int>, int> AlgoritmoGenetico::obter_melhor_solucao() {
  if (populacao.empty()) return {};

  auto comparar_por_custo = [](const std::pair<std::vector<int>, int>& a, const std::pair<std::vector<int>, int>& b) {
    return a.second < b.second;
  };

  auto melhor_elemento = std::min_element(populacao.begin(), populacao.end(), comparar_por_custo);

  return *melhor_elemento;
}

/**
 * @brief Realiza a seleção por torneio.
 * Seleciona pares de soluções aleatoriamente e escolhe a melhor entre elas.
 * @param num_selecionados Número de soluções a serem selecionadas.
 * @return std::vector<std::pair<std::vector<int>, int>> Soluções selecionadas.
 */
std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecao_torneio(int num_selecionados) {
  std::vector<std::pair<std::vector<int>, int>> selecionados;
  selecionados.reserve(num_selecionados);

  std::vector<int> indices(populacao.size());
  for (int i = 0; i < int(populacao.size()); i++) {
    indices[i] = i;
  }
  std::shuffle(indices.begin(), indices.end(), gerador_aleatorio);

  for (int i = 1; i < num_selecionados; i++) {
    int indice_competidor1 = indices[i-1];
    int custo_competidor1 = populacao[indice_competidor1].second;

    int indice_competidor2 = indices[i];
    int custo_competidor2 = populacao[indice_competidor2].second;

    if (custo_competidor1 <= custo_competidor2) {
      selecionados.push_back(populacao[indice_competidor1]);
    } else {
      selecionados.push_back(populacao[indice_competidor2]);
    }
  }

  return selecionados;
}

/**
 * @brief Realiza a seleção por elitismo.
 * Ordena a população pelo custo e seleciona as melhores soluções.
 * @param num_selecionados Número de soluções a serem selecionadas.
 * @return std::vector<std::pair<std::vector<int>, int>> Soluções selecionadas.
 */
std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecao_elitismo(int num_selecionados) {
  std::vector<std::pair<std::vector<int>, int>> populacao_temp = populacao;

  auto comparar_por_custo = [](const std::pair<std::vector<int>, int>& a, const std::pair<std::vector<int>, int>& b) {
    return a.second < b.second;
  };

  std::partial_sort(populacao_temp.begin(), populacao_temp.begin() + num_selecionados, populacao_temp.end(), comparar_por_custo);

  std::vector<std::pair<std::vector<int>, int>> selecionados(populacao_temp.begin(), populacao_temp.begin() + num_selecionados);

  return selecionados;
}

/**
 * @brief Realiza a seleção aleatória de soluções.
 * @param num_selecionados Número de soluções a serem selecionadas.
 * @return std::vector<std::pair<std::vector<int>, int>> Soluções selecionadas.
 */
std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecao_aleatoria(int num_selecionados) {
  std::vector<std::pair<std::vector<int>, int>> selecionados;
  selecionados.reserve(num_selecionados);

  std::vector<int> indices(populacao.size());
  for (int i = 0; i < int(populacao.size()); i++) {
    indices[i] = i;
  }
  std::shuffle(indices.begin(), indices.end(), gerador_aleatorio);

  for (int i = 0; i < num_selecionados; i++) {
    selecionados.push_back(populacao[indices[i]]);
  }

  return selecionados;
}

/**
 * @brief Realiza o cruzamento 1-point com reparo.
 * Seleciona um ponto de corte e combina os genes dos pais, reparando duplicatas
 * para garantir que todos os vértices estejam presentes na solução filha.
 * @param pai1 Primeira solução pai.
 * @param pai2 Segunda solução pai.
 * @return std::pair<std::vector<int>, int> Solução filha resultante do cruzamento.
 */
std::pair<std::vector<int>, int> AlgoritmoGenetico::cruzamento_1x_reparado(
  const std::pair<std::vector<int>, int>& pai1,
  const std::pair<std::vector<int>, int>& pai2
) {
  int num_vertices = pai1.first.size();
  std::vector<int> filho = pai1.first;

  std::uniform_int_distribution<> distribuicao(1, num_vertices - 2);
  int ponto_corte = distribuicao(gerador_aleatorio);

  for (int i = ponto_corte; i < num_vertices; i++) {
    filho[i] = pai2.first[i];
  }

  std::vector<int> contagem(num_vertices, 0);
  std::vector<int> vertices_que_faltam;
  std::vector<int> pos_duplicadas;

  for (int i = 0; i < num_vertices; i++) {
    contagem[filho[i]]++;
  }

  for (int vertice = 0; vertice < num_vertices; vertice++) {
    if (contagem[vertice] == 0) vertices_que_faltam.push_back(vertice);
  }

  for (int i = 0; i < num_vertices; i++) {
    int c = filho[i];
    if (contagem[c] > 1) {
      contagem[c]--;
      pos_duplicadas.push_back(i);
    }
  }

  std::shuffle(pos_duplicadas.begin(), pos_duplicadas.end(), gerador_aleatorio);
  for (int i = 0; i < int(pos_duplicadas.size()); i++) {
    filho[pos_duplicadas[i]] = vertices_que_faltam[i];
  }

  return {filho, calcula_custo(filho)};
}

/**
 * @brief Realiza o cruzamento Order Crossover (OX).
 * Seleciona dois pontos de corte e preserva a ordem dos vértices dos pais.
 * @param pai1 Primeira solução pai.
 * @param pai2 Segunda solução pai.
 * @return std::pair<std::vector<int>, int> Solução filha resultante do cruzamento.
 */
std::pair<std::vector<int>, int> AlgoritmoGenetico::cruzamento_ox(
  const std::pair<std::vector<int>, int>& pai1,
  const std::pair<std::vector<int>, int>& pai2
) {
  int num_vertices = pai1.first.size();
  std::vector<int> filho(num_vertices, -1);

  std::uniform_int_distribution<> distribuicao(1, num_vertices - 2);
  int ponto_corte1 = distribuicao(gerador_aleatorio);
  int ponto_corte2 = distribuicao(gerador_aleatorio);

  if (ponto_corte1 > ponto_corte2) std::swap(ponto_corte1, ponto_corte2);

  std::vector<bool> visitados(num_vertices, false);
  for (int i = ponto_corte1; i <= ponto_corte2; i++) {
    int vertice = pai1.first[i];
    filho[i] = vertice;
    visitados[vertice] = true;
  }

  int pos_filho = (ponto_corte2 + 1) % num_vertices;
  int pos_pai2 = (ponto_corte2 + 1) % num_vertices;

  for (int i = 0; i < num_vertices; i++) {
    int vertice = pai2.first[pos_pai2];
    if (!visitados[vertice]) {
      filho[pos_filho] = vertice;
      pos_filho = (pos_filho + 1) % num_vertices;
    }
    pos_pai2 = (pos_pai2 + 1) % num_vertices;
  }

  return {filho, calcula_custo(filho)};
}

/**
 * @brief Gera e avalia a população inicial do algoritmo genético.
 * Inclui soluções geradas pelas heurísticas Vizinho Mais Próximo e Inserção Mais Barata, além de soluções aleatórias.
 * @param tamanho_populacao Tamanho desejado da população inicial.
 */
void AlgoritmoGenetico::gerar_e_avaliar_populacao_inicial(int tamanho_populacao) {
  if (tamanho_populacao < 2) {
    std::cerr << "Erro: O tamanho mínimo da população é 2" << std::endl;
    return;
  }

  populacao.clear();
  populacao.reserve(tamanho_populacao);

  int qtd_vertices = grafo.get_qtd_vertices();

  auto solucao_vizinho = vizinho_mais_proximo(grafo, 0);
  solucao_vizinho.first.pop_back();

  auto solucao_insercao = insercao_mais_barata(grafo, 0);
  solucao_insercao.first.pop_back();

  if (tamanho_populacao > 2) {
    std::vector<int> vertices_base(qtd_vertices);
    for (int i = 0; i < qtd_vertices; i++) {
      vertices_base[i] = i;
    }

    while (int(populacao.size()) < tamanho_populacao) {
      std::shuffle(vertices_base.begin(), vertices_base.end(), gerador_aleatorio);
      int custo = calcula_custo(vertices_base);
      populacao.push_back({vertices_base, custo});
    }
  }
}

/**
 * @brief Seleciona uma subpopulação com base no tipo de seleção especificado.
 * @param num_selecionados Número de soluções a serem selecionadas.
 * @param tipo_selecao Tipo de seleção a ser utilizada (TORNEIO, ELITISMO, ALEATORIA).
 * @return std::vector<std::pair<std::vector<int>, int>> Soluções selecionadas.
 */
std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecionar_populacao(int num_selecionados, TipoSelecao tipo_selecao) {
  if (num_selecionados > int(populacao.size())) {
    std::cerr << "Erro: O número de soluções selecionadas não deve ser maior do que o tamanho da população" << std::endl;
    return {};
  }

  switch (tipo_selecao) {
    case TipoSelecao::TORNEIO:
      return selecao_torneio(num_selecionados);
    case TipoSelecao::ELITISMO:
      return selecao_elitismo(num_selecionados);
    case TipoSelecao::ALEATORIA:
      return selecao_aleatoria(num_selecionados);
    default:
        std::cerr << "Erro: Tipo de seleção inválido" << std::endl;
        return {};
    }
}

/**
 * @brief Realiza o cruzamento entre pares de soluções selecionadas.
 * @param pais Vetor de soluções selecionadas para cruzamento.
 * @param taxa_reproducao Probabilidade de cruzamento entre cada par de soluções.
 * @param tipo_cruzamento Tipo de cruzamento a ser utilizado (UM_X, OX).
 * @return std::vector<std::pair<std::vector<int>, int>> Soluções filhas resultantes do cruzamento.
 */
std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::realizar_cruzamento(
  std::vector<std::pair<std::vector<int>, int>>& pais,
  double taxa_reproducao,
  TipoCruzamento tipo_cruzamento
) {
  int num_pais = pais.size();
  std::vector<std::pair<std::vector<int>, int>> filhos;
  filhos.reserve(num_pais);

  std::uniform_real_distribution<double> distribuicao_probabilistica(0.0, 1.0);

  for (int i = 0; i < num_pais; i += 2) {
    if (i + 1 >= num_pais) {
      filhos.push_back(pais[i]);
      break;
    }

    const auto& pai1 = pais[i];
    const auto& pai2 = pais[i + 1];

    if (distribuicao_probabilistica(gerador_aleatorio) < taxa_reproducao) {
      std::pair<std::vector<int>, int> filho1, filho2;

      switch (tipo_cruzamento) {
        case TipoCruzamento::UM_X:
          filho1 = cruzamento_1x_reparado(pai1, pai2);
          filho2 = cruzamento_1x_reparado(pai2, pai1);
          break;
        case TipoCruzamento::OX:
          filho1 = cruzamento_ox(pai1, pai2);
          filho2 = cruzamento_ox(pai2, pai1);
          break;
        default:
          filho1 = pai1;
          filho2 = pai2;
          break;
      }

      filhos.push_back(filho1);
      filhos.push_back(filho2);
    }
  }

  return filhos;
}

/**
 * @brief Aplica mutação nas soluções filhas com base na taxa de mutação.
 * A mutação é realizada trocando dois vértices aleatoriamente na solução.
 * @param filhos Vetor de soluções filhas a serem mutadas.
 * @param taxa_mutacao Probabilidade de mutação para cada solução filha.
 */
void AlgoritmoGenetico::aplicar_mutacao(
  std::vector<std::pair<std::vector<int>, int>>& filhos,
  double taxa_mutacao
) {
  std::uniform_int_distribution<> distribuicao_probabilistica(0.0, 1.0);

  for (auto& filho: filhos) {
    if (distribuicao_probabilistica(gerador_aleatorio) < taxa_mutacao) {
      int num_vertices = filho.first.size();
      std::uniform_int_distribution<> distribuicao_posicao(0, num_vertices - 1);

      int pos1 = distribuicao_posicao(gerador_aleatorio);
      int pos2 = distribuicao_posicao(gerador_aleatorio);

      while (pos1 == pos2) {
        pos2 = distribuicao_posicao(gerador_aleatorio);
      }

      std::swap(filho.first[pos1], filho.first[pos2]);
      filho.second = calcula_custo(filho.first);
    }
  }
}

/**
 * @brief Renova a população combinando a população atual com os filhos gerados.
 * Seleciona as melhores soluções com base no tipo de renovação especificado.
 * @param filhos Vetor de soluções filhas geradas.
 * @param tipo_renovacao Tipo de renovação a ser utilizada (TORNEIO, ELITISMO).
 */
void AlgoritmoGenetico::renovar_populacao(std::vector<std::pair<std::vector<int>, int>>& filhos, TipoRenovacao tipo_renovacao) {
  int tamanho_original_populacao = populacao.size();

  populacao.insert(populacao.end(), filhos.begin(), filhos.end());

  switch (tipo_renovacao) {
    case TipoRenovacao::TORNEIO:
      populacao = selecao_torneio(tamanho_original_populacao);
      break;
    case TipoRenovacao::ELITISMO:
      populacao =  selecao_elitismo(tamanho_original_populacao);
      break;
    default:
        std::cerr << "Erro: Tipo de renovação inválido" << std::endl;
        return;
    }
}

/**
 * @brief Executa o algoritmo genético completo.
 * Inclui etapas de geração inicial, seleção, cruzamento, mutação e renovação.
 * @param tamanho_populacao Tamanho da população inicial.
 * @param taxa_reproducao Taxa de reprodução (cruzamento).
 * @param taxa_mutacao Taxa de mutação.
 * @param num_geracoes Número máximo de gerações a serem executadas.
 * @param num_selecionados_para_cruzamento Número de soluções selecionadas para cruzamento.
 * @param max_geracoes_sem_melhoria Número máximo de gerações sem melhoria antes de parar.
 * @param tipo_selecao Tipo de seleção a ser utilizada (TORNEIO, ELITISMO, ALEATORIA).
 * @param tipo_cruzamento Tipo de cruzamento a ser utilizado (UM_X, OX).
 * @param tipo_renovacao Tipo de renovação a ser utilizada (TORNEIO, ELITISMO).
 * @return std::pair<std::vector<int>, int> Melhor solução encontrada (ordem de vértices e custo).
 */
std::pair<std::vector<int>, int> AlgoritmoGenetico::executar_algoritmo(
  int tamanho_populacao, double taxa_reproducao, double taxa_mutacao, int num_geracoes,
  int num_selecionados_para_cruzamento, int max_geracoes_sem_melhoria,
  TipoSelecao tipo_selecao, TipoCruzamento tipo_cruzamento, TipoRenovacao tipo_renovacao
) {
  // Etapas (1) Início e (2) Fitness
  gerar_e_avaliar_populacao_inicial(tamanho_populacao);

  std::pair<std::vector<int>, int> melhor_solucao_global = obter_melhor_solucao();

  int geracao_atual = 0;
  int geracoes_sem_melhoria = 0;

  while (geracao_atual < num_geracoes && geracoes_sem_melhoria < max_geracoes_sem_melhoria) {
    geracao_atual++;

    // Etapa (3) Nova Geração
    auto pais = selecionar_populacao(num_selecionados_para_cruzamento, tipo_selecao);
    auto filhos = realizar_cruzamento(pais, taxa_reproducao, tipo_cruzamento);
    aplicar_mutacao(filhos, taxa_mutacao);

    // Etapa(4) Renovação
    renovar_populacao(filhos, tipo_renovacao);

    auto melhor_da_geracao = obter_melhor_solucao();

    if (melhor_da_geracao.second < melhor_solucao_global.second) {
      melhor_solucao_global = melhor_da_geracao;
      geracoes_sem_melhoria = 0;
    } else {
      geracoes_sem_melhoria++;
    }
  }

  return melhor_solucao_global;
}