#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "headers/busca-largura.h"

int main(){
    Grafo grafo_simples;

    for(int ii = 0; ii < 11; ii++){
        grafo_simples.inserir_vertice();
    }

    grafo_simples.inserir_aresta_ndir(1, 2, 1);
    grafo_simples.inserir_aresta_ndir(1, 3, 1);
    grafo_simples.inserir_aresta_ndir(2, 3, 1);
    grafo_simples.inserir_aresta_ndir(2, 4, 1);
    grafo_simples.inserir_aresta_ndir(2, 8, 1);
    grafo_simples.inserir_aresta_ndir(2, 11, 1);
    grafo_simples.inserir_aresta_ndir(3, 4, 1);
    grafo_simples.inserir_aresta_ndir(3, 5, 1);
    grafo_simples.inserir_aresta_ndir(4, 8, 1);
    grafo_simples.inserir_aresta_ndir(4, 7, 1);
    grafo_simples.inserir_aresta_ndir(4, 9, 1);
    grafo_simples.inserir_aresta_ndir(5, 6, 1);
    grafo_simples.inserir_aresta_ndir(7, 10, 1);
    grafo_simples.inserir_aresta_ndir(7, 11, 1);
    grafo_simples.inserir_aresta_ndir(9, 11, 1);
    grafo_simples.inserir_aresta_ndir(10, 11, 1);

    busca_largura_matriz_adj_iterativa(grafo_simples, 6);
    busca_largura_lista_adj_recorrencia(grafo_simples, 6);

    Grafo grafo_retorno(10);

    grafo_retorno.inserir_aresta_ndir(1, 10, 1);
    grafo_retorno.inserir_aresta_ndir(1, 4, 1);
    grafo_retorno.inserir_aresta_ndir(1, 3, 1);
    grafo_retorno.inserir_aresta_ndir(2, 10, 1);
    grafo_retorno.inserir_aresta_ndir(2, 3, 1);
    grafo_retorno.inserir_aresta_ndir(3, 4, 1);
    grafo_retorno.inserir_aresta_ndir(3, 5, 1);
    grafo_retorno.inserir_aresta_ndir(4, 5, 1);
    grafo_retorno.inserir_aresta_ndir(4, 8, 1);
    grafo_retorno.inserir_aresta_ndir(5, 6, 1);
    grafo_retorno.inserir_aresta_ndir(5, 7, 1);
    grafo_retorno.inserir_aresta_ndir(6, 7, 1);
    grafo_retorno.inserir_aresta_ndir(7, 10, 1);
    grafo_retorno.inserir_aresta_ndir(8, 9, 1);

    grafo_retorno.exportar_para_dot("retorno.dot", 0);
    gerar_imagem("retorno.dot", "retorno.png");

    Grafo arvore_retorno = busca_largura_arestas_retorno(grafo_retorno, 0);

    arvore_retorno.exportar_para_dot("arvore.dot", 0);
    gerar_imagem("arvore.dot", "arvore.png");
}