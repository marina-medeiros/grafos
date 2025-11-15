#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>
#include <limits>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/GrafoListaAdj.h"
#include "../headers/DigrafoMatrizAdj.h"

const int INF = std::numeric_limits<int>::max() / 2;

static void imprimir_caminho_recursivo(int vertice_inicial, int vertice_final, const std::vector<int>& predecessor) {
    if (vertice_final == vertice_inicial) {
        std::cout << vertice_inicial;
        return;
    }
    if (predecessor[vertice_final] == -1) {
        std::cout << "Nenhum caminho de " << vertice_inicial << " para " << vertice_final << " encontrado.";
        return;
    }
    imprimir_caminho_recursivo(vertice_inicial, predecessor[vertice_final], predecessor);
    std::cout << " -> " << vertice_final;
}


bool bellman_ford(const DigrafoMatrizAdj& grafo, int s, std::vector<int>& distancia, std::vector<int>& predecessor) {
    int V = grafo.get_qtd_vertices();
    distancia.assign(V, INF);
    predecessor.assign(V, -1);
    distancia[s] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (grafo.existe_aresta(u, v)) {
                    int peso_uv = grafo.get_peso(u, v);
                    if (distancia[u] != INF && distancia[v] > distancia[u] + peso_uv) {
                        distancia[v] = distancia[u] + peso_uv;
                        predecessor[v] = u;
                    }
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (grafo.existe_aresta(u, v)) {
                int peso_uv = grafo.get_peso(u, v);
                if (distancia[u] != INF && distancia[v] > distancia[u] + peso_uv) {
                    return false; 
                }
            }
        }
    }

    return true; 
}

void bellman_ford_geral(const DigrafoMatrizAdj& grafo, int s) {
    int V = grafo.get_qtd_vertices();
    std::vector<int> distancia;
    std::vector<int> predecessor;

    std::cout << "Executando Bellman-Ford, origem " << s << std::endl;
    bool resultado = bellman_ford(grafo, s, distancia, predecessor);

    if (resultado) {
        std::cout << "\nDistâncias mais curtas a partir de " << s << ":" << std::endl << std::endl;
        for (int i = 0; i < V; ++i) {
            std::cout << "Vértice " << i << ": ";
            if (distancia[i] == INF) {
                std::cout << "Inalcançável (INF)" << std::endl;
            } else {
                std::cout << "Distância = " << distancia[i];
                std::cout << " | Caminho: ";
                imprimir_caminho_recursivo(s, i, predecessor);
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    } else {
        std::cout << "RESULTADO: Ciclo de peso negativo detectado! Caminho calculado não é válido\n" << std::endl;
    }
}

void bellman_ford_especifico(const DigrafoMatrizAdj& grafo, int s, int d) {
    int V = grafo.get_qtd_vertices();

    if (s < 0 || s >= V) {
        std::cerr << "Erro: Vértice de origem " << s << " fora do intervalo [0, " << V-1 << "]." << std::endl;
        return;
    }
    if (d < 0 || d >= V) {
        std::cerr << "Erro: Vértice de destino " << d << " fora do intervalo [0, " << V-1 << "]." << std::endl;
        return;
    }

    std::vector<int> distancia;
    std::vector<int> predecessor;

    std::cout << "Executando Bellman-Ford, origem " << s << ", destino " << std::endl;
    bool resultado = bellman_ford(grafo, s, distancia, predecessor);

    if (resultado) {
        std::cout << "\nCaminho mais curto de " << s << " para " << d << ":" << std::endl;

        if (distancia[d] == INF) {
            std::cout << "\nDestino " << d << ": Inalcançável (INF)" << std::endl;
        } else {
            std::cout << "\nDistância = " << distancia[d];
            std::cout << " | Caminho: ";
            imprimir_caminho_recursivo(s, d, predecessor);
            std::cout << std::endl;
        }
    } else {
        std::cout << "RESULTADO: Ciclo de peso negativo detectado! Caminho calculado não é válido\n" << std::endl;
    }
}