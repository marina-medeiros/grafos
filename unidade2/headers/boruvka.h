#ifndef BORUVKA_H
#define BORUVKA_H
#include "../../final/headers/GrafoMatrizAdj.h"
#include "arvore-minima.h"
#include <vector>

GrafoMatrizAdj boruvka(const GrafoMatrizAdj& grafoMatrizAdj);
void unite_sets(int u, int v, std::vector<int>& parent, std::vector<int>& rank);
int find_set(int u, std::vector<int>& parent);

#endif