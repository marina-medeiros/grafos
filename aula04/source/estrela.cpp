#include <iostream>
#include <vector>
#include <utility> // std::pair
#include "../headers/estrela.h"

/*
funciona para o exemplo feito em sala, mas tem problemas:
- pont[qtd_vertices] tem que ser igual ao número final de arcos
- isso tem que ser definido no início da função, então a qtd de arcos tem que estar definida no início

- motivo de ter que ser definido antes:
    "Caso não existam arcos saindo do vértice i, o elemento pont[i] corresponde ao índice do primeiro arco que sai do i+1-ésimo vértice."
    Do jeito que está agora, caso não tenham arcos saindo do último vértice, teremos um erro.
*/

void Estrela::gerar_estrela(std::vector<std::vector<int>> matriz_adj){
    int qtd_vertices = int(matriz_adj.size());
    int conta_arcos = 0;
    int arco_saindo = 0;
    int linha_anterior_zerada = 0;
    
    for(int ii = 0; ii < qtd_vertices; ii++){
        for(int jj = 0; jj < qtd_vertices; jj++){
            if(matriz_adj[ii][jj] != 0){
                pesos.push_back(matriz_adj[ii][jj]);
                inicio_fim.push_back(std::make_pair(ii+1, jj+1));

                conta_arcos++;
                if(arco_saindo == 0){
                    pont.push_back(conta_arcos);
                    if(linha_anterior_zerada){
                        pont[ii-1] = conta_arcos;
                        linha_anterior_zerada = 0;
                    }
                }
                arco_saindo = 1;
            }
        }
        if(arco_saindo == 0){
            pont.push_back(-1); // guarda o lugar
            linha_anterior_zerada = 1;
        }
        arco_saindo = 0;
    }
}

void Estrela::imprimir_estrela(){
    for(int ii = 0; ii < int(pesos.size()); ii++){
        std::cout << pesos[ii] << " | ("; 
        std::cout << inicio_fim[ii].first << "," << inicio_fim[ii].second << ") | ";
        if(ii < int(pont.size())){    
            std::cout << pont[ii];
        }else{
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}