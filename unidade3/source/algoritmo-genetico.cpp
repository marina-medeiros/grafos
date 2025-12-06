#include "../../final/headers/DigrafoMatrizAdj.h"
#include "../headers/algoritmo-genetico.h"
#include <algorithm>

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

std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecao_elitismo(int num_selecionados) {
  std::vector<std::pair<std::vector<int>, int>> populacao_temp = populacao;

  auto comparar_por_custo = [](const std::pair<std::vector<int>, int>& a, const std::pair<std::vector<int>, int>& b) {
    return a.second < b.second;
  };

  std::partial_sort(populacao_temp.begin(), populacao_temp.begin() + num_selecionados, populacao_temp.end(), comparar_por_custo);

  std::vector<std::pair<std::vector<int>, int>> selecionados(populacao_temp.begin(), populacao_temp.begin() + num_selecionados);

  return selecionados;
}

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

std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::selecionar_populacao(TipoSelecao tipo_selecao, int num_selecionados) {
  if (num_selecionados > int(populacao.size())) {
    std::cerr << "Erro: O número de soluções selecionadas não deve ser maior do que o tamanho da população" << std::endl;
    return;
  }

  switch (tipo_selecao) {
    case TORNEIO:
      return selecao_torneio(num_selecionados);
    case ELITISMO:
      return selecao_elitismo(num_selecionados);
    case ALEATORIA:
      return selecao_aleatoria(num_selecionados);
    default:
        std::cerr << "Erro: Tipo de seleção inválido" << std::endl;
        return {};
    }
}

std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::realizar_cruzamento(
  std::vector<std::pair<std::vector<int>, int>>& pais,
  TipoCruzamento tipo_cruzamento,
  double taxa_reproducao
) {
  int num_pais = pais.size();
  std::vector<std::pair<std::vector<int>, int>> filhos;
  filhos.reserve(num_pais);

  std::uniform_int_distribution<> distribuicao_probabilistica(0.0, 1.0);

  for (int i = 0; i < num_pais; i += 2) {
    const auto& pai1 = pais[i];
    const auto& pai2 = pais[i + 1];

    if (distribuicao_probabilistica(gerador_aleatorio) < taxa_reproducao) {
      std::pair<std::vector<int>, int> filho1, filho2;

      switch (tipo_cruzamento) {
        case UM_X:
          filho1 = cruzamento_1x_reparado(pai1, pai2);
          filho2 = cruzamento_1x_reparado(pai2, pai1);
          break;
        case OX:
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

std::vector<std::pair<std::vector<int>, int>> AlgoritmoGenetico::aplicar_mutacao(
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

void AlgoritmoGenetico::renovar_populacao(std::vector<std::pair<std::vector<int>, int>>& filhos, TipoRenovacao tipo_renovacao) {
  int tamanho_original_populacao = populacao.size();

  auto v = populacao;
  v.insert(v.end(), filhos.begin(), filhos.end());

  switch (tipo_renovacao) {
    case TORNEIO:
      populacao = selecao_torneio(tamanho_original_populacao);
    case ELITISMO:
      populacao =  selecao_elitismo(tamanho_original_populacao);
    default:
        std::cerr << "Erro: Tipo de renovação inválido" << std::endl;
        return;
    }
}