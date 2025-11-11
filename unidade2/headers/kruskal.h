#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <map>
#include <set>
#include <stack>
#include <utility> 
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "arvore-minima.h"

bool encontra_ciclo(const Grafo& grafo);
ArvoreMinima gerar_arvore_minima(const Grafo& grafo);

// std::map<int, int> busca_em_profundidade_grafo(const Grafo& grafo, int vertice_inicial);
// std::pair<std::map<int, int>, std::vector<std::pair<int, int>>> busca_profundidade_lista_adj_recursiva(GrafoListaAdj grafo, int vertice);
// void busca_profundidade_lista_adj_recursiva_util(int u,
//                                                 std::vector<bool>& visitados,
//                                                 std::map<int, int>& predecessores,
//                                                 std::map<int, std::list<int>>& lista_adj,
//                                                 std::vector<std::pair<int, int>>& arestas_retorno,
//                                                 const std::vector<std::string>& rotulos);
// void exportar_arvore_profundidade_para_dot(const std::string& filename,
//                                             std::map<int, int> arvore, 
//                                             const std::vector<std::pair<int, int>>& arestas_retorno,
//                                             const std::vector<std::string>& rotulos);
// void busca_articulacoes_dfs_recursiva(
//     const Grafo& grafo,int u, std::vector<int>& disc, std::vector<int>& low, 
//     std::vector<int>& parent, std::stack<std::pair<int, int>>& pilha,
//     std::set<int>& ap, std::vector<std::set<int>>& blocos, int& tempo);

#endif