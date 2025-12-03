#include <algorithm>
#include <limits>
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

std::vector<std::pair<std::vector<int>, int>> vizinhanca_swap(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::vector<std::pair<std::vector<int>, int>> vizinhanca;
    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices()-1; jj++){
            std::pair<std::vector<int>, int> nova_solucao = solucao;
            std::swap(nova_solucao.first[ii], nova_solucao.first[jj]);
            nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

            vizinhanca.push_back(nova_solucao);
        }
    }

    return vizinhanca;
}


// retorna uma solução
// couter < vector.len
std::pair<std::vector<int>, int> swap(std::pair<std::vector<int>, int> solucao, int vertice, int swap_pos, const DigrafoMatrizAdj &grafo){
    std::pair<std::vector<int>, int> nova_solucao = solucao;
    std::swap(nova_solucao.first[swap_pos], nova_solucao.first[vertice]);
    nova_solucao.second = calcula_custo(nova_solucao.first, grafo);

    return nova_solucao;
}

std::pair<std::vector<int>, int> busca_local(std::pair<std::vector<int>, int> solucao, int tipo_busca, const DigrafoMatrizAdj &grafo){
    bool melhoria = true;
    std::vector<std::pair<std::vector<int>, int>> solucoes_geradas;
    while(melhoria){
        melhoria = false;
        if(tipo_busca == 1){ //first_imp
            int vertice = 0; // vertice a ser trocado
            int swap_pos = 0; // posição de destino do vértice a ser trocado
            std::pair<std::vector<int>, int> nova_sol = swap(solucao, vertice, swap_pos, grafo);

            swap_pos++;
            if(swap_pos == grafo.get_qtd_vertices()-1){
                swap_pos == 0;
                vertice++;
            }

            solucoes_geradas.push_back(nova_sol);

            if(nova_sol.second < solucao.second){ // se o custo for menor
                solucao = nova_sol;
                melhoria = true;
                break; // rever!
            }
                
        }
        else if(tipo_busca == 2){ //best_imp
            std::pair<std::vector<int>, int> melhor_sol = solucao;

        }
    }
}
