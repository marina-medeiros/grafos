#include "../headers/arvore_busca.h"
#include <fstream>
#include <iostream>

ArvoreBusca::ArvoreBusca(int vertices) : qtd_vertices(vertices) {
    predecessores.assign(vertices, -1);
}

ArvoreBusca::~ArvoreBusca() {}

void ArvoreBusca::set_predecessor(int vertice, int predecessor) {
    if (vertice >= 0 && vertice < qtd_vertices) {
        predecessores[vertice] = predecessor;
    }
}

int ArvoreBusca::get_predecessor(int vertice) const {
    // Verifica se o índice do vértice é válido
    if (vertice >= 0 && vertice < qtd_vertices) {
        return predecessores[vertice];
    }
    // Retorna -1 se o vértice for inválido ou não tiver predecessor (como a raiz)
    return -1; 
}





void ArvoreBusca::adicionar_aresta_retorno(int u, int v) {
    arestas_retorno.push_back({u, v});
}

void ArvoreBusca::adicionar_aresta_avanco(int u, int v) {
    arestas_avanco.push_back({u, v});
}

void ArvoreBusca::adicionar_aresta_cruzamento(int u, int v) {
    arestas_cruzamento.push_back({u, v});
}


void ArvoreBusca::exportar_arestas_nao_arvore(std::ofstream& file) const {
    
    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 
             << " [style=dashed, color=red, constraint=false];\n";
    }

    for (const auto& aresta : arestas_avanco) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 
             << " [style=dashed, color=darkgreen, constraint=false];\n";
    }

    for (const auto& aresta : arestas_cruzamento) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 
             << " [style=dashed, color=darkgoldenrod, constraint=false];\n";
    }
}

void ArvoreBusca::gerar_imagem(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}