#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/busca-largura.h"

/**
 * Construtor da classe Grafo, inicializando o grafo com um número específico de vértices.
 * 
 * Parâmetros:
 *   vertices - Número inicial de vértices no grafo.
 * Retorno: 
 *   Nenhum.
 */
Grafo::Grafo(int vertices) : qtd_vertices(vertices), qtd_arestas(0) {
    rotulos.resize(vertices);
    for (int i = 0; i < vertices; i++) {
        rotulos[i] = std::to_string(i);
    }
}

/**
 * Incrementa a contagem de arestas do grafo.
 * 
 * Parâmetros:
 *   Nenhum.
 * Retorno:
 *   Nenhum.
 */
void Grafo::incrementar_qtd_arestas() {
    this->qtd_arestas++;
}

/**
 * Decrementa a contagem de arestas do grafo, garantindo que não fique negativa.
 * 
 * Parâmetros:
 *   Nenhum.
 * Retorno:
 *   Nenhum.
 */
void Grafo::decrementar_qtd_arestas() {
    if (this->qtd_arestas > 0) {
        this->qtd_arestas--;
    }
}

/**
 * Verifica se o grafo é conexo utilizando uma busca em profundidade (DFS).
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  true se o grafo for conexo, false caso contrário.
 */
bool Grafo::is_conexo() {
    if (qtd_vertices <= 1) {
        return true;
    }

    std::map<int, int> vertices_alcancados = busca_em_profundidade_grafo(*this, 0);

    return vertices_alcancados.size() == qtd_vertices;
}

/**
 * Verifica se o grafo é bipartido utilizando uma busca em largura (BFS) colorida.
 * 
 * Parâmetros:
 *  Nenhum.
 * Retorno:
 *  true se o grafo for bipartido, false caso contrário.
 */
bool Grafo::is_bipartido() {
    if (qtd_vertices <= 1) {
        return true;
    }

    std::vector<int> cores(qtd_vertices, 0);

    for (int i = 0; i < qtd_vertices; ++i) {
        if (cores[i] == 0) {
            if (!busca_largura_colorida_grafo(*this, i, cores)) {
                return false;
            }
        }
    }

    return true;
}

void Grafo::determinar_articulacoes_blocos_lowpt() {
    std::vector<int> disc(qtd_vertices, -1);
    std::vector<int> low(qtd_vertices, -1);
    std::vector<int> parent(qtd_vertices, -1);
    std::set<int> articulacoes;
    std::vector<std::set<int>> blocos;
    std::stack<std::pair<int, int>> pilha;
    
    int tempo = 0;

    for (int i = 0; i < qtd_vertices; ++i) {
        if (disc[i] == -1) {
            busca_articulacoes_dfs_recursiva(*this, i, disc, low, parent, pilha, articulacoes, blocos, tempo);

            if (!pilha.empty()) {
                std::set<int> aux;
                while (!pilha.empty()) {
                    std::pair<int, int> edge = pilha.top();
                    pilha.pop();
                    aux.insert(edge.first);
                    aux.insert(edge.second);
                }
                blocos.push_back(aux);
            }
        }
    }

    if (articulacoes.empty()) {
        std::cout << "O grafo não possui pontos de articulção." << std::endl;
    } else {
        std::cout << "\nPontos de Articulação encontrados:\n";
        for (int v_idx : articulacoes) {
            std::cout << "  - Vértice " << this->get_rotulos()[v_idx] << " (índice " << v_idx << ")\n";
        }
    }
    
    if (blocos.empty()) {
        std::cout << "\nO grafo não possui blocos." << std::endl;
    } else {
        std::cout << "\nForam encontrados " << blocos.size() << " blocos:\n";
        int i = 1;
        for (const auto& bloco : blocos) {
            std::cout << "  - Bloco " << i++ << ": { ";
            for (int v_idx : bloco) {
                std::cout << this->get_rotulos()[v_idx] << " ";
            }
            std::cout << "}\n";
        }
    }
}

