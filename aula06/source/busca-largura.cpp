#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include "../../aula04/headers/grafo.h"
#include "../headers/busca-largura.h"

// Implemente o algoritmo para a busca em largura com matriz de adjacência e sem recorrência.
void busca_largura_matriz_adj_iterativa(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    visitado[verticeInicial] = true;

    std::queue<int> fila;

    fila.push(verticeInicial);
    std::vector<std::vector<int>> matriz_adj = grafo.get_matriz_adj();

    std::cout << "Ordem de visitação:" << std::endl;
    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();

        for(int v = 0; v < grafo.get_qtd_vertices(); v++){
            if(!visitado[v] && matriz_adj[verticeAtual][v] != 0){
                visitado[v] = true;
                predecessor[v] = verticeAtual;
                fila.push(v);
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores:" << std::endl;
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
}

// Implemente o algoritmo para a busca em largura com lista de adjacência e com recorrência, salvando o predecessor.
void busca_largura_lista_adj_recorrencia(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);

    visitado[verticeInicial] = true;

    std::queue<int> fila;

    fila.push(verticeInicial);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    std::cout << "Ordem de visitação:" << std::endl;
    while(!fila.empty()){
        int verticeAtual = fila.front();
        std:: cout << verticeAtual+1 << " ";
        fila.pop();
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                predecessor[vizinho] = verticeAtual;
                fila.push(vizinho);
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores:" << std::endl;
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
}

// Implemente o algoritmo para a busca em largura com arestas de retorno e classificando as arestas como **pai, tio, irmão ou primo**.
Grafo busca_largura_arestas_retorno(Grafo grafo, int verticeInicial){
    Grafo arvore(grafo.get_qtd_vertices());
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::vector<int> nivel(grafo.get_qtd_vertices(), 0);
    std::queue<int> fila;
    int peso = 1;

    visitado[verticeInicial] = true;
    nivel[verticeInicial] = 0;
    fila.push(verticeInicial);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    while(!fila.empty()){
        int verticeAtual = fila.front();
        fila.pop();
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                nivel[vizinho] = nivel[verticeAtual] + 1;
                std::cout<< "Pai: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, 1);
                predecessor[vizinho] = verticeAtual;

                fila.push(vizinho);
            }else{
                if(arvore.get_matriz_adj()[verticeAtual][vizinho] == 0){
                    if(nivel[verticeAtual] + 1 == nivel[vizinho] &&
                       verticeAtual != predecessor[vizinho]){
                        std::cout<< "Tio: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 4; 
                    }
                    if(predecessor[verticeAtual] == predecessor[vizinho]){
                        std::cout<< "Irmãos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 2; 
                    }
                    if(nivel[vizinho] == nivel[verticeAtual] &&
                       predecessor[verticeAtual] != predecessor[vizinho]){
                        std::cout<< "Primos: " << verticeAtual+1 << ", " << vizinho+1 << std::endl;
                        peso = 3; 
                    }
                    arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, peso);
                }
            }
        }
    }

    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){
        std::cout << nivel[ii] << " ";
    }
    std::cout << std::endl;

    return arvore;
}

//teste
void exportar_arvore_bfs(Grafo arvore, const std::string& filename,
                         int raiz, const std::vector<int>& nivel) {
    std::ofstream file(filename);
    file << "digraph BFS_Arvore {\n";
    file << "  rankdir=TB;\n"; // top-bottom (árvore vertical)

    // Declara os nós
    for (int i = 0; i < arvore.get_qtd_vertices(); i++) {
        file << "  " << i+1 << " [label=\"" << i+1 << "\", shape=circle];\n";
    }

    // Cria arestas da árvore
    auto matriz = arvore.get_matriz_adj();
    for (int i = 0; i < arvore.get_qtd_vertices(); i++) {
        for (int j = 0; j < arvore.get_qtd_vertices(); j++) {
            if (matriz[i][j] != 0) {
                file << "  " << i+1 << " -> " << j+1;
                // Diferencia tipos de arestas pela cor
                if (matriz[i][j] == 1) file << " [color=black, penwidth=2];\n"; // árvore
                else if (matriz[i][j] == 2) file << " [color=blue, style=dashed];\n"; // irmãos
                else if (matriz[i][j] == 3) file << " [color=green, style=dotted];\n"; // primos
                else if (matriz[i][j] == 4) file << " [color=red, style=bold];\n";   // tios
                else file << ";\n";
            }
        }
    }

    // Agrupa vértices por nível
    int maxNivel = *max_element(nivel.begin(), nivel.end());
    for (int d = 0; d <= maxNivel; d++) {
        file << "  { rank = same; ";
        for (int i = 0; i < arvore.get_qtd_vertices(); i++) {
            if (nivel[i] == d) file << i+1 << "; ";
        }
        file << "}\n";
    }

    file << "}\n";
}