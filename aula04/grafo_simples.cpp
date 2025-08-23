#include <iostream>
#include <vector>
#include <bits/stdc++.h>

class Grafo{
    std::vector<std::vector<int>> matriz_adj;
    int qtd_vertices = 0;

    public:
    
    Grafo(){ 
        matriz_adj = std::vector<std::vector<int>> (0, std::vector<int>(0, 0));
    }

    void inserir_vertice(){
        qtd_vertices++;
        
        matriz_adj.resize(qtd_vertices);

        for(auto& row : matriz_adj){
            row.resize(qtd_vertices, 0);
        }
    }

    void inserir_aresta(int u, int v){
        matriz_adj[u-1][v-1] = 1;
        matriz_adj[v-1][u-1] = 1;
    }

    void remover_aresta(int u, int v){
        matriz_adj[u-1][v-1] = 0;
        matriz_adj[v-1][u-1] = 0;
    }

    void remover_vertice(int v){
        matriz_adj.erase(matriz_adj.begin() + v-1);

        for(int ii = 0; ii < qtd_vertices-1; ii++){
            matriz_adj[ii].erase(matriz_adj[ii].begin() + v-1);
        }

        qtd_vertices--;

        matriz_adj.resize(qtd_vertices);

        for(auto& row : matriz_adj){
            row.resize(qtd_vertices, 0);
        }
    }

    void print_matrix_adj(){
        for(int ii = 0; ii < qtd_vertices; ii++){
            for(int jj = 0; jj < qtd_vertices; jj++){
                std::cout << matriz_adj[ii][jj] << " ";
            }
            std::cout << std::endl;
        }
            std::cout << std::endl;
    }
};

int main(){
    Grafo grafo_simples;

    for(int ii = 0; ii < 6; ii++){
        grafo_simples.inserir_vertice();
    }

    grafo_simples.inserir_aresta(1, 4);
    grafo_simples.inserir_aresta(2, 4);
    grafo_simples.inserir_aresta(2, 3);
    grafo_simples.inserir_aresta(3, 4);
    grafo_simples.inserir_aresta(5, 4);
    grafo_simples.inserir_aresta(6, 4);
    grafo_simples.inserir_aresta(5, 6);

    grafo_simples.print_matrix_adj();

    grafo_simples.remover_aresta(5,6);

    grafo_simples.print_matrix_adj();

    grafo_simples.remover_vertice(3);

    grafo_simples.print_matrix_adj();

}