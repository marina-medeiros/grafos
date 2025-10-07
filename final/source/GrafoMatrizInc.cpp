#include <iostream>
#include <queue>
#include <vector>

#include "../headers/GrafoMatrizInc.h"

GrafoMatrizInc::GrafoMatrizInc(int vertices) : Grafo(vertices) {
    matriz_inc.resize(vertices);
}

void GrafoMatrizInc::limpar() {
    this->matriz_inc.clear();
    this->arestas_info.clear();
    this->rotulos.clear();
    this->qtd_vertices = 0;
    this->qtd_arestas = 0;
}

void GrafoMatrizInc::inserir_vertice() {
    rotulos.push_back(std::to_string(qtd_vertices));
    matriz_inc.push_back(std::vector<int>(qtd_arestas, 0));
    qtd_vertices++;
}

void GrafoMatrizInc::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    };

    // 1. Identifica e remove todas as arestas conectadas a 'u'
    std::vector<int> arestas_a_remover;
    for (int j = 0; j < qtd_arestas; ++j) {
        if (matriz_inc[u][j] == 1) {
            arestas_a_remover.push_back(j);
        }
    }
    
    for (int i = arestas_a_remover.size() - 1; i >= 0; --i) {
        int j = arestas_a_remover[i];
        for (auto& linha : matriz_inc) {
            linha.erase(linha.begin() + j);
        }
        arestas_info.erase(arestas_info.begin() + j);
    }
    qtd_arestas -= arestas_a_remover.size();

    // 2. Remove a linha do vértice 'u'
    matriz_inc.erase(matriz_inc.begin() + u);
    rotulos.erase(rotulos.begin() + u);

    // 3. Reindexa as arestas restantes
    for (auto& aresta : arestas_info) {
        if (aresta.first > u) aresta.first--;
        if (aresta.second > u) aresta.second--;
    }
    
    // 4. Atualiza contagem de vértices
    qtd_vertices--;
}

void GrafoMatrizInc::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;

    if (existe_aresta(u, v)) return;

    for (int i = 0; i < qtd_vertices; ++i) {
        matriz_inc[i].push_back(0);
    }

    int nova_aresta_idx = qtd_arestas;
    matriz_inc[u][nova_aresta_idx] = 1;
    matriz_inc[v][nova_aresta_idx] = 1;

    arestas_info.push_back({u, v});
    qtd_arestas++;
}

void GrafoMatrizInc::remover_aresta(int u, int v) {
    int aresta_idx = -1;
    for (int j = 0; j < qtd_arestas; ++j) {
        if ((arestas_info[j].first == u && arestas_info[j].second == v) ||
            (arestas_info[j].first == v && arestas_info[j].second == u)) {
            aresta_idx = j;
            break;
        }
    }

    if (aresta_idx != -1) {
        for (int i = 0; i < qtd_vertices; ++i) {
            matriz_inc[i].erase(matriz_inc[i].begin() + aresta_idx);
        }
        arestas_info.erase(arestas_info.begin() + aresta_idx);
        qtd_arestas--;
    }
}

bool GrafoMatrizInc::existe_aresta(int u, int v) const {
    for (int j = 0; j < qtd_arestas; ++j) {
        if (matriz_inc[u][j] == 1 && matriz_inc[v][j] == 1) {
            return true;
        }
    }
    return false;
}

std::list<int> GrafoMatrizInc::get_vizinhos(int v) const {
    std::list<int> vizinhos;
    if (v < 0 || v >= qtd_vertices) return vizinhos;

    for (int j = 0; j < qtd_arestas; ++j) {
        if (matriz_inc[v][j] == 1) {
            const auto& aresta = arestas_info[j];
            int vizinho = (aresta.first == v) ? aresta.second : aresta.first;
            vizinhos.push_back(vizinho);
        }
    }
    return vizinhos;
}

void GrafoMatrizInc::print() const {
    std::cout << "\n--- Imprimindo Matriz de Incidência ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo esta vazio.\n";
        return;
    }

    std::cout << "\t";
    for (int j = 0; j < qtd_arestas; ++j) {
        const auto& aresta = arestas_info.at(j);
        std::string label_aresta = "a" + std::to_string(j);
        std::cout << label_aresta << "\t";
    }
    std::cout << std::endl;

    for (int i = 0; i < qtd_vertices; ++i) {
        std::cout << rotulos.at(i) << "\t";
        if (qtd_arestas > 0) {
            for (int j = 0; j < qtd_arestas; ++j) {
                std::cout << matriz_inc.at(i).at(j) << "\t";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------------------------\n";
}