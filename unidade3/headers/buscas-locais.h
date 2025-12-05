#ifndef BUSCASLOCAIS_H
#define BUSCASLOCAIS_H

#include "../../final/headers/DigrafoMatrizAdj.h"

std::pair<std::vector<int>, int> busca_local(std::pair<std::vector<int>, int> solucao, int tipo_busca, int heuristica, const DigrafoMatrizAdj &grafo);
int calcula_custo(std::vector<int> ordem_vertices, const DigrafoMatrizAdj &grafo);

std::pair<std::vector<int>, int> swap(std::pair<std::vector<int>, int> solucao, int vertice, int swap_pos, const DigrafoMatrizAdj &grafo);
std::pair<std::vector<int>, int> shift(std::pair<std::vector<int>, int> solucao, int vertice, int shift_pos, const DigrafoMatrizAdj &grafo);
std::pair<std::vector<int>, int> invert(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo);

std::vector<std::pair<std::vector<int>, int>> vizinhanca_swap(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo);
std::vector<std::pair<std::vector<int>, int>> vizinhanca_shift(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo);
std::vector<std::pair<std::vector<int>, int>> vizinhanca_invert(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo);

void imprimir_solucao(const std::pair<std::vector<int>, int> &sol, std::vector<std::string> &rotulos);
void imprimir_busca_local(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo);

#endif