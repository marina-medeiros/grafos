#include <queue>
#include <vector>

#include "../headers/Grafo.h"
#include "../headers/busca-largura.h"
#include "../headers/arvore-largura.h"
#include "../headers/GrafoListaAdj.h"

/** 
 * Realiza a busca em largura (BFS) em um grafo a partir de um vértice inicial.
 * Constrói uma árvore de busca e classifica as arestas do grafo. 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao grafo representado por GrafoListaAdj.
 *   verticeInicial - Índice do vértice inicial para a BFS.
 * Retorno:
 *   Um objeto ArvoreLargura representando a árvore gerada pela BFS.
 */
bool busca_largura_colorida_grafo(const Grafo& grafo, int vertice_inicial, std::vector<int>& cores) {
    int qtd_vertices = grafo.get_qtd_vertices();
    if (vertice_inicial < 0 || vertice_inicial >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return false;
    }

    std::queue<int> fila;

    cores[vertice_inicial] = 1;
    fila.push(vertice_inicial);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        // Itera sobre os vértices adjacentes
        for (int v : grafo.get_vizinhos(u)) {
            // Se o adjacente 'v' ainda não foi colorido
            if (cores[v] == 0) {
                // Vértice adjacente recebe cor oposta
                cores[v] = -cores[u];
                fila.push(v);
            }
            // Se vértices adjacentes tiverem a mesma cor, então não é bipartido
            else if (cores[v] == cores[u]) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Realiza a busca em largura (BFS) em um grafo a partir de um vértice inicial.
 * Constrói uma árvore de busca e classifica as arestas do grafo. 
 * Usa a lista de adjacência para realizar a busca.
 * 
 * Parâmetros:
 *   grafo - Referência ao grafo representado por GrafoListaAdj.
 *   verticeInicial - Índice do vértice inicial para a BFS.
 * Retorno:
 *   Um objeto ArvoreLargura representando a árvore gerada pela BFS.
 */
ArvoreLargura busca_largura_arestas_retorno(GrafoListaAdj grafo, int verticeInicial){
    ArvoreLargura arvore(grafo.get_qtd_vertices());
    auto rotulos_grafo = grafo.get_rotulos();
    arvore.set_rotulos(rotulos_grafo);

    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::queue<int> fila;
    int peso = 1;

    visitado[verticeInicial] = true;
    arvore.set_nivel(verticeInicial, 0);
    fila.push(verticeInicial);

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();

    for (auto& [vertice, vizinhos] : lista_adj) {
        vizinhos.sort();
    }

    printf("\n--- Iniciando Busca em Largura a partir de %s ---\n", rotulos_grafo[verticeInicial].c_str());
    printf("Relacionamentos:\n");

    while(!fila.empty()){
        int verticeAtual = fila.front();
        fila.pop();
        for(int vizinho : lista_adj[verticeAtual]){
            if(!visitado[vizinho]){
                visitado[vizinho] = true;
                arvore.set_nivel(vizinho, arvore.get_nivel(verticeAtual)+1);
                std::cout << "   Pai: " << rotulos_grafo[verticeAtual] << ", " << rotulos_grafo[vizinho] << "\n";

                arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, 1);
                predecessor[vizinho] = verticeAtual;

                fila.push(vizinho);
            }else{
                if(arvore.get_matriz_adj()[verticeAtual][vizinho] == 0){
                    if(arvore.get_nivel(verticeAtual)+1 == arvore.get_nivel(vizinho) &&
                       verticeAtual != predecessor[vizinho]){
                        std::cout<< "   Tio: " << rotulos_grafo[verticeAtual] << ", " << rotulos_grafo[vizinho] << std::endl;
                        peso = 4; 
                    }
                    if(predecessor[verticeAtual] == predecessor[vizinho]){
                        std::cout<< "   Irmãos: " << rotulos_grafo[verticeAtual] << ", " << rotulos_grafo[vizinho] << std::endl;
                        peso = 2; 
                    }
                    if(arvore.get_nivel(vizinho) == arvore.get_nivel(verticeAtual) &&
                       predecessor[verticeAtual] != predecessor[vizinho]){
                        std::cout<< "   Primos: " << rotulos_grafo[verticeAtual] << ", " << rotulos_grafo[vizinho] << std::endl;
                        peso = 3; 
                    }
                    arvore.inserir_aresta_ndir(verticeAtual+1, vizinho+1, peso);
                }
            }
        }
    }
    std::cout << std::endl << "Níveis dos vértices:" << std::endl;
    for(int ii = 0; ii < grafo.get_qtd_vertices(); ii++){

        std::cout << "Vértice " << rotulos_grafo[ii] << ": " << arvore.get_nivel(ii) << std::endl;
    }
    std::cout << std::endl;

    return arvore;
}