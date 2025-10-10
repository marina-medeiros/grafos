#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include <map>
#include <set>
#include <stack>
#include <utility> 
#include "Grafo.h"
#include "GrafoListaAdj.h"

std::map<int, int> busca_em_profundidade_grafo(const Grafo& grafo, int vertice_inicial);
std::pair<std::map<int, int>, std::vector<std::pair<int, int>>> busca_profundidade_lista_adj_recursiva(GrafoListaAdj grafo, int vertice);
void busca_profundidade_lista_adj_recursiva_util(int u,
                                                std::vector<bool>& visitados,
                                                std::map<int, int>& predecessores,
                                                std::map<int, std::list<int>>& lista_adj,
                                                std::vector<std::pair<int, int>>& arestas_retorno);
void exportar_arvore_profundidade_para_dot(const std::string& filename,
                                            std::map<int, int> arvore, 
                                            const std::vector<std::pair<int, int>>& arestas_retorno);
void busca_articulacoes_dfs_recursiva(
    const Grafo& grafo,int u, std::vector<int>& disc, std::vector<int>& low, 
    std::vector<int>& parent, std::stack<std::pair<int, int>>& pilha,
    std::set<int>& ap, std::vector<std::set<int>>& blocos, int& tempo);

#endif