#ifndef BUSCA_PROFUNDIDADE_DIGRAFO_H
#define BUSCA_PROFUNDIDADE_DIGRAFO_H

#include <map>

#include "../../aula04/headers/grafo.h"


void busca_profundidade_digrafo_completa(Grafo grafo, int verticeInicial);
void busca_profundidade_digrafo_rec(int ultimoVertice, std::vector<bool> &visitado,
                                        std::vector<int> &predecessor, 
                                        std::map<int, std::list<int>> &lista_adj);

#endif