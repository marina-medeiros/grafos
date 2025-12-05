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
  std::vector<std::pair<std::vector<int>, int>> temp_populacao = populacao;


  auto comparar_por_custo = [](const std::pair<std::vector<int>, int>& a, const std::pair<std::vector<int>, int>& b) {
    return a.second < b.second;
  };

  std::partial_sort(temp_populacao.begin(), temp_populacao.begin() + num_selecionados, temp_populacao.end(), comparar_por_custo);

  std::vector<std::pair<std::vector<int>, int>> selecionados(temp_populacao.begin(), temp_populacao.begin() + num_selecionados);

  return selecionados;
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

void AlgoritmoGenetico::selecao_populacao(TipoSelecao tipo_selecao, int num_selecionados) {
  if (num_selecionados > int(populacao.size())) {
    std::cerr << "Erro: O número de soluções selecionadas não deve ser maior do que o tamanho da população" << std::endl;
    return;
  }

  switch (tipo_selecao) {
    case ALEATORIA:
      populacao = selecao_aleatoria(num_selecionados);
      break;
    case TORNEIO:
      populacao = selecao_torneio(num_selecionados);
      break;
    case ELITISMO:
      populacao = selecao_elitismo(num_selecionados);
      break;
    default:
        std::cerr << "Erro: Tipo de seleção inválido" << std::endl;
        return;
    }
}