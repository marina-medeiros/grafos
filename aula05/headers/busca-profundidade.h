#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include <map>

#include "../../aula04/headers/grafo.h"

std::map<int, int> busca_profundidade_matriz_adj_iterativa(Grafo grafo, int vertice);
void exportar_arvore_profundidade_para_dot(const std::string& filename, std::map<int, int> arvore);

#endif