#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <vector>
#include "Grafo.h"
#include "arvore-largura.h"
#include "GrafoListaAdj.h"

/**
 * @brief Tenta colorir um componente conexo de um grafo com duas cores (Busca em Largura).
 * Inicia uma travessia BFS a partir de um vértice, colorindo seus vizinhos com
 * cores alternadas. Se encontrar um vizinho que já foi colorido com a mesma cor
 * que o vértice atual, o componente não é bipartido.
 * * @param grafo O grafo a ser percorrido.
 * @param vertice_inicial O vértice de início para a busca neste componente.
 * @param cores Um vetor de inteiros passado por referência, que armazena as cores
 * dos vértices (0: não colorido, 1: cor A, -1: cor B).
 * @return true se o componente conexo for bipartido, false caso contrário.
 */
bool busca_largura_colorida_grafo(const Grafo& grafo, int vertice_inicial, std::vector<int>& cores);

ArvoreLargura busca_largura_arestas_retorno(GrafoListaAdj grafo, int verticeInicial);
#endif