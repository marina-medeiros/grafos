#ifndef BUSCA_LARGURA_DIGRAFO_H
#define BUSCA_LARGURA_DIGRAFO_H

#include <map>

#include "Grafo.h"
#include "GrafoListaAdj.h"
#include "DigrafoListaAdj.h"
#include "arvore-busca.h"

bool eh_ancestral(int u_descendente, int v_ancestral, const std::vector<int>& predecessor);
ArvoreBusca busca_largura_digrafo(DigrafoListaAdj& grafo, int verticeInicial);
void exportar_arvore_bfs_para_dot(const std::string& filename,
                                  int qtd_vertices,
                                  ArvoreBusca& arvore);
void gerar_imagem_bsfd(const std::string& dotfile, const std::string& imgfile);
#endif