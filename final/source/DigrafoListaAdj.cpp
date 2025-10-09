#include "../headers/DigrafoListaAdj.h"
#include <iostream>



DigrafoListaAdj::DigrafoListaAdj(int vertices) : Grafo(vertices)  {
    for (int i = 0; i < vertices; ++i) {
        lista_adj[i] = std::list<int>();
    }
}


void DigrafoListaAdj::limpar() {
    this->lista_adj.clear();
    this->rotulos.clear();
    this->qtd_vertices = 0;
    this->qtd_arestas = 0;
}

void DigrafoListaAdj::inserir_vertice(const std::string& rotulo) {
    lista_adj[qtd_vertices] = std::list<int>();

    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }
    
    qtd_vertices++;
}

void DigrafoListaAdj::remover_vertice(int u) {
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
    rotulos.erase(rotulos.begin() + u);

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

void DigrafoListaAdj::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;
    if (!existe_aresta(u, v)) {
        lista_adj[u].push_back(v);
        qtd_arestas++;
    }
}

/**
 * @brief Sobrescrita da remoção de aresta para comportamento DIRECIONADO.
 */
void DigrafoListaAdj::remover_aresta(int u, int v) {
    if (u < 0 || u >= get_qtd_vertices() || v < 0 || v >= get_qtd_vertices()) {
        std::cerr << "Erro: Vértice inválido para remover aresta.\n";
        return;
    }

    if (existe_aresta(u, v)) {
        // A MUDANÇA PRINCIPAL ESTÁ AQUI:
        // Remove 'v' apenas da lista de vizinhos de 'u'.
        lista_adj[u].remove(v);

        // Decrementa a quantidade de arestas
        decrementar_qtd_arestas();
    }
}


bool DigrafoListaAdj::existe_aresta(int u, int v) const {
    auto it = lista_adj.find(u);
    if (it == lista_adj.end()) return false;
    const std::list<int>& vizinhos = it->second;
    return (std::find(vizinhos.begin(), vizinhos.end(), v) != vizinhos.end());
}

std::list<int> DigrafoListaAdj::get_vizinhos(int v) const {
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        return it->second;
    }
    return std::list<int>();
}

void DigrafoListaAdj::print() const {
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


int DigrafoListaAdj::get_grau_saida(int v) const {
    // Para uma lista de adjacências, isso é simplesmente o tamanho da lista de vizinhos.
    if (v < 0 || v >= get_qtd_vertices()) return 0;
    return get_vizinhos(v).size();
}


int DigrafoListaAdj::get_grau_entrada(int v) const {
    if (v < 0 || v >= get_qtd_vertices()) return 0;

    int grau_entrada = 0;
    // Precisamos percorrer todo o grafo para ver quem aponta para 'v'
    for (int i = 0; i < get_qtd_vertices(); ++i) {
        for (int vizinho : get_vizinhos(i)) {
            if (vizinho == v) {
                grau_entrada++;
            }
        }
    }
    return grau_entrada;
}