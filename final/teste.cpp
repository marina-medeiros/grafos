#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "headers/Grafo.h"
#include "headers/Digrafo.h"
#include "headers/arvore_bfs.h"
#include "headers/busca-largura.h"
#include "headers/busca-largura-digrafo.h"
#include "headers/busca-profundidade-digrafo.h"

int main(){
    Digrafo grafo_dir(8);
    grafo_dir.inserir_aresta(1, 2, 1);
    grafo_dir.inserir_aresta(1, 4, 1);
    grafo_dir.inserir_aresta(2, 5, 1);
    grafo_dir.inserir_aresta(4, 5, 1);
    grafo_dir.inserir_aresta(5, 1, 1);
    grafo_dir.inserir_aresta(3, 5, 1);
    grafo_dir.inserir_aresta(3, 1, 1);
    grafo_dir.inserir_aresta(6, 7, 1);
    grafo_dir.inserir_aresta(6, 3, 1);
    grafo_dir.inserir_aresta(7, 8, 1);
    grafo_dir.inserir_aresta(8, 7, 1);

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl << std::endl;

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    grafo_dir.print_matriz_adj();

    grafo_dir.gerar_matriz_inc();

    std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    grafo_dir.print_matriz_inc();

    std::cout << "Lista de Adjacência do grafo direcionado:" << std::endl << std::endl;
    grafo_dir.gerar_lista_adj();
    grafo_dir.print_lista_adj();

    busca_largura_digrafo(grafo_dir, 2);

    // std::map<int, int> arvore = busca_profundidade_digrafo_completa(grafo_dir, 2);

    grafo_dir.exportar_para_dot("grafo_dir_bl.dot");
    grafo_dir.gerar_imagem("grafo_dir_bl.dot", "grafo_dir_bl.png");

    Digrafo grafo_p(10);
    // grafo_p.inserir_aresta(1, 3, 1); // a -> c
    // grafo_p.inserir_aresta(3, 2, 1); // c -> b
    // grafo_p.inserir_aresta(3, 4, 1); // c -> d
    // grafo_p.inserir_aresta(4, 1, 1); // d -> a
    // grafo_p.inserir_aresta(4, 5, 1); // d -> e
    // grafo_p.inserir_aresta(5, 3, 1); // e -> c
    // grafo_p.inserir_aresta(6, 5, 1); // f -> e
    // grafo_p.inserir_aresta(6, 7, 1); // f -> g
    // grafo_p.inserir_aresta(7, 6, 1); // g -> f 
    // grafo_p.inserir_aresta(8, 4, 1); // h -> d
    // grafo_p.inserir_aresta(8, 9, 1); // h -> i
    // grafo_p.inserir_aresta(10, 1, 1); // s -> a
    // grafo_p.inserir_aresta(10, 2, 1); // s -> b
    // grafo_p.inserir_aresta(10, 7, 1); // s -> h

    grafo_p.inserir_aresta(1, 2, 1); // s -> a
    grafo_p.inserir_aresta(1, 3, 1); // s -> b
    grafo_p.inserir_aresta(1, 8, 1); // s -> g
    grafo_p.inserir_aresta(2, 4, 1); // a -> c
    grafo_p.inserir_aresta(4, 3, 1); // c -> b
    grafo_p.inserir_aresta(4, 5, 1); // c -> d
    grafo_p.inserir_aresta(5, 2, 1); // d -> a
    grafo_p.inserir_aresta(5, 6, 1); // d -> e
    grafo_p.inserir_aresta(6, 4, 1); // e -> c
    grafo_p.inserir_aresta(7, 6, 1); // f -> e
    grafo_p.inserir_aresta(7, 8, 1); // f -> g
    grafo_p.inserir_aresta(8, 7, 1); // g -> f 
    grafo_p.inserir_aresta(9, 5, 1); // h -> d
    grafo_p.inserir_aresta(9, 10, 1); // h -> i

    std::cout << "Lista de Adjacência do grafo direcionado:" << std::endl << std::endl;
    grafo_p.gerar_lista_adj();
    grafo_p.print_lista_adj();
    
    busca_profundidade_digrafo_completa(grafo_p, 0);
}