#ifndef BUSCA_PROFUNDIDADE_DIGRAFO_H
#define BUSCA_PROFUNDIDADE_DIGRAFO_H

#include <map>

#include "../../aula04/headers/grafo.h"


enum class Cor { BRANCO, CINZA, PRETO };
std::map<int, int> busca_profundidade_digrafo_completa(Grafo& grafo, int verticeInicial);
void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    std::map<int, std::list<int>>& lista_adj,
                                    std::vector<Cor>& cores,
                                    std::vector<int>& predecessor,
                                    std::vector<int>& tempo_entrada,
                                    std::vector<int>& tempo_saida,
                                    std::vector<std::pair<int, int>>& arestas_retorno,
                                    std::vector<std::pair<int, int>>& arestas_avanco,
                                    std::vector<std::pair<int, int>>& arestas_cruzamento,
                                    int& tempo1, int& tempo2);
void exportar_arvore_profundidade_para_dot(const std::string& filename, std::map<int, int> arvore, 
                                                std::vector<std::pair<int, int>> arestas_retorno, 
                                                std::vector<std::pair<int, int>> arestas_avanco, 
                                                std::vector<std::pair<int, int>> arestas_cruzamento);

#endif