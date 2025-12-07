#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <fstream>
#include <limits>

#include "../headers/Grafo.h"
#include "../headers/DigrafoListaAdjPonderada.h"

const int INF = std::numeric_limits<int>::max() / 2;

/**
 * @brief Função auxiliar estática para imprimir o caminho mínimo recursivamente.
 *
 * Percorre o vetor de predecessores de trás para frente e imprime o caminho formatado no console.
 *
 * @param vertice_inicial O nó de origem do caminho.
 * @param vertice_final O nó de destino (ou nó atual da recursão).
 * @param predecessor Vetor contendo o predecessor de cada nó no caminho.
 */
static void imprimir_caminho_recursivo(int vertice_inicial, int vertice_final, const std::vector<int>& predecessor) {
    if (vertice_final == vertice_inicial) {
        std::cout << vertice_inicial+1;
        return;
    }
    if (predecessor[vertice_final] == -1) {
        std::cout << "Nenhum caminho de " << vertice_inicial+1 << " para " << vertice_final+1 << " encontrado.";
        return;
    }
    imprimir_caminho_recursivo(vertice_inicial, predecessor[vertice_final], predecessor);
    std::cout << " -> " << vertice_final+1;
}

/**
 * @brief Executa o algoritmo Bellman-Ford para encontrar caminhos mais curtos.
 *
 * Calcula as distâncias mais curtas do vértice de origem 's' para todos os outros
 * vértices, populando os vetores 'distancia' e 'predecessor' 
 *
 * Também detecta a presença de ciclos negativos.
 *
 * @param grafo O digrafo ponderado que será analisado.
 * @param s O índice do vértice de origem.
 * @param distancia Vetor (referência) que será preenchido com as distâncias mínimas.
 * @param predecessor Vetor (referência) que será preenchido com os predecessores.
 * @return true caso o algoritmo for concluído com sucesso (sem ciclos negativos).
 * @return false caso um ciclo de peso negativo for detectado.
 */
bool bellman_ford(const DigrafoListaAdjPonderada& grafo, int s, std::vector<int>& distancia, std::vector<int>& predecessor) {
    int V = grafo.get_qtd_vertices();
    distancia.assign(V, INF);
    predecessor.assign(V, -1);
    distancia[s] = 0;

    for (int i = 1; i <= V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (const auto& par : grafo.get_arestas_saindo(u)) {
                int v = par.first;
                int peso = par.second;
                
                if (distancia[u] != INF && distancia[v] > distancia[u] + peso) {
                    distancia[v] = distancia[u] + peso;
                    predecessor[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < V; ++u) {
        for (const auto& par : grafo.get_arestas_saindo(u)) {
            int v = par.first;
            int peso = par.second;
            
            if (distancia[u] != INF && distancia[v] > distancia[u] + peso) {
                return false; 
            }
        }
    }

    return true; 
}

/**
 * @brief Executa Bellman-Ford e imprime os caminhos da origem 's' para todos os vértices.
 *
 * Chama a função 'bellman_ford' para preencher os vetores distância e predecessor, 
 * em seguida, itera por todos os vértices para imprimir o caminho e a distância de 's' até cada um deles.
 *
 * Também trata e reporta o caso de um ciclo de peso negativo ser detectado.
 *
 * @param grafo O digrafo ponderado que será analisado.
 * @param s O índice do vértice de origem.
 */
void bellman_ford_geral(const DigrafoListaAdjPonderada& grafo, int s) {

    int V = grafo.get_qtd_vertices();

    if (s < 0 || s >= V) {
        std::cerr << "Erro: Vértice de origem " << s+1 << " fora do intervalo [0, " << V << "]." << std::endl;
        return;
    }

    std::vector<int> distancia;
    std::vector<int> predecessor;

    std::cout << "Executando Bellman-Ford, origem " << s+1 << std::endl;
    bool resultado = bellman_ford(grafo, s, distancia, predecessor);

    if (resultado) {
        std::cout << "\nDistâncias mais curtas a partir de " << s+1 << ":" << std::endl << std::endl;
        for (int i = 0; i < V; ++i) {
            std::cout << "Vértice " << i+1 << ": ";
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

/**
 * @brief Executa Bellman-Ford e imprime o caminho mais curto entre dois determinados vértices.
 *
 * Chama a função 'bellman_ford' para calcular os caminhos, imprimindo apenas o resultado 
 * (distância e caminho) para o vértice de destino 'd'.
 *
 * @param grafo O digrafo ponderado que será analisado.
 * @param s O índice do vértice de origem.
 * @param d O índice do vértice de destino.
 */
void bellman_ford_especifico(const DigrafoListaAdjPonderada& grafo, int s, int d) {
    int V = grafo.get_qtd_vertices();

    if (s < 0 || s >= V) {
        std::cerr << "Erro: Vértice de origem " << s+1 << " fora do intervalo [0, " << V << "]." << std::endl;
        return;
    }
    if (d < 0 || d >= V) {
        std::cerr << "Erro: Vértice de destino " << d+1 << " fora do intervalo [0, " << V << "]." << std::endl;
        return;
    }

    std::vector<int> distancia;
    std::vector<int> predecessor;

    std::cout << "Executando Bellman-Ford, origem " << s+1 << ", destino " << d+1 << std::endl;
    bool resultado = bellman_ford(grafo, s, distancia, predecessor);

    if (resultado) {
        std::cout << "\nCaminho mais curto de " << s+1 << " para " << d+1 << ":" << std::endl;

        if (distancia[d] == INF) {
            std::cout << "\nDestino " << d+1 << ": Inalcançável (INF)" << std::endl;
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