#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>

#include "../headers/GrafoListaAdj.h"
#include "../headers/GrafoMatrizAdj.h"

const int GrafoMatrizAdj::INF = std::numeric_limits<int>::max() / 2;

/**
 * Construtor da classe GrafoMatrizAdj, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *  vertices - Número inicial de vértices no grafo.
 * Retorno: 
 *  Nenhum.
 */
GrafoMatrizAdj::GrafoMatrizAdj(int vertices) : Grafo(vertices) {
    matriz_adj.resize(vertices, std::vector<int>(vertices, INF));
}

/**
 * Limpa o grafo, removendo todos os vértices e arestas.
 * Reseta a quantidade de vértices e arestas para zero.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void GrafoMatrizAdj::limpar() {
    this->matriz_adj.clear();
    this->rotulos.clear();
    this->qtd_vertices = 0;
    this->qtd_arestas = 0;
}

/**
 * Insere um novo vértice no grafo com um rótulo opcional.
 * Se nenhum rótulo for fornecido, o índice do vértice será usado como rótulo.
 * 
 * Parâmetros:
 *  rotulo - Rótulo opcional para o novo vértice.
 * Retorno:
 *  Nenhum.
 */
void GrafoMatrizAdj::inserir_vertice(const std::string& rotulo) {
    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }

    qtd_vertices++;
    
    matriz_adj.resize(qtd_vertices);
    for (auto& row : matriz_adj) {
        row.resize(qtd_vertices, INF);
    }
}

/**
 * Remove um vértice do grafo, eliminando todas as arestas associadas a ele.
 * Reindexa os vértices restantes para manter a consistência dos índices.   
 * 
 * Parâmetros:
 *  u - Índice do vértice a ser removido.
 * Retorno:
 *  Nenhum.
 */
void GrafoMatrizAdj::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    }
    
    for (int i = 0; i < qtd_vertices; ++i) {
        if (matriz_adj[u][i] != INF) {
            qtd_arestas--;
        }
    }
    
    matriz_adj.erase(matriz_adj.begin() + u);
    rotulos.erase(rotulos.begin() + u);

    for (auto& linha : matriz_adj) {
        linha.erase(linha.begin() + u);
    }
    
    qtd_vertices--;
}

/**
 * Insere uma aresta não direcionada entre os vértices u e v com o peso especificado.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 *  peso - Peso da aresta (padrão é 1). 
 * Retorno: 
 *  Nenhum.
 */
void GrafoMatrizAdj::inserir_aresta(int u, int v, int peso) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] == INF) {
            qtd_arestas++;
        }
        matriz_adj[u][v] = peso;
        matriz_adj[v][u] = peso; 
    }
}

/**
 * Remove a aresta não direcionada entre os vértices u e v.
 * Se a aresta não existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  Nenhum.
 */
void GrafoMatrizAdj::remover_aresta(int u, int v) {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        if (matriz_adj[u][v] != INF) {
            qtd_arestas--;
        }
        matriz_adj[u][v] = INF;
        matriz_adj[v][u] = INF;
    }
}

/**
 * Verifica se existe uma aresta não direcionada entre os vértices u e v.   
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.   
 * Retorno:
 *  true se a aresta existir, false caso contrário.
 */
bool GrafoMatrizAdj::existe_aresta(int u, int v) const {
    if (u >= 0 && u < qtd_vertices && v >= 0 && v < qtd_vertices) {
        return matriz_adj[u][v] != INF;
    }
    return false;
}

/**
 * Retorna uma lista dos vizinhos do vértice v (vértices adjacentes).
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo vizinhos serão retornados.
 * Retorno:
 *  Uma lista de inteiros representando os índices dos vértices vizinhos.
 */
std::list<int> GrafoMatrizAdj::get_vizinhos(int v) const {
    std::list<int> vizinhos;
    if (v >= 0 && v < qtd_vertices) {
        for (int j = 0; j < qtd_vertices; ++j) {
            if (matriz_adj[v][j] != INF) {
                vizinhos.push_back(j);
            }
        }
    }
    return vizinhos;
}

/**
 * Imprime a matriz de adjacência do grafo no console.
 * Mostra os rótulos dos vértices e os pesos das arestas.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void GrafoMatrizAdj::print() const {
    std::cout << "\n--- Imprimindo Matriz de Adjacência ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo está vazio.\n";
        return;
    }

    std::cout << "\t";
    for (int i = 0; i < qtd_vertices; ++i) {
        if (rotulos.at(i).empty()) {
            std::cout << i << "\t";
        } else {
            std::cout << rotulos.at(i) << "\t";
        }
    }
    std::cout << std::endl;

    for (int i = 0; i < qtd_vertices; ++i) {
        if (rotulos.at(i).empty()) {
            std::cout << i << "\t";
        } else {
            std::cout << rotulos.at(i) << "\t";
        }
        for (int j = 0; j < qtd_vertices; ++j) {
            if (matriz_adj.at(i).at(j) == INF) {
                std::cout << "-\t"; 
            } else {
                std::cout << matriz_adj.at(i).at(j) << "\t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------\n";
}

/**
 * Converte o grafo representado por matriz de adjacência para uma representação por lista de adjacência.
 * Parâmetros:
 *  Nenhum.
 * Retorno: 
 * Um objeto GrafoListaAdj representando o grafo convertido.
 */
GrafoListaAdj GrafoMatrizAdj::converter_para_lista_adj() const {
    GrafoListaAdj lista_adj(qtd_vertices);
    lista_adj.set_rotulos(get_rotulos());

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j = i + 1; j < qtd_vertices; j++) {
            if (matriz_adj[i][j] != INF) {
                lista_adj.inserir_aresta(i, j, matriz_adj[i][j]);
            }
        }
    }

    return lista_adj;
}