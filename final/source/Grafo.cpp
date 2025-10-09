#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/busca-largura.h"

Grafo::Grafo(int vertices) : qtd_vertices(vertices), qtd_arestas(0) {
    rotulos.resize(vertices);
    for (int i = 0; i < vertices; i++) {
        rotulos[i] = std::to_string(i);
    }
}

void Grafo::incrementar_qtd_arestas() {
    this->qtd_arestas++;
}

void Grafo::decrementar_qtd_arestas() {
    if (this->qtd_arestas > 0) {
        this->qtd_arestas--;
    }
}

bool Grafo::is_conexo() {
    if (qtd_vertices <= 1) {
        return true;
    }

    std::map<int, int> vertices_alcancados = busca_em_profundidade_grafo(*this, 0);

    return vertices_alcancados.size() == qtd_vertices;
}

bool Grafo::is_bipartido() {
    if (qtd_vertices <= 1) {
        return true;
    }

    std::vector<int> cores(qtd_vertices, 0);

    // Itera por todos os vértices para garantir que grafos desconexos sejam tratados
    for (int i = 0; i < qtd_vertices; ++i) {
        // Se o vértice 'i' ainda não foi visitado/colorido,
        // então inicia a verificação de bipartição para o componente ao qual 'i' pertence
        if (cores[i] == 0) {
            // Se a função auxiliar retornar 'false' para qualquer componente,
            // então o grafo inteiro não é bipartido
            if (!busca_largura_colorida_grafo(*this, i, cores)) {
                return false;
            }
        }
    }

    // Se todos os componentes foram verificados com sucesso, o grafo é bipartido
    return true;
}

void Grafo::carregar_de_arquivo(const std::string& filename) {
    std::ifstream arquivo(filename);
    if (!arquivo.is_open()) {
        std::cerr << "Erro: Nao foi possivel abrir o arquivo " << filename << std::endl;
        return;
    }

    // 1. Lê o número de vértices da primeira linha
    int num_vertices_arquivo;
    arquivo >> num_vertices_arquivo;
    if (arquivo.fail()) {
        std::cerr << "Erro ao ler o numero de vertices do arquivo." << std::endl;
        return;
    }
    
    // 2. Limpa o estado atual e reinicializa o grafo com o novo tamanho
    this->limpar();
    this->rotulos.resize(num_vertices_arquivo);
    for (int i = 0; i < num_vertices_arquivo; ++i) {
        this->inserir_vertice(); 
    }

    // 3. Mapa para traduzir rótulos do arquivo (string) para índices (int)
    std::map<std::string, int> mapa_rotulos;
    int proximo_indice = 0;

    std::string linha;
    std::getline(arquivo, linha); 

    // 4. Lê cada linha de aresta
    while (std::getline(arquivo, linha)) {
        if (linha.empty()) continue;

        std::stringstream ss(linha);
        std::string rotulo1_str, rotulo2_str;

        std::getline(ss, rotulo1_str, ',');
        std::getline(ss, rotulo2_str);

        int indice1, indice2;

        // Mapeia o primeiro rótulo para um índice
        if (mapa_rotulos.find(rotulo1_str) == mapa_rotulos.end()) {
            if (proximo_indice >= this->qtd_vertices) continue;
            indice1 = proximo_indice++;
            mapa_rotulos[rotulo1_str] = indice1;
            this->rotulos[indice1] = rotulo1_str;
        } else {
            indice1 = mapa_rotulos[rotulo1_str];
        }

        // Mapeia o segundo rótulo para um índice
        if (mapa_rotulos.find(rotulo2_str) == mapa_rotulos.end()) {
            if (proximo_indice >= this->qtd_vertices) continue;
            indice2 = proximo_indice++;
            mapa_rotulos[rotulo2_str] = indice2;
            this->rotulos[indice2] = rotulo2_str;
        } else {
            indice2 = mapa_rotulos[rotulo2_str];
        }
        
        this->inserir_aresta(indice1, indice2);
    }
    
    arquivo.close();
}

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


    // Adiciona todos os vértices
    for (int i = 0; i < qtd_vertices; i++) {
        file << "    " << i << " [label=\"" << rotulos.at(i) << "\"];\n";
    }

    file << "\n";

    // Adiciona as arestas
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

void gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}