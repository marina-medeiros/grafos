#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "headers/grafo.h"
#include "headers/digrafo.h"

int main(){
    
    // Grafo não direcionado --------------------------------------------------------------------

    Grafo grafo_simples(6);

    grafo_simples.inserir_aresta(1, 4, 3);
    grafo_simples.inserir_aresta(2, 4, 1);
    grafo_simples.inserir_aresta(2, 3, 4);
    grafo_simples.inserir_aresta(3, 4, 2);
    grafo_simples.inserir_aresta(5, 4, 2);
    grafo_simples.inserir_aresta(6, 4, 1);
    grafo_simples.inserir_aresta(5, 6, 1);

    std::cout << "----------- GRAFO NÃO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.exportar_para_dot("grafo_simples_inicial.dot");
    grafo_simples.gerar_imagem("grafo_simples_inicial.dot", "grafo_simples_inicial.png");

    grafo_simples.remover_aresta(5,6);

    std::cout << "Matriz de adjacência após remover a aresta(5-6):"  << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.remover_vertice(3);

    std::cout << "Matriz de adjacência após remover o vértice 3:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.gerar_matriz_inc();

    std::cout << "Matriz de incidência:" << std::endl << std::endl;
    grafo_simples.print_matriz_inc();

    grafo_simples.exportar_para_dot("grafo_simples.dot");
    grafo_simples.gerar_imagem("grafo_simples.dot", "grafo_simples.png");

    grafo_simples.gerar_lista_adj();

    std::cout << "Lista de adjacência:" << std::endl;
    grafo_simples.print_lista_adj();

    // 11 - Função que determina se um grafo é conexo ou não.

    grafo_simples.isConexo() ? std::cout << "O grafo é conexo" << std::endl :  std::cout << "O grafo é não conexo" << std::endl;

    // 12 - Determinar se um grafo é bipartido

    grafo_simples.isBipartido() ? std::cout << "O grafo é bipartido" << std::endl :  std::cout << "O grafo é não bipartido" << std::endl;



    // Grafo direcionado --------------------------------------------------------------------

    Digrafo grafo_direcionado(6);

    grafo_direcionado.inserir_aresta(1, 4, 1);
    grafo_direcionado.inserir_aresta(3, 2, 8);
    grafo_direcionado.inserir_aresta(4, 2, 9);
    grafo_direcionado.inserir_aresta(5, 4, 7);
    grafo_direcionado.inserir_aresta(5, 6, 1);
    grafo_direcionado.inserir_aresta(6, 3, 1);

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matriz_adj();

    grafo_direcionado.gerar_matriz_inc();

    std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matriz_inc();

    grafo_direcionado.exportar_para_dot("grafo_direcionado.dot");
    grafo_direcionado.gerar_imagem("grafo_direcionado.dot", "grafo_direcionado.png");



}