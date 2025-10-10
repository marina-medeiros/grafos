#include "../headers/DigrafoListaAdj.h"
#include <iostream>


/**
 * Construtor da classe DigrafoListaAdj, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *  vertices - Número inicial de vértices no digrafo.
 * Retorno: 
 *  Nenhum.
 */
DigrafoListaAdj::DigrafoListaAdj(int vertices) : Grafo(vertices)  {
    for (int i = 0; i < vertices; ++i) {
        lista_adj[i] = std::list<int>();
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
void DigrafoListaAdj::limpar() {
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
void DigrafoListaAdj::inserir_vertice(const std::string& rotulo) {
    lista_adj[qtd_vertices] = std::list<int>();

    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }
    
    qtd_vertices++;
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
void DigrafoListaAdj::remover_vertice(int u) {
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
 * Insere uma aresta direcionada do vértice u para o vértice v com um peso opcional.
 * Se a aresta já existir, a função não faz nada.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 *  peso - Peso opcional da aresta (padrão é 1).
 * Retorno:
 *  Nenhum.
 */
void DigrafoListaAdj::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;
    if (!existe_aresta(u, v)) {
        lista_adj[u].push_back(v);
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
void DigrafoListaAdj::remover_aresta(int u, int v) {
    if (u < 0 || u >= get_qtd_vertices() || v < 0 || v >= get_qtd_vertices()) {
        std::cerr << "Erro: Vértice inválido para remover aresta.\n";
        return;
    }

    if (existe_aresta(u, v)) {
        lista_adj[u].remove(v);

        decrementar_qtd_arestas();
    }
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
bool DigrafoListaAdj::existe_aresta(int u, int v) const {
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
std::list<int> DigrafoListaAdj::get_vizinhos(int v) const {
    auto it = lista_adj.find(v);
    if (it != lista_adj.end()) {
        return it->second;
    }
    return std::list<int>();
}

/**
 * Imprime a lista de adjacência do digrafo no console.
 * Mostra cada vértice seguido por seus vizinhos.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
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

/**
 * Retorna o grau de saída do vértice v (número de arestas saindo de v).
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo grau de saída será retornado.
 * Retorno:
 *  O grau de saída do vértice v.
 */
int DigrafoListaAdj::get_grau_saida(int v) const {
    if (v < 0 || v >= get_qtd_vertices()) return 0;
    return get_vizinhos(v).size();
}

/**
 * Retorna o grau de entrada do vértice v (número de arestas entrando em v).
 * 
 * Parâmetros:
 *  v - Índice do vértice cujo grau de entrada será retornado.
 * Retorno:
 *  O grau de entrada do vértice v.
 */
int DigrafoListaAdj::get_grau_entrada(int v) const {
    if (v < 0 || v >= get_qtd_vertices()) return 0;

    int grau_entrada = 0;
    for (int i = 0; i < get_qtd_vertices(); ++i) {
        for (int vizinho : get_vizinhos(i)) {
            if (vizinho == v) {
                grau_entrada++;
            }
        }
    }
    return grau_entrada;
}

/**
 * Gera o grafo subjacente não direcionado a partir do digrafo atual.
 * O grafo subjacente contém todas as arestas do digrafo, mas sem direção
 * (ou seja, cada aresta direcionada u -> v se torna uma aresta não direcionada {u, v}).
 * Utiliza a classe GrafoListaAdj para representar o grafo subjacente.
 * 
 * Parâmetros:
 *   digrafo - Referência ao digrafo do qual o grafo subjacente será gerado.
 * Retorno:
 *   Um objeto GrafoListaAdj representando o grafo subjacente.
 */
GrafoListaAdj DigrafoListaAdj::obter_grafo_subjacente(const DigrafoListaAdj& digrafo) {
    int qtd_vertices = digrafo.get_qtd_vertices();

    GrafoListaAdj grafo_subjacente(qtd_vertices);
    grafo_subjacente.set_rotulos(digrafo.get_rotulos());

    std::cout << "\n--- Gerando o Grafo Subjacente ---\n";

    for (int u = 0; u < qtd_vertices; ++u) {
        for (int v : digrafo.get_vizinhos(u)) {
            grafo_subjacente.inserir_aresta(u, v);
        }
    }
    std::cout << "Grafo subjacente gerado com sucesso.\n";
    return grafo_subjacente;
}