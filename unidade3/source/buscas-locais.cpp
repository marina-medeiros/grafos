#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>
#include "../../final/headers/DigrafoMatrizAdj.h"

/**
 * @brief Calcula o custo total de uma solução (ordem de vértices).
 * 
 * A soma é feita considerando o peso das arestas entre vértices consecutivos na ordem.
 *
 * @param ordem_vertices Vetor representando a ordem visitada dos vértices.
 * @param grafo Grafo direcionado contendo a matriz de adjacência.
 * @return double Custo total da ordem.
 */
int calcula_custo(std::vector<int> ordem_vertices, const DigrafoMatrizAdj &grafo){
    int custo = 0;
    std::vector<std::vector<int>> pesos = grafo.get_matriz_adj();
    int num_vertices = ordem_vertices.size();

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
 * @brief Executa a operação SWAP entre dois vértices da solução.
 *
 * Troca os elementos de posição e recalcula o custo da nova ordem.
 *
 * @param solucao Par contendo vetor de vértices e seu custo.
 * @param vertice Índice do primeiro vértice.
 * @param swap_pos Índice do segundo vértice.
 * @param grafo Grafo para cálculo do custo.
 * @return std::pair<std::vector<int>, int> Nova solução após o swap.
 */
std::pair<std::vector<int>, int> swap(std::pair<std::vector<int>, int> solucao, int vertice, int swap_pos, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    std::swap(nova_solucao.first[swap_pos], nova_solucao.first[vertice]);
    nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

    return nova_solucao;
}

/**
 * @brief Gera todos os vizinhos da solução a partir da heurística SWAP.
 *
 * @param solucao Solução inicial.
 * @param grafo Grafo para recálculo dos custos.
 * @return std::vector<std::pair<std::vector<int>, int>> Lista de soluções vizinhas.
 */
std::vector<std::pair<std::vector<int>, int>> vizinhanca_swap(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices(); jj++){
            if(ii == jj){
                continue;
            }
            vizinhanca.push_back(swap(solucao, ii, jj, grafo));
        }
    }

    return vizinhanca;
}

/**
 * @brief Executa a operação SHIFT movendo um vértice para outra posição.
 *
 * Remove o vértice da posição original e o insere em uma nova posição.
 *
 * @param solucao Solução inicial.
 * @param vertice Posição atual do vértice.
 * @param shift_pos Nova posição alvo.
 * @param grafo Grafo para cálculo do custo.
 * @return std::pair<std::vector<int>, int> Nova solução após o shift.
 */
std::pair<std::vector<int>, int> shift(std::pair<std::vector<int>, int> solucao, int vertice, int shift_pos, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    auto& v = nova_solucao.first;

    if (vertice < 0 || vertice >= (int)v.size()) return solucao;

    int nova_pos = shift_pos;
    int elem = v[vertice];

    v.erase(v.begin() + vertice);

    v.insert(v.begin() + nova_pos, elem);

    nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

    return nova_solucao;
}
/**
 * @brief Gera toda a vizinhança da solução baseada na heurística SHIFT.
 *
 * @param solucao Solução base.
 * @param grafo Grafo contendo os custos.
 * @return std::vector<std::pair<std::vector<int>, int>> Lista de vizinhos.
 */
std::vector<std::pair<std::vector<int>, int>> vizinhanca_shift(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices(); jj++){
            if(ii == jj){
                continue;
            }
            vizinhanca.push_back(shift(solucao, ii, jj, grafo));
        }
    }

    return vizinhanca;
}

/**
 * @brief Executa a operação INVERT (2-opt parcial), invertendo um segmento aleatório.
 *
 * Seleciona aleatoriamente duas posições i e j, com i < j, e inverte o trecho entre elas.
 *
 * @param solucao Solução base.
 * @param grafo Grafo para cálculo de custo.
 * @return std::pair<std::vector<int>, int> Nova solução após o invert.
 */
std::pair<std::vector<int>, int> invert(std::pair<std::vector<int>, int> solucao, int i, int j, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    auto& v = nova_solucao.first;
    
    if (i < j) {
        std::reverse(v.begin() + i, v.begin() + j + 1);
    }

    nova_solucao.second = calcula_custo(v, grafo);

    return nova_solucao;
}

/**
 * @brief Gera uma vizinhança aleatória baseada em múltiplas execuções da heurística INVERT.
 *
 * @param solucao Solução inicial.
 * @param grafo Grafo para cálculo dos custos.
 * @return std::vector<std::pair<std::vector<int>, int>> Vizinhança gerada.
 */
std::vector<std::pair<std::vector<int>, int>> vizinhanca_invert(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < solucao.first.size() - 1; ii++){
        for(int jj = ii + 1; jj < solucao.first.size(); jj++){
            vizinhanca.push_back(invert(solucao, ii, jj, grafo));
        }
    }

    return vizinhanca;
}

/**
 * @brief Imprime uma solução no formato: ordem dos vértices + custo.
 *
 * @param sol Par contendo vetor de vértices e custo total.
 */
void imprimir_solucao(const std::pair<std::vector<int>, int> &sol, std::vector<std::string> &rotulos) {
    std::cout << "Ordem: ";
    for (auto v : sol.first) std::cout << rotulos.at(v) << " ";
    std::cout << rotulos.at(sol.first[0]);
    std::cout << " | Custo = " << sol.second << std::endl;
}

/**
 * @brief Executa a busca local baseada em SWAP, SHIFT ou INVERT.
 *
 * Implementa as estratégias First Improvement e Best Improvement.
 *
 * @param solucao Solução inicial.
 * @param tipo_busca 1 = First Improvement, 2 = Best Improvement.
 * @param heuristica 1 = SWAP, 2 = SHIFT, 3 = INVERT.
 * @param grafo Grafo utilizado para calcular custos.
 * @return std::pair<std::vector<int>, int> Melhor solução encontrada.
 */
std::pair<std::vector<int>, int> busca_local(std::pair<std::vector<int>, int> solucao, int tipo_busca, int heuristica, const DigrafoMatrizAdj &grafo){
    bool melhoria = true;
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;

    if (solucao.first.size() > grafo.get_qtd_vertices()) {
        solucao.first.pop_back();
    }

    switch (heuristica){
        case 1: vizinhanca = vizinhanca_swap(solucao, grafo); break;
        case 2: vizinhanca = vizinhanca_shift(solucao, grafo); break;
        case 3: vizinhanca = vizinhanca_invert(solucao, grafo); break;
        default: break;
    }

    while(melhoria){
        melhoria = false;
        if(tipo_busca == 1){ //first_imp
            for(auto sol : vizinhanca){
                if(sol.second < solucao.second){
                    solucao = sol;
                    melhoria = true;
                    break; 
                }
            }    
        }
        else if(tipo_busca == 2){ //best_imp
            std::pair<std::vector<int>, int> melhor_sol = solucao;
            for(auto sol : vizinhanca){
                if(sol.second < melhor_sol.second){
                    melhor_sol = sol;
                }
            }
            if(melhor_sol.second < solucao.second){
                solucao = melhor_sol;
                melhoria = true;
            }
        }
    }

    return solucao;
}

/**
 * @brief Imprime os resultados da busca local para todas as heurísticas e estratégias.
 *
 * @param solucao Solução inicial.
 * @param grafo Grafo utilizado nos cálculos.
 */
void imprimir_busca_local(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    auto rotulos = grafo.get_rotulos();

    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "Solucoes encontradas a partir da busca local: " << std::endl;
    std::cout << "------------ Metodo 'first improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 1, grafo), rotulos);
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 2, grafo), rotulos);
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 3, grafo), rotulos);
    std::cout << "------------ Metodo 'best improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 1, grafo), rotulos);
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 2, grafo), rotulos);
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 3, grafo), rotulos);
    std::cout << "----------------------------------------------------------" << std::endl << std::endl;
}