#ifndef BUSCA_PROFUNDIDADE_DIGRAFO_H
#define BUSCA_PROFUNDIDADE_DIGRAFO_H

#include <map>

#include "Grafo.h"
#include "GrafoListaAdj.h"
#include "DigrafoListaAdj.h"
#include "arvore_busca.h"

enum class Cor { BRANCO, CINZA, PRETO };

ArvoreBusca busca_profundidade_digrafo_completa(DigrafoListaAdj& grafo, int verticeInicial);
void busca_profundidade_digrafo_rec(int ultimoVertice, 
                                    std::map<int, std::list<int>>& lista_adj,
                                    std::vector<Cor>& cores,
                                    ArvoreBusca& arvore,
                                    int& tempo1, int& tempo2);
void exportar_arvore_dfs_para_dot(const std::string& filename,
                                           ArvoreBusca arvore);
#endif