#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include "Grafo.h"
#include "DigrafoMatrizAdj.h"

struct ResultadoFloydWarshall {
    std::vector<std::vector<int>> dist;
    std::vector<std::vector<int>> pred;
};

ResultadoFloydWarshall floyd_warshall(const DigrafoMatrizAdj& grafoMatrizAdj);
void imprimirMatrizDistancias(const std::vector<std::vector<int>>& dist);

#endif