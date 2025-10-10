#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <vector>
#include "Grafo.h"
#include "arvore-largura.h"
#include "GrafoListaAdj.h"

bool busca_largura_colorida_grafo(const Grafo& grafo, int vertice_inicial, std::vector<int>& cores);
ArvoreLargura busca_largura_arestas_retorno(GrafoListaAdj grafo, int verticeInicial);

#endif