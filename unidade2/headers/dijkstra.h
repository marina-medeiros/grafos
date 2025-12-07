#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <utility> 
#include "Grafo.h"
#include "DigrafoMatrizAdj.h"

std::vector<int> dijkstra_geral(const DigrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial);
std::vector<int> dijkstra_especifico(const DigrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial, int vertice_final);

#endif