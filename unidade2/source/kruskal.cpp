#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../../final/headers/GrafoMatrizAdj.h"
#include "arvore-minima.h"

bool encontra_ciclo(const GrafoListaAdj& grafo){
    std::vector<std::pair<int, int>> arestas_retorno = busca_profundidade_lista_adj_recursiva(grafo, 0).second;

    if(arestas_retorno.size() > 0){
        return true;
    }
    return false;
}

int partition(std::vector<std::vector<int>> &arestas_e_pesos, int low, int high){
    int pivot = arestas_e_pesos[high][2];
    int ii = (low - 1);

    for(int jj = low; jj <= high - 1; jj++){
        if(arestas_e_pesos[jj][2] <= pivot){
            ii++;
            swap(arestas_e_pesos[ii], arestas_e_pesos[jj]);
        }
    }

    swap(arestas_e_pesos[ii+1], arestas_e_pesos[high]);
    return(ii+1);
}

void quickSort_arestas(std::vector<std::vector<int>> &arestas_e_pesos, int low, int high){
    if(low < high){
        int pi = partition(arestas_e_pesos, low, high);

        quickSort_arestas(arestas_e_pesos, low, pi - 1);
        quickSort_arestas(arestas_e_pesos, pi + 1, high);
    }
}

std::vector<std::vector<int>> ordenar_arestas(const GrafoMatrizAdj& grafo){
    std::vector<std::vector<int>> arestas_e_pesos;
    std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();

    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices(); jj++){
            std::cout << matriz_adj[ii][jj] << "  ";
        }
        std::cout << std::endl;
    }

    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        for(int jj = 0; jj < grafo.get_qtd_vertices(); jj++){
            if(matriz_adj[ii][jj] != 0  && ii <= jj){
                std::vector<int> aresta = {ii, jj, matriz_adj[ii][jj]};
                arestas_e_pesos.push_back(aresta);
            }
        }
    }

    quickSort_arestas(arestas_e_pesos, 0, arestas_e_pesos.size() - 1);

    std::cout << "quicksort" << std::endl;
    for(int ii = 0; ii < arestas_e_pesos.size(); ii++){
        std::cout << arestas_e_pesos[ii][0] << " " << arestas_e_pesos[ii][1] << " " << arestas_e_pesos[ii][2] << std::endl;
    }
    std::cout << "fim da ordenação" << std::endl;

    return arestas_e_pesos;
}

GrafoMatrizAdj gerar_arvore_minima(const GrafoMatrizAdj& grafoMatrizAdj, const GrafoListaAdj& grafoListaAdj){
    int qtd_vertices = grafoListaAdj.get_qtd_vertices();
    int qtd_arestas = 0;
    GrafoMatrizAdj agm_matriz_adj(qtd_vertices);
    GrafoListaAdj agm_lista_adj(qtd_vertices);
    
    std::vector<std::vector<int>> arestas_ordenadas = ordenar_arestas(grafoMatrizAdj);

    int indice_aresta = 0;

    while(qtd_arestas < (qtd_vertices - 1)){
        std::vector<int> aresta = arestas_ordenadas[indice_aresta];
        std::cout << "aresta da vez: " << indice_aresta << std::endl;
        std::cout << "aresta: " << aresta[0] << " " << aresta[1] << " peso: " << aresta[2] << std::endl;

        

        qtd_arestas++;
        indice_aresta++;
    }

    return agm_matriz_adj;
}