#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "headers/busca-largura-digrafo.h"
#include "headers/busca-profundidade-digrafo.h"

int main(){
    Grafo grafo_dir(8);
    grafo_dir.inserir_aresta_dir(1, 2, 1);
    grafo_dir.inserir_aresta_dir(1, 4, 1);
    grafo_dir.inserir_aresta_dir(2, 5, 1);
    grafo_dir.inserir_aresta_dir(4, 5, 1);
    grafo_dir.inserir_aresta_dir(5, 1, 1);
    grafo_dir.inserir_aresta_dir(3, 5, 1);
    grafo_dir.inserir_aresta_dir(3, 1, 1);
    grafo_dir.inserir_aresta_dir(6, 7, 1);
    grafo_dir.inserir_aresta_dir(6, 3, 1);
    grafo_dir.inserir_aresta_dir(7, 8, 1);
    grafo_dir.inserir_aresta_dir(8, 7, 1);

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl << std::endl;

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    grafo_dir.print_matriz_adj();

    grafo_dir.gerar_matriz_inc(1);

    std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    grafo_dir.print_matriz_inc();

    std::cout << "Lista de Adjacência do grafo direcionado:" << std::endl << std::endl;
    grafo_dir.gerar_lista_adj();
    grafo_dir.print_lista_adj();

    busca_largura_digrafo(grafo_dir, 2);

    busca_profundidade_digrafo_completa(grafo_dir, 2);

    grafo_dir.exportar_para_dot("grafo_dir_bl.dot", 1);
    gerar_imagem("grafo_dir_bl.dot", "grafo_dir_bl.png");
    
}