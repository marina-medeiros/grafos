#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>
#include <random>
#include "../../final/headers/DigrafoMatrizAdj.h"

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


std::pair<std::vector<int>, int> swap(std::pair<std::vector<int>, int> solucao, int vertice, int swap_pos, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    std::swap(nova_solucao.first[swap_pos], nova_solucao.first[vertice]);
    nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

    return nova_solucao;
}


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

std::pair<std::vector<int>, int> invert(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    auto& v = nova_solucao.first;

    int n = v.size();

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, n - 1);
    int i = 0;
    int j = 0;

    while(i == j || i > j){
        i = dist(gen);
        j = dist(gen);
        if (i > j) std::swap(i, j);
    }

    std::reverse(v.begin() + i, v.begin() + j + 1);
    nova_solucao.second = calcula_custo(v, grafo);

    return nova_solucao;
}

std::vector<std::pair<std::vector<int>, int>> vizinhanca_invert(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < grafo.get_qtd_vertices()/2; ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices()/2; jj++){
            vizinhanca.push_back(invert(solucao, grafo));
        }
    }

    return vizinhanca;
}

void imprimir_solucao(const std::pair<std::vector<int>, int> &sol, std::vector<std::string> &rotulos) {
    std::cout << "Ordem: ";
    for (auto v : sol.first) std::cout << rotulos.at(v) << " ";
    std::cout << rotulos.at(sol.first[0]);
    std::cout << " | Custo = " << sol.second << std::endl;
}


/**
 * Aplica uma Busca Local para tentar reduzir o custo da solução fornecida.
 * @param solucao Par contendo {vetor_caminho, custo_total}. 
 * @param tipo_busca Estratégia de aceitação: 1 = First Improvement, 2 = Best Improvement.
 * @param heuristica Movimento usado: 1 = Swap, 2 = Shift, 3 = Invert.
 * @param grafo O digrafo contendo a matriz de pesos.
 * @return std::pair<std::vector<int>, int> A solução otimizada (ou a original, se não houver melhoria).
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