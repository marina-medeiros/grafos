#ifndef TESTE_HEURISTICAS_H
#define TESTE_HEURISTICAS_H

#include <vector>
#include <utility>
#include "../../final/headers/DigrafoMatrizAdj.h"

void testes_buscas_locais();
// Funções de teste para heurísticas
void testar_swap(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);
void testar_shift(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);
void testar_invert(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);

void testar_vizinhanca_swap(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);
void testar_vizinhanca_shift(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);
void testar_vizinhanca_invert(const DigrafoMatrizAdj &grafo, std::pair<std::vector<int>, int> solucao);

#endif
