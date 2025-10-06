#include <iostream>
#include <queue>

#include "../headers/GrafoListaAdj.h"

GrafoListaAdj::GrafoListaAdj(int vertices) : Grafo(vertices) {
    for (int i = 0; i < vertices; ++i) {
        lista_adj[i] = std::list<int>();
    }
}

void GrafoListaAdj::inserir_vertice() {
    int novo_vertice_idx = qtd_vertices;
    lista_adj[novo_vertice_idx] = std::list<int>();
    qtd_vertices++;
}

void GrafoListaAdj::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    };

    // 1. Remove todas as arestas conectadas a 'u'
    std::list<int> vizinhos_a_remover = lista_adj[u];
    for (int v : vizinhos_a_remover) {
        remover_aresta(u, v);
    }

    // 2. Remove o vértice 'u' do mapa
    lista_adj.erase(u);

    // 3. Reindexa os vértices e arestas com índice > u
    std::map<int, std::list<int>> nova_lista_adj;
    for (auto const& [vertice, vizinhos] : lista_adj) {
        int novo_vertice_idx = (vertice > u) ? vertice - 1 : vertice;
        
        std::list<int> novos_vizinhos;
        for (int vizinho : vizinhos) {
            novos_vizinhos.push_back((vizinho > u) ? vizinho - 1 : vizinho);
        }
        nova_lista_adj[novo_vertice_idx] = novos_vizinhos;
    }
    lista_adj = nova_lista_adj;
    
    // 4. Atualiza a contagem de vértices
    qtd_vertices--;
}

void GrafoListaAdj::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;
    if (!existe_aresta(u, v)) {
        lista_adj[u].push_back(v);
        lista_adj[v].push_back(u);
        qtd_arestas++;
    }
}

void GrafoListaAdj::remover_aresta(int u, int v) {
    if (existe_aresta(u, v)) {
        lista_adj[u].remove(v);
        lista_adj[v].remove(u);
        qtd_arestas--;
    }
}

bool GrafoListaAdj::existe_aresta(int u, int v) const {
    auto it = lista_adj.find(u);
    if (it == lista_adj.end()) return false;
    const std::list<int>& vizinhos = it->second;
    return (std::find(vizinhos.begin(), vizinhos.end(), v) != vizinhos.end());
}

std::list<int> GrafoListaAdj::get_vizinhos(int v) const {
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        return it->second;
    }
    return std::list<int>();
}