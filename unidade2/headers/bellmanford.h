#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include "../../final/headers/Grafo.h"
#include "../../final/headers/DigrafoMatrizAdj.h"

bool bellman_ford(const DigrafoMatrizAdj& grafo, int s, std::vector<int>& distancia, std::vector<int>& predecessor);
void bellman_ford_geral(const DigrafoMatrizAdj& grafo, int s);
void bellman_ford_especifico(const DigrafoMatrizAdj& grafo, int s, int d);

#endif