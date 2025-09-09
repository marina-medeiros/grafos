#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include <map>

#include "../../aula04/headers/grafo.h"

std::map<int, int> busca_profundidade_matriz_adj_iterativa(Grafo grafo, int vertice);
std::map<int, int> busca_profundidade_lista_adj_recursiva(Grafo grafo, int vertice);
void busca_profundidade_lista_adj_recursiva_util(int vertice, std::vector<bool> &visitados, std::map<int, int> &predecessores, std::map<int, std::list<int>> &lista_adj);
void exportar_arvore_profundidade_para_dot(const std::string &filename, std::map<int, int> arvore);

#endif