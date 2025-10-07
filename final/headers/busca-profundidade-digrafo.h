#ifndef BUSCA_PROFUNDIDADE_DIGRAFO_H
#define BUSCA_PROFUNDIDADE_DIGRAFO_H

#include <map>

#include "grafo.h"


enum class Cor { BRANCO, CINZA, PRETO };
std::map<int, int> busca_profundidade_digrafo_completa(Grafo& grafo, int verticeInicial);
void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    std::map<int, std::list<int>>& lista_adj,
                                    std::vector<Cor>& cores,
                                    std::map<int, int>& predecessores,
                                    std::vector<int>& predecessor,
                                    std::vector<int>& tempo_entrada,
                                    std::vector<int>& tempo_saida,
                                    std::vector<std::pair<int, int>>& arestas_retorno,
                                    std::vector<std::pair<int, int>>& arestas_avanco,
                                    std::vector<std::pair<int, int>>& arestas_cruzamento,
                                    int& tempo1, int& tempo2);
void exportar_arvore_dfs_para_dot(const std::string& filename,
                                           const std::map<int, int>& predecessores,
                                           const std::vector<std::pair<int, int>>& arestas_retorno,
                                           const std::vector<std::pair<int, int>>& arestas_avanco,
                                           const std::vector<std::pair<int, int>>& arestas_cruzamento);
void gerar_imagem_dsfd(const std::string& dotfile, const std::string& imgfile);
#endif