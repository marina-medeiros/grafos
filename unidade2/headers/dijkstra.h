#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <map>
#include <set>
#include <stack>
#include <vector>
#include <utility> 
#include "Grafo.h"
#include "GrafoListaAdj.h"

std::vector<int> dijkstra_geral(const GrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial);
std::vector<int> dijkstra_especifico(const GrafoMatrizAdj& grafoMatrizAdj, int vertice_inicial, int vertice_final);

#endif