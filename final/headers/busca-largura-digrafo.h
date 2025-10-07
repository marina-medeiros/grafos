#ifndef BUSCA_LARGURA_DIGRAFO_H
#define BUSCA_LARGURA_DIGRAFO_H

#include <map>

#include "grafo.h"

bool eh_ancestral(int u_descendente, int v_ancestral, const std::vector<int>& predecessor);
void busca_largura_digrafo(Grafo grafo, int verticeInicial);
void exportar_arvore_bfs_para_dot(const std::string& filename,
                                  int qtd_vertices,
                                  std::vector<int> predecessores,
                                  const std::vector<std::pair<int, int>>& arestas_retorno,
                                  const std::vector<std::pair<int, int>>& arestas_avanco,
                                  const std::vector<std::pair<int, int>>& arestas_cruzamento);
void gerar_imagem_bsfd(const std::string& dotfile, const std::string& imgfile);
#endif