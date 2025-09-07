#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <map>

#include "../../aula04/headers/grafo.h"

void busca_largura_matriz_adj_iterativa(Grafo grafo, int verticeInicial);
void busca_largura_lista_adj_recorrencia(Grafo grafo, int verticeInicial);
Grafo busca_largura_arestas_retorno(Grafo grafo, int verticeInicial);

#endif