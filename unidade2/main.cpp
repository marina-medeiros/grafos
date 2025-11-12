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
    GrafoMatrizAdj grafoMatrizAdj(5);
    
    grafoMatrizAdj.inserir_aresta(1, 2, 1);
    grafoMatrizAdj.inserir_aresta(1, 3, 20);
    grafoMatrizAdj.inserir_aresta(2, 3, 17);
    grafoMatrizAdj.inserir_aresta(0, 2, 85);
    grafoMatrizAdj.inserir_aresta(0, 3, 22);
    grafoMatrizAdj.inserir_aresta(1, 4, 86);
    grafoMatrizAdj.inserir_aresta(3, 4, 23);
    grafoMatrizAdj.inserir_aresta(0, 4, 86);
    grafoMatrizAdj.inserir_aresta(0, 1, 15);
    grafoMatrizAdj.inserir_aresta(2, 4, 90);
    
    gerar_arvore_minima(grafoMatrizAdj);
}