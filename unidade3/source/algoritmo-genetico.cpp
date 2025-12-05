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

void AlgoritmoGenetico::gerar_e_avaliar_populacao_inicial(int tamanho_populacao) {
  if (tamanho_populacao < 2) {
    std::cerr << "O tamanho mínimo da população é 2." << std::endl;
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