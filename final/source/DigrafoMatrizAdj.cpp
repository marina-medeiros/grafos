#include <iostream>
#include <queue>
#include <fstream>

#include "../headers/DigrafoMatrizAdj.h"

void DigrafoMatrizAdj::inserir_aresta(int u, int v, int peso) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] == 0) {
            qtd_arestas++;
        }

        matriz_adj[u][v] = peso;
    }
}

void DigrafoMatrizAdj::remover_aresta(int u, int v) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] != 0) {
            qtd_arestas--;
        }
        matriz_adj[u][v] = 0;
    }
}