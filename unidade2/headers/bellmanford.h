#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <vector>
#include "../../final/headers/Grafo.h"
#include "../../final/headers/DigrafoListaAdjPonderada.h"

extern const int INF;

bool bellman_ford(const DigrafoListaAdjPonderada& grafo, int s, std::vector<int>& distancia, std::vector<int>& predecessor);
void bellman_ford_geral(const DigrafoListaAdjPonderada& grafo, int s);
void bellman_ford_especifico(const DigrafoListaAdjPonderada& grafo, int s, int d);

#endif