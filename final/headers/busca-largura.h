#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <map>

#include "grafo.h"
#include "arvore-largura.h"

void busca_largura_matriz_adj_iterativa(Grafo grafo, int verticeInicial);
void busca_largura_lista_adj_recorrencia(Grafo grafo, int verticeInicial);
bool busca_largura_colorida(Grafo& grafo, int v, std::vector<int>& cores);
ArvoreLargura busca_largura_arestas_retorno(Grafo grafo, int verticeInicial);
void exportar_arvore_bfs(const Grafo& arvore, const std::string& filename,
                         int raiz, const std::vector<int>& nivel);
#endif