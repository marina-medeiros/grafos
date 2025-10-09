#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "headers/Grafo.h"
//#include "headers/Digrafo.h"
#include "headers/arvore_bfs.h"
#include "headers/busca-largura.h"
#include "headers/busca-largura-digrafo.h"
#include "headers/busca-profundidade-digrafo.h"
#include "headers/busca-profundidade.h"
#include "headers/GrafoListaAdj.h"
#include "headers/GrafoMatrizAdj.h"
#include "headers/GrafoMatrizInc.h"
#include "headers/DigrafoMatrizAdj.h"
#include "headers/DigrafoListaAdj.h"




int main(){
    // GrafoListaAdj grafo_bfs_simples(10);

    // grafo_bfs_simples.inserir_aresta(1, 10, 1);
    // grafo_bfs_simples.inserir_aresta(1, 4, 1);
    // grafo_bfs_simples.inserir_aresta(1, 3, 1);
    // grafo_bfs_simples.inserir_aresta(2, 10, 1);
    // grafo_bfs_simples.inserir_aresta(2, 3, 1);
    // grafo_bfs_simples.inserir_aresta(3, 4, 1);
    // grafo_bfs_simples.inserir_aresta(3, 5, 1);
    // grafo_bfs_simples.inserir_aresta(4, 5, 1);
    // grafo_bfs_simples.inserir_aresta(4, 8, 1);
    // grafo_bfs_simples.inserir_aresta(5, 6, 1);
    // grafo_bfs_simples.inserir_aresta(5, 7, 1);
    // grafo_bfs_simples.inserir_aresta(6, 7, 1);
    // grafo_bfs_simples.inserir_aresta(7, 10, 1);
    // grafo_bfs_simples.inserir_aresta(8, 9, 1);

    

    // ArvoreLargura arvore_bfs_simples = busca_largura_arestas_retorno(grafo_bfs_simples, 0);
    // arvore_bfs_simples.exportar_arvore_bfs(arvore_bfs_simples, "arvore_bfs_t.dot");
    // gerar_imagem("arvore_bfs_t.dot", "arvore_bfs_t.png");

    // GrafoListaAdj grafos_dfs_simples(10);


    // grafos_dfs_simples.inserir_aresta(1, 2, 1); // s -- a
    // grafos_dfs_simples.inserir_aresta(1, 8, 1); // s -- g
    // grafos_dfs_simples.inserir_aresta(1, 3, 1); // s -- b

    // // Arestas de a (2)
    // grafos_dfs_simples.inserir_aresta(2, 4, 1); // a -- c
    // grafos_dfs_simples.inserir_aresta(2, 5, 1); // a -- d

    // // Arestas de b (3)
    // grafos_dfs_simples.inserir_aresta(3, 1, 1); // b -- s

    // // Arestas de c (4)
    // grafos_dfs_simples.inserir_aresta(4, 5, 1); // c -- d
    // grafos_dfs_simples.inserir_aresta(4, 6, 1); // c -- e
    
    // // Arestas de d (5)
    // grafos_dfs_simples.inserir_aresta(5, 6, 1); // d -- e

    // // Arestas de e (6)
    // grafos_dfs_simples.inserir_aresta(6, 7, 1); // e -- f
    // // grafos_dfs_simples.inserir_aresta(6, 8, 1); // e -- g
    
    // // Arestas de g (8)
    // grafos_dfs_simples.inserir_aresta(8, 9, 1); // f -- h

    // // Arestas de h (9)
    // grafos_dfs_simples.inserir_aresta(9, 10, 1); // h -- i

    // auto resultado_dfs = busca_profundidade_lista_adj_recursiva(grafos_dfs_simples, 1);
    // std::map<int, int> predecessores_dfs = resultado_dfs.first;
    // std::vector<std::pair<int, int>> arestas_retorno_dfs = resultado_dfs.second;

    // if (!predecessores_dfs.empty()) {
    //     exportar_arvore_profundidade_para_dot("dfs_com_retorno.dot", predecessores_dfs, arestas_retorno_dfs);
    //     gerar_imagem("dfs_com_retorno.dot", "dfs_com_retorno.png");
    // }

    DigrafoListaAdj grafo_dir(8);
    // grafo_dir.inserir_aresta(1, 2, 1);
    // grafo_dir.inserir_aresta(1, 4, 1);
    // grafo_dir.inserir_aresta(2, 5, 1);
    // grafo_dir.inserir_aresta(4, 5, 1);
    // grafo_dir.inserir_aresta(5, 1, 1);
    // grafo_dir.inserir_aresta(3, 5, 1);
    // grafo_dir.inserir_aresta(3, 1, 1);
    // grafo_dir.inserir_aresta(6, 7, 1);
    // grafo_dir.inserir_aresta(6, 3, 1);
    // grafo_dir.inserir_aresta(7, 8, 1);
    // grafo_dir.inserir_aresta(8, 7, 1);

    grafo_dir.inserir_aresta(0, 1, 1);
    grafo_dir.inserir_aresta(0, 3, 1);
    grafo_dir.inserir_aresta(1, 4, 1);
    grafo_dir.inserir_aresta(3, 4, 1);
    grafo_dir.inserir_aresta(4, 0, 1);
    grafo_dir.inserir_aresta(2, 4, 1);
    grafo_dir.inserir_aresta(2, 0, 1);
    grafo_dir.inserir_aresta(5, 6, 1);
    grafo_dir.inserir_aresta(5, 2, 1);
    grafo_dir.inserir_aresta(6, 7, 1);
    grafo_dir.inserir_aresta(7, 6, 1);

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl << std::endl;

    grafo_dir.print();

    // std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    // grafo_dir.print_matriz_adj();

    // grafo_dir.gerar_matriz_inc();

    // std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    // grafo_dir.print_matriz_inc();

    // std::cout << "Lista de Adjacência do grafo direcionado:" << std::endl << std::endl;
    // grafo_dir.gerar_lista_adj();
    // grafo_dir.print_lista_adj();

    auto arvore_bfs = busca_largura_digrafo(grafo_dir, 2);
    exportar_arvore_bfs_para_dot("arvore_bfs_digrafo.dot", arvore_bfs.get_qtd_vertices(), arvore_bfs);
    gerar_imagem("arvore_bfs_digrafo.dot", "arvore_bfs_digrafo.png");

    // std::map<int, int> arvore = busca_profundidade_digrafo_completa(grafo_dir, 2);

    // grafo_dir.exportar_para_dot("grafo_dir_bl.dot");
    // gerar_imagem("grafo_dir_bl.dot", "grafo_dir_bl.png");

    DigrafoListaAdj grafo_p(10);
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

    // grafo_p.inserir_aresta(1, 2, 1); // s -> a
    // grafo_p.inserir_aresta(1, 3, 1); // s -> b
    // grafo_p.inserir_aresta(1, 8, 1); // s -> g
    // grafo_p.inserir_aresta(2, 4, 1); // a -> c
    // grafo_p.inserir_aresta(4, 3, 1); // c -> b
    // grafo_p.inserir_aresta(4, 5, 1); // c -> d
    // grafo_p.inserir_aresta(5, 2, 1); // d -> a
    // grafo_p.inserir_aresta(5, 6, 1); // d -> e
    // grafo_p.inserir_aresta(6, 4, 1); // e -> c
    // grafo_p.inserir_aresta(7, 6, 1); // f -> e
    // grafo_p.inserir_aresta(7, 8, 1); // f -> g
    // grafo_p.inserir_aresta(8, 7, 1); // g -> f 
    // grafo_p.inserir_aresta(9, 5, 1); // h -> d
    // grafo_p.inserir_aresta(9, 10, 1); // h -> i

    grafo_p.inserir_aresta(0, 1, 1); // s -> a
    grafo_p.inserir_aresta(0, 2, 1); // s -> b
    grafo_p.inserir_aresta(0, 7, 1); // s -> g
    grafo_p.inserir_aresta(1, 3, 1); // a -> c
    grafo_p.inserir_aresta(3, 2, 1); // c -> b
    grafo_p.inserir_aresta(3, 4, 1); // c -> d
    grafo_p.inserir_aresta(4, 1, 1); // d -> a
    grafo_p.inserir_aresta(4, 5, 1); // d -> e
    grafo_p.inserir_aresta(5, 3, 1); // e -> c
    grafo_p.inserir_aresta(6, 5, 1); // f -> e
    grafo_p.inserir_aresta(6, 7, 1); // f -> g
    grafo_p.inserir_aresta(7, 6, 1); // g -> f 
    grafo_p.inserir_aresta(8, 4, 1); // h -> d
    grafo_p.inserir_aresta(8, 9, 1); // h -> i

    std::cout << "Lista de Adjacência do grafo direcionado:" << std::endl << std::endl;
    grafo_p.print();
    // grafo_p.gerar_lista_adj();
    // grafo_p.print_lista_adj();
    
    // busca_profundidade_digrafo_completa(grafo_p, 0);
    ArvoreBusca arvore_dfs = busca_profundidade_digrafo_completa(grafo_p, 0);
    exportar_arvore_dfs_para_dot("arvore_dfs_digrafo2.dot", arvore_dfs);
    gerar_imagem("arvore_dfs_digrafo2.dot", "arvore_dfs_digrafo2.png");
}