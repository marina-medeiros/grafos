#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <map>
#include <cstdio>
#include <list>

#include "headers/grafo.h"
#include "headers/estrela.h"

void gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}

int main(){
    // Grafo não direcionado --------------------------------------------------------------------

    Grafo grafo_simples;

    for(int ii = 0; ii < 6; ii++){
        grafo_simples.inserir_vertice();
    }

    grafo_simples.inserir_aresta_ndir(1, 4, 3);
    grafo_simples.inserir_aresta_ndir(2, 4, 1);
    grafo_simples.inserir_aresta_ndir(2, 3, 4);
    grafo_simples.inserir_aresta_ndir(3, 4, 2);
    grafo_simples.inserir_aresta_ndir(5, 4, 2);
    grafo_simples.inserir_aresta_ndir(6, 4, 1);
    grafo_simples.inserir_aresta_ndir(5, 6, 1);

    std::cout << "----------- GRAFO NÃO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.exportar_para_dot("grafo_simples_inicial.dot", 0);
    gerar_imagem("grafo_simples_inicial.dot", "grafo_simples_inicial.png");

    grafo_simples.remover_aresta_ndir(5,6);

    std::cout << "Matriz de adjacência após remover a aresta(5-6):"  << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.remover_vertice(3);

    std::cout << "Matriz de adjacência após remover o vértice 3:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.exportar_para_dot("grafo_simples.dot", 0);
    gerar_imagem("grafo_simples.dot", "grafo_simples.png");

    grafo_simples.gerar_lista_adj();

    std::cout << "Lista de adjacência:" << std::endl;
    grafo_simples.print_lista_adj();

    // Grafo direcionado --------------------------------------------------------------------

    Grafo grafo_direcionado;

    for(int ii = 0; ii < 6; ii++){
        grafo_direcionado.inserir_vertice();
    }

    grafo_direcionado.inserir_aresta_dir(1, 4, 1);
    grafo_direcionado.inserir_aresta_dir(3, 2, 8);
    grafo_direcionado.inserir_aresta_dir(4, 2, 9);
    grafo_direcionado.inserir_aresta_dir(5, 4, 7);
    grafo_direcionado.inserir_aresta_dir(5, 6, 1);
    grafo_direcionado.inserir_aresta_dir(6, 3, 1);

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matriz_adj();

    grafo_direcionado.gerar_matriz_inc(1);

    std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matrix_inc();

    grafo_direcionado.exportar_para_dot("grafo_direcionado.dot", 1);
    gerar_imagem("grafo_direcionado.dot", "grafo_direcionado.png");

    std::cout << "----------- ESTRELA DIRETA ----------------------" << std::endl;

    Grafo grafo_estrela;

    for(int ii = 0; ii < 5; ii++){
        grafo_estrela.inserir_vertice();
    }

    grafo_estrela.inserir_aresta_dir(1, 2, 3);
    grafo_estrela.inserir_aresta_dir(1, 3, 2);
    grafo_estrela.inserir_aresta_dir(2, 3, 1);
    grafo_estrela.inserir_aresta_dir(2, 5, 2);
    grafo_estrela.inserir_aresta_dir(4, 3, 1);
    grafo_estrela.inserir_aresta_dir(4, 5, 3);
    grafo_estrela.inserir_aresta_dir(5, 4, 4);

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;
   
    grafo_estrela.print_matriz_adj();

    Estrela estrela(grafo_estrela.get_matriz_adj());

    estrela.imprimir_estrela();
}