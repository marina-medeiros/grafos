#include <algorithm>
#include <limits>
#include <vector>
#include <iostream>
#include <random>
#include "../../final/headers/DigrafoMatrizAdj.h"

double calcula_custo(std::vector<int> ordem_vertices, const DigrafoMatrizAdj &grafo){
    double custo = 0;
    std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();
    for(int ii = 0; ii < int(ordem_vertices.size()) - 1; ii++){
        int v1 = ordem_vertices[ii];
        int v2 = ordem_vertices[ii+1];
        custo += matriz_adj[v1][v2];
    }
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
        for(int jj = 0; jj < grafo.get_qtd_vertices()-1; jj++){
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

    if (nova_pos > vertice){
        nova_pos--;
    }

    v.insert(v.begin() + nova_pos, elem);

    nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

    return nova_solucao;
}

std::vector<std::pair<std::vector<int>, int>> vizinhanca_shift(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices()-1; jj++){
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

std::pair<std::vector<int>, int> busca_local(std::pair<std::vector<int>, int> solucao, int tipo_busca, int heuristica, const DigrafoMatrizAdj &grafo){
    bool melhoria = true;
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;

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
