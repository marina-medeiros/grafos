#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

#include "../headers/DigrafoMatrizInc.h"

/**
 * Construtor da classe DigrafoMatrizInc, inicializando o grafo com um número específico de vértices.
 * Parâmetros:
 *  vertices - Número inicial de vértices no digrafo.
 * Retorno: 
 *  Nenhum.
 */
DigrafoMatrizInc::DigrafoMatrizInc(int vertices) : Grafo(vertices) {
    matriz_inc.resize(vertices);
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
void DigrafoMatrizInc::limpar() {
    this->matriz_inc.clear();
    this->arestas_info.clear();
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
void DigrafoMatrizInc::inserir_vertice(const std::string& rotulo) {
    if (rotulo.empty()) {
        rotulos.push_back(std::to_string(qtd_vertices));
    } else {
        rotulos.push_back(rotulo);
    }

    matriz_inc.push_back(std::vector<int>(qtd_arestas, 0));
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
void DigrafoMatrizInc::remover_vertice(int u) {
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

/**
 * Insere uma aresta direcionada do vértice u para o vértice v com o peso especificado.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 *  peso - Peso da aresta a ser inserida (não usado na matriz de incidência).
 * Retorno: 
 *  Nenhum.
 */
void DigrafoMatrizInc::inserir_aresta(int u, int v, int peso) {
    if (u < 0 || u >= qtd_vertices || v < 0 || v >= qtd_vertices) return;

    if (existe_aresta(u, v)) return;

    for (int i = 0; i < qtd_vertices; ++i) {
        matriz_inc[i].push_back(0);
    }

    int nova_aresta_idx = qtd_arestas;
    matriz_inc[u][nova_aresta_idx] = -1;
    matriz_inc[v][nova_aresta_idx] = 1;

    arestas_info.push_back({u, v});
    qtd_arestas++;
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
void DigrafoMatrizInc::remover_aresta(int u, int v) {
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

/**
 * Verifica se existe uma aresta direcionada do vértice u para o vértice v.
 * 
 * Parâmetros:
 *  u - Índice do vértice de origem.
 *  v - Índice do vértice de destino.
 * Retorno:
 *  true se a aresta existir, false caso contrário.
 */
bool DigrafoMatrizInc::existe_aresta(int u, int v) const {
    for (int j = 0; j < qtd_arestas; ++j) {
        if (matriz_inc[u][j] == 1 && matriz_inc[v][j] == 1) {
            return true;
        }
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
std::list<int> DigrafoMatrizInc::get_vizinhos(int v) const {
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

/**
 * Imprime a matriz de incidência do digrafo no console.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizInc::print() const {
    std::cout << "\n--- Imprimindo Matriz de Incidência ---\n";
    if (qtd_vertices == 0) {
        std::cout << "O grafo está vazio.\n";
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

/**
 * Exporta o digrafo para um arquivo no formato DOT, adequado para visualização com Graphviz.
 * 
 * Parâmetros:
 *  filename - Nome do arquivo de saída.
 *  eh_digrafo - Indica se o grafo é direcionado (true) ou não (false).
 * Retorno:
 *  Nenhum.
 */
void DigrafoMatrizInc::exportar_para_dot(const std::string& filename, bool eh_digrafo) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        return;
    }

    if (eh_digrafo) {
        file << "digraph G {\n";
        file << "  rankdir=TB;\n"; 
        file << "  overlap=false;\n";
    } else {
        file << "graph G {\n";
    }

    for (int i = 0; i < qtd_vertices; i++) {
        file << "    " << i << " [label=\"" << rotulos.at(i) << "\"];\n";
    }

    file << "\n";

    for (int aresta_idx = 0; aresta_idx < get_qtd_arestas(); ++aresta_idx) {
        int origem = -1;
        int destino = -1;

        for (int vertice_idx = 0; vertice_idx < get_qtd_vertices(); ++vertice_idx) {
            
            if (matriz_inc[vertice_idx][aresta_idx] == 1) {
                origem = vertice_idx;
            } else if (matriz_inc[vertice_idx][aresta_idx] == -1) {
                destino = vertice_idx;
            }
        }

        if (origem != -1 && destino != -1) {
            file << "  " << origem << " -> " << destino << ";\n";
        }
    }

    file << "}\n";
    file.close();
}
