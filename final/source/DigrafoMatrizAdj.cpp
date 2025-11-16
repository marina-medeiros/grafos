#include <iostream>
#include <queue>
#include <fstream>

#include "../headers/DigrafoMatrizAdj.h"

/**
 * Construtor da classe DigrafoMatrizAdj, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *  vertices - Número inicial de vértices no digrafo.
 * Retorno: 
 *  Nenhum.
 */
void DigrafoMatrizAdj::inserir_aresta(int u, int v, int peso) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] == INF) {
            qtd_arestas++;
        }

        matriz_adj[u][v] = peso;
    }
}

/**
 * Remove uma aresta direcionada do vértice u para o vértice v.
 * Se a aresta não existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizAdj::remover_aresta(int u, int v) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] != INF) {
            qtd_arestas--;
        }
        matriz_adj[u][v] = INF;
    }
}