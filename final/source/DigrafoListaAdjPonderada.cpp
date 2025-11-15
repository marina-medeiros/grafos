#include "../headers/DigrafoListaAdjPonderada.h"
#include <iostream>
#include <algorithm> 

/**
 * Construtor da classe DigrafoListaAdjPonderada, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *  vertices - Número inicial de vértices no digrafo.
 * Retorno: 
 *  Nenhum.
 */
DigrafoListaAdjPonderada::DigrafoListaAdjPonderada(int vertices) : Grafo(vertices) {
    for (int i = 0; i < vertices; ++i) {
        lista_adj[i] = std::list<std::pair<int, int>>();
    }
}

/**
 * Limpa o digrafo, removendo todos os vértices e arestas.
 * Reseta a quantidade de vértices e arestas para zero.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::limpar() {
    this->lista_adj.clear();
    this->rotulos.clear();
    this->qtd_vertices = 0;
    this->qtd_arestas = 0;
}

/**
 * Insere um novo vértice no digrafo com um rótulo opcional.
 * Se nenhum rótulo for fornecido, o índice do vértice será usado como rótulo.
 * 
 * Parâmetros:
 *  rotulo - Rótulo opcional para o novo vértice.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::inserir_vertice(const std::string& rotulo) {
    lista_adj[qtd_vertices] = std::list<std::pair<int, int>>();
    
    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }

    qtd_vertices++;
}

/**
 * Insere uma aresta direcionada do vértice u para o vértice v com um peso.
 * Se a aresta já existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 *  peso - Peso da aresta.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;
    
    if (!existe_aresta(u, v)) {
        lista_adj[u].push_back({v, peso});
        qtd_arestas++;
    }
}

/**
 * Remove uma aresta direcionada do vértice u para o vértice v.
 * Se a aresta não existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::remover_aresta(int u, int v) {
    if (u < 0 || u >= qtd_vertices) return;

    auto it = lista_adj.find(u);
    if (it != lista_adj.end()) {
        for (auto list_it = it->second.begin(); list_it != it->second.end(); ++list_it) {
            if (list_it->first == v) {
                it->second.erase(list_it);
                qtd_arestas--;
                break;
            }
        }
    }
}

/**
 * Remove um vértice do digrafo, eliminando todas as arestas associadas a ele.
 * Reindexa os vértices restantes para manter a consistência dos índices.
 * 
 * Parâmetros:
 *  u - Índice do vértice a ser removido.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::remover_vertice(int u) {
    if (u < 0 || u >= qtd_vertices) return;

    if (lista_adj.count(u)) {
        qtd_arestas -= lista_adj[u].size();
        lista_adj.erase(u); 
    }

    std::map<int, std::list<std::pair<int, int>>> nova_lista_adj;
    
    for (auto const& [vertice_atual, lista_vizinhos] : lista_adj) {
        
        int novo_indice_vertice = (vertice_atual > u) ? vertice_atual - 1 : vertice_atual;
        
        std::list<std::pair<int, int>> nova_lista_vizinhos;
        
        for (const auto& par : lista_vizinhos) {
            int vizinho_atual = par.first;
            int peso = par.second;
            
            if (vizinho_atual == u) {
                qtd_arestas--;
                continue;
            }
            
            int novo_indice_vizinho = (vizinho_atual > u) ? vizinho_atual - 1 : vizinho_atual;
            
            nova_lista_vizinhos.push_back({novo_indice_vizinho, peso});
        }
        
        nova_lista_adj[novo_indice_vertice] = nova_lista_vizinhos;
    }

    lista_adj = nova_lista_adj;
    
    rotulos.erase(rotulos.begin() + u);
    qtd_vertices--;
}


/**
 * Verifica se existe uma aresta direcionada do vértice u para o vértice v.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  true se a aresta existir, false caso contrário.
 */
bool DigrafoListaAdjPonderada::existe_aresta(int u, int v) const {
    auto it = lista_adj.find(u);
    if (it == lista_adj.end()) return false;

    for(const auto& par : it->second) {
        if (par.first == v) {
            return true;
        }
    }
    return false;
}

/**
 * Retorna o peso da aresta direcionada (u, v).
 * Se a aresta não existir ou os vértices forem inválidos, retorna 0.
 *
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  O peso (int) da aresta, ou 0 se não existir.
 */int DigrafoListaAdjPonderada::get_peso(int u, int v) const {
    auto it = lista_adj.find(u);
    if (it == lista_adj.end()) return 0; // Vértice u não encontrado

    for(const auto& par : it->second) {
        if (par.first == v) {
            return par.second; // Retorna o peso
        }
    }
    return 0; // Aresta não encontrada
}

/**
 * Retorna a lista de arestas saindo do vértice u.
 * A lista contém pares (vizinho, peso).
 *
 * Parâmetros:
 *  u - Índice do vértice de origem.
 * Retorno:
 *  Uma referência constante para a lista de pares (vizinho, peso).
 */
const std::list<std::pair<int, int>>& DigrafoListaAdjPonderada::get_arestas_saindo(int u) const {
    return lista_adj.at(u);
}

/**
 * Retorna a lista de vizinhos (vértices adjacentes) do vértice v.
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo vizinhos serão retornados.
 * Retorno:
 *  Uma lista de inteiros representando os índices dos vértices vizinhos.
 */
std::list<int> DigrafoListaAdjPonderada::get_vizinhos(int v) const { 
    std::list<int> vizinhos_idx;
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        for(const auto& par : it->second) {
            vizinhos_idx.push_back(par.first);
        }
    }
    return vizinhos_idx;
}

/**
 * Retorna o grau de saída do vértice v (número de arestas saindo de v).
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo grau de saída será retornado.
 * Retorno:
 *  O grau de saída do vértice v.
 */
int DigrafoListaAdjPonderada::get_grau_saida(int v) const {
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        return it->second.size();
    }
    return 0;
}

/**
 * Imprime a lista de adjacência do digrafo no console.
 * Mostra cada vértice e seu peso seguido por seus vizinhos.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdjPonderada::print() const {
    std::cout << "\n--- Imprimindo Lista de Adjacência PONDERADA ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo está vazio.\n";
        return;
    }

    for (int i = 0; i < qtd_vertices; ++i) {
        // Usa at(i) para garantir que o vértice exista
        std::cout << rotulos.at(i) << " (" << i << "): ";
        const auto& vizinhos = lista_adj.at(i);
        if (vizinhos.empty()) {
            std::cout << "-> (nenhum)";
        } else {
            for (const auto& par : vizinhos) {
                // par.first é o vizinho, par.second é o peso
                std::cout << "-> " << rotulos.at(par.first) 
                          << " (" << par.first << ", peso: " << par.second << ") ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------\n";
}