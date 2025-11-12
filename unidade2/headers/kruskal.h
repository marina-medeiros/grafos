#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../../final/headers/GrafoMatrizAdj.h"
#include "arvore-minima.h"

bool encontra_ciclo(const GrafoListaAdj& grafo);
GrafoMatrizAdj gerar_agm_kruskal(const GrafoMatrizAdj& grafoMatrizAdj);
std::vector<std::vector<int>> ordenar_arestas(const GrafoMatrizAdj& grafo);

#endif