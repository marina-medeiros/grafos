#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include <map>
#include "Grafo.h"

std::map<int, int> busca_em_profundidade_grafo(const Grafo& grafo, int vertice_inicial);

#endif