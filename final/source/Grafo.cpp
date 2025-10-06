#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

#include "../headers/Grafo.h"
#include "../headers/busca-profundidade.h"
#include "../headers/busca-largura.h"

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

    // Se todos os componentes foram verificados com sucesso, o grafo é bipartido.
    return true;
}

void Grafo::exportar_para_dot(const std::string& filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        return;
    }

    file << "graph G {\n";

    // Adiciona todos os vértices
    for (int i = 0; i < qtd_vertices; i++) {
        file << "  " << i+1 << ";\n";
    }

    // Adiciona as arestas
    for (int i = 0; i < qtd_vertices; i++) {
        for (int j : get_vizinhos(i)) {
            if (j > i) {
                file << "  " << i+1 << " -- " << j+1 << ";\n"; 
            }
        }
    }

    file << "}\n";
    file.close();
}

void Grafo::gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}