#include "../headers/buscas-locais-testes.h"
#include "../headers/buscas-locais.h"
#include <iostream>

using namespace std;

void testes_buscas_locais(){
  DigrafoMatrizAdj grafo(0);
  grafo.carregar_de_arquivo_csv("../dados/testes.csv", true);

  std::vector<int> ordem = {0, 1, 2, 3, 4};
  double custo = calcula_custo(ordem, grafo);
  std::pair<std::vector<int>, int> solucao(ordem, custo);

  testar_swap(grafo, solucao);
  testar_shift(grafo, solucao);
  testar_invert(grafo, solucao);

  testar_vizinhanca_swap(grafo, solucao);
  testar_vizinhanca_shift(grafo, solucao);
  testar_vizinhanca_invert(grafo, solucao);
}

void imprimir_solucao_testes(const pair<vector<int>, int> &sol) {
    cout << "Ordem: ";
    for (auto v : sol.first) cout << v << " ";
    cout << " | Custo = " << sol.second << endl;
}

// -----------------------------------------------------------------------------
// Testes individuais
// -----------------------------------------------------------------------------

void testar_swap(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando SWAP ===\n";
    imprimir_solucao_testes(solucao);

    for (int i = 0; i < grafo.get_qtd_vertices(); i++) {
        for (int j = i; j < grafo.get_qtd_vertices(); j++) {
            auto r = swap(solucao, i, j, grafo);
            cout << "swap(" << i << ", " << j << "): ";
            imprimir_solucao_testes(r);
        }
    }
}

void testar_shift(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando SHIFT ===\n";
    imprimir_solucao_testes(solucao);

    for (int i = 0; i < grafo.get_qtd_vertices(); i++) {
        for (int j = 0; j < grafo.get_qtd_vertices(); j++) {
            if (i == j) continue;
            auto r = shift(solucao, i, j, grafo);
            cout << "shift(" << i << " -> " << j << "): ";
            imprimir_solucao_testes(r);
        }
    }
}

void testar_invert(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando INVERT ===\n";
    imprimir_solucao_testes(solucao);

    // Apenas 10 inversões aleatórias
    for (int k = 0; k < 10; k++) {
        auto r = invert(solucao, grafo);
        cout << "invert " << k+1 << ": ";
        imprimir_solucao_testes(r);
    }
}

// -----------------------------------------------------------------------------
// Testes de vizinhança
// -----------------------------------------------------------------------------

void testar_vizinhanca_swap(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando VIZINHANÇA SWAP ===\n";
    imprimir_solucao_testes(solucao);

    auto viz = vizinhanca_swap(solucao, grafo);

    int k = 0;
    for (auto &s : viz) {
        cout << "#" << k++ << ": ";
        imprimir_solucao_testes(s);
    }
}

void testar_vizinhanca_shift(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando VIZINHANÇA SHIFT ===\n";
    imprimir_solucao_testes(solucao);

    auto viz = vizinhanca_shift(solucao, grafo);

    int k = 0;
    for (auto &s : viz) {
        cout << "#" << k++ << ": ";
        imprimir_solucao_testes(s);
    }
}

void testar_vizinhanca_invert(const DigrafoMatrizAdj &grafo, pair<vector<int>, int> solucao) {
    cout << "\n=== Testando VIZINHANÇA INVERT ===\n";
    imprimir_solucao_testes(solucao);

    auto viz = vizinhanca_invert(solucao, grafo);

    int k = 0;
    for (auto &s : viz) {
        cout << "#" << k++ << ": ";
        imprimir_solucao_testes(s);
    }
}