/**
 * Carrega um grafo a partir de um arquivo de texto.
 * O arquivo deve ter o seguinte formato:
 *   - A primeira linha contém o número de vértices.
 *   - As linhas subsequentes contêm pares de rótulos de vértices separados por vírgula, representando arestas.
 * 
 * Parâmetros:
 *   filename - Nome do arquivo a ser carregado.
 * Retorno:
 *   Nenhum.    
 */
void Grafo::carregar_de_arquivo(const std::string& filename) {
    std::ifstream arquivo(filename);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << filename << std::endl;
        return;
    }

    int num_vertices_arquivo;
    arquivo >> num_vertices_arquivo;
    if (arquivo.fail()) {
        std::cerr << "Erro ao ler o numero de vertices do arquivo." << std::endl;
        return;
    }
    
    this->limpar();
    for (int i = 0; i < num_vertices_arquivo; ++i) {
        this->inserir_vertice(); 
    }

    std::map<std::string, int> mapa_rotulos;
    int proximo_indice = 0;

    std::string linha;
    std::getline(arquivo, linha); 

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string rotulo1_str, rotulo2_str, rotulo3_str;

        std::getline(ss, rotulo1_str, ',');
        std::getline(ss, rotulo2_str, ',');
        std::getline(ss, rotulo3_str);

        // if (mapa_rotulos.find(rotulo1_str) == mapa_rotulos.end()) {
        //     if (proximo_indice >= this->qtd_vertices) continue;
        //     indice1 = proximo_indice++;
        //     mapa_rotulos[rotulo1_str] = indice1;
        //     this->rotulos[indice1] = rotulo1_str;
        // } else {
        //     indice1 = mapa_rotulos[rotulo1_str];
        // }

        // if (mapa_rotulos.find(rotulo2_str) == mapa_rotulos.end()) {
        //     if (proximo_indice >= this->qtd_vertices) continue;
        //     indice2 = proximo_indice++;
        //     mapa_rotulos[rotulo2_str] = indice2;
        //     this->rotulos[indice2] = rotulo2_str;
        // } else {
        //     indice2 = mapa_rotulos[rotulo2_str];
        // }

        int indice1 = std::stoi(rotulo1_str);
        int indice2 = std::stoi(rotulo2_str);
        if (indice1 < 0 || indice1 >= this->qtd_vertices || indice2 < 0 || indice2 >= this->qtd_vertices) {
            std::cerr << "Aviso: índice fora do intervalo na linha: " << linha << std::endl;
            continue;
        }

        if(!rotulo3_str.empty()){
            this->inserir_aresta(indice1, indice2, std::stoi(rotulo3_str));
        }else{
            this->inserir_aresta(indice1, indice2);
        }
    }
    
    arquivo.close();
}

/**
 * Exporta o grafo para um arquivo no formato DOT, adequado para visualização com Graphviz.
 * 
 * Parâmetros:
 *  filename - Nome do arquivo de saída.
 *  eh_digrafo - Indica se o grafo é direcionado (true) ou não (false).
 * Retorno:
 *  Nenhum.
 */
void Grafo::exportar_para_dot(const std::string& filename, bool eh_digrafo) const {
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

    for (int i = 0; i < qtd_vertices; i++) {
        for (int j : get_vizinhos(i)) {
            if (eh_digrafo) {
                file << "  " << i << " -> " << j << ";\n"; 
            } else if (j > i) {
                file << "  " << i << " -- " << j << ";\n"; 
            }
        }
    }

    file << "}\n";
    file.close();
}

/**
 * Gera uma imagem PNG a partir de um arquivo DOT usando o Graphviz.
 * 
 * Parâmetros:
 *   dotfile - Nome do arquivo DOT de entrada.
 *   imgfile - Nome do arquivo de saída para a imagem PNG.
 * Retorno:
 *   Nenhum.
 */
void gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}