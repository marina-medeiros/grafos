#ifndef INSERCAOPROXIMA_H
#define INSERCAOPROXIMA_H

#include "../../final/headers/DigrafoMatrizAdj.h"

std::pair<std::vector<int>, int> insercao_mais_barata(const DigrafoMatrizAdj& grafo, int origem);

#endif