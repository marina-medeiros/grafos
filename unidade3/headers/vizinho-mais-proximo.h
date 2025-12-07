#ifndef VIZINHOPROXIMO_H
#define VIZINHOPROXIMO_H

#include "../../final/headers/DigrafoMatrizAdj.h"

std::pair<std::vector<int>, int> vizinho_mais_proximo(const DigrafoMatrizAdj& grafo, int origem);

#endif