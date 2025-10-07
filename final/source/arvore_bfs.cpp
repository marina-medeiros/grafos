#include "../headers/arvore_bfs.h"
#include <fstream>
#include <algorithm>
#include <iostream>

ArvoreBFS::ArvoreBFS(int vertices) : ArvoreBusca(vertices) {
    niveis.assign(vertices, 0);
}


void ArvoreBFS::exportar_para_dot(std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph ArvoreBFS {\n";
    file << "  rankdir=TB; // Garante o layout de Cima para Baixo (Top to Bottom)\n";
    file << "  node [shape=circle];\n\n";
    
    // 1. Desenha todos os nós, adicionando o Nível como rótulo
    
    for (int i = 0; i < qtd_vertices; ++i) {
        // O rótulo do nó mostrará seu número e seu nível na árvore BFS
        file << "  " << i + 1 << " [label=\"" << i + 1 << "\"];\n";
    }

    // 2. Desenha as arestas da árvore (sólidas, em preto)
    for (int i = 0; i < qtd_vertices; ++i) {
        if (predecessores[i] != -1) { // Se o vértice tem um pai
            file << "  " << predecessores[i] + 1 << " -- " << i + 1 << " [penwidth=2];\n";
        }
    }

    // 3. Chama a função da classe base para desenhar as outras arestas
    // (retorno, avanço, cruzamento) com seus estilos e cores definidos.
    exportar_arestas_nao_arvore(file);

    file << "}\n";
    file.close();
}
