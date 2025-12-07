#ifndef PRIM_H
#define PRIM_H
#include "../../final/headers/GrafoListaAdj.h"
#include "arvore-minima.h"
#include <vector>

int findMin(const std::vector<int>& key, const std::vector<bool>& in_agm);
GrafoMatrizAdj prim(const GrafoMatrizAdj& grafoMatrizAdj);

#endif