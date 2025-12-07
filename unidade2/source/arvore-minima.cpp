#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../headers/arvore-minima.h"

/**
 * Construtor da classe ArvoreMinima, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *   vertices - Número inicial de vértices no grafo.
 * Retorno: 
 *   Nenhum.
 */
ArvoreMinima::ArvoreMinima(int vertices) : Grafo(vertices) {
    for (int i = 0; i < vertices; ++i) {
        lista_adj[i] = std::list<int>();
    }
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
void ArvoreMinima::limpar() {
    this->lista_adj.clear();
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
void ArvoreMinima::inserir_vertice(const std::string& rotulo) {
    lista_adj[qtd_vertices] = std::list<int>();
    
    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }
    
    qtd_vertices++;
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
void ArvoreMinima::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) {
        std::cout << "Índice de vértice inválido, remoção cancelada" << std::endl;
        return;
    };

    std::list<int> vizinhos_a_remover = lista_adj[u];
    for (int v : vizinhos_a_remover) {
        remover_aresta(u, v);
    }

    lista_adj.erase(u);
    rotulos.erase(rotulos.begin() + u);

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
void ArvoreMinima::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;
    if (!existe_aresta(u, v)) {
        lista_adj[u].push_back(v);
        lista_adj[v].push_back(u);
        qtd_arestas++;
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
void ArvoreMinima::remover_aresta(int u, int v) {
    if (existe_aresta(u, v)) {
        lista_adj[u].remove(v);
        lista_adj[v].remove(u);
        qtd_arestas--;
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
bool ArvoreMinima::existe_aresta(int u, int v) const {
    auto it = lista_adj.find(u);
    if (it == lista_adj.end()) return false;
    const std::list<int>& vizinhos = it->second;
    return (std::find(vizinhos.begin(), vizinhos.end(), v) != vizinhos.end());
}

/**
 * Retorna a lista de vizinhos (vértices adjacentes) do vértice v.
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo vizinhos serão retornados.
 * Retorno:
 *  Uma lista de inteiros representando os índices dos vértices vizinhos.
 */
std::list<int> ArvoreMinima::get_vizinhos(int v) const {
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        return it->second;
    }
    return std::list<int>();
}

/**
 * Imprime a lista de adjacência do grafo no console.
 * Mostra cada vértice seguido por seus vizinhos.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void ArvoreMinima::print() const {
    std::cout << "\n--- Imprimindo Lista de Adjacência ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo está vazio.\n";
        return;
    }

    for (int i = 0; i < qtd_vertices; ++i) {
        std::cout << rotulos.at(i) << " (" << i << "): ";

        const auto& vizinhos = lista_adj.at(i);
        if (vizinhos.empty()) {
            std::cout << "-> (nenhum)";
        } else {
            for (int vizinho_idx : vizinhos) {
                std::cout << "-> " << rotulos.at(vizinho_idx) << " (" << vizinho_idx << ") ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------\n";
}
