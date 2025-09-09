#include <iostream>
#include <stack>
#include <vector>
#include <map>

#include "../aula04/headers/grafo.h"
#include "headers/busca-profundidade.h"

void gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}

int main() {
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

    std::cout << "Matriz de adjacência:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    std::cout << "Busca em profundidade iterativa:" << std::endl << std::endl;
    std::map<int, int> arvore = busca_profundidade_matriz_adj_iterativa(grafo_simples, 4);

    exportar_arvore_profundidade_para_dot("arvore_profundidade-grafo_simples.dot", arvore);
    gerar_imagem("arvore_profundidade-grafo_simples.dot", "arvore_profundidade-grafo_simples.png");

    std::cout << std::endl << "Busca em profundidade recursiva:" << std::endl << std::endl;
    std::map<int, int> arvore_recursiva = busca_profundidade_lista_adj_recursiva(grafo_simples, 4);

    exportar_arvore_profundidade_para_dot("arvore_profundidade-grafo_simples_recursivo.dot", arvore_recursiva);
    gerar_imagem("arvore_profundidade-grafo_simples_recursivo.dot", "arvore_profundidade-grafo_simples_recursivo.png");
}