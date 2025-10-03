#include <stack>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "../headers/grafo.h"
#include "../headers/busca-profundidade.h"

bool isConexo(Grafo& grafo){
    int qtd_vertices = grafo.get_qtd_vertices();

    if (qtd_vertices <= 1) {
        return true;
    }

    std::map<int, int> dfs = busca_profundidade_lista_adj_recursiva(grafo, 1);

    int qtd_visitados = dfs.size();

    return qtd_visitados == qtd_vertices;
}