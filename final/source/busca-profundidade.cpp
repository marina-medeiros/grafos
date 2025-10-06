#include <iostream>
#include <map>
#include <stack>
#include <vector>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"

/*
    BuscaProfundidade(Grafo G, vértice V) {
        Cria pilha vazia P;
        Empilha (P, v);
        Enquanto P.tamanho > 0 faça {
            u = Consulta(P);
            Se existe aresta uv pertencente ao grafo com v.visitado == 0, então {
                v.visitado = 1
                v.predecessor = u
                Empilha(P, v);
            } Senão {
                Desempilha(P)
            }
        }
    }
*/

std::map<int, int> busca_em_profundidade_grafo(const Grafo& grafo, int vertice_inicial) {
    int qtd_vertices = grafo.get_qtd_vertices();
    std::map<int, int> predecessores;

    if (vertice_inicial <= 0 || vertice_inicial > qtd_vertices) {
        std::cout << "Índice de vértice inválido, busca cancelada" << std::endl;
        return predecessores;
    }

    std::stack<int> pilha;
    std::vector<bool> visitados(qtd_vertices, false);

    pilha.push(vertice_inicial);
    visitados[vertice_inicial] = true;
    predecessores[vertice_inicial] = -1;

    while (!pilha.empty()) {
        int u = pilha.top();
        
        bool encontrou_vizinho_nao_visitado = false;
        for (int v : grafo.get_vizinhos(u)) {
            if (!visitados[v]) {
                visitados[v] = true;
                predecessores[v] = u;
                pilha.push(v);
                
                encontrou_vizinho_nao_visitado = true;
                break;
            }
        }

        if (!encontrou_vizinho_nao_visitado) {
            pilha.pop();
        }
    }

    return predecessores;
}