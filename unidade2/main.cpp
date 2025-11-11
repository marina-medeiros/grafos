#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../../final/headers/GrafoMatrizAdj.h"
#include "headers/arvore-minima.h"
#include "headers/kruskal.h"

int main(){
    GrafoMatrizAdj grafo_0(4);
    
    grafo_0.inserir_aresta(0, 1, 8);
    grafo_0.inserir_aresta(1, 2, 5);
    grafo_0.inserir_aresta(2, 3, -1);
    grafo_0.inserir_aresta(3, 1, 1);

    ordenar_arestas(grafo_0);
}