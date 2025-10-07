#include "../headers/arvore_dfs.h"
#include <fstream>

ArvoreDFS::ArvoreDFS(int vertices) : ArvoreBusca(vertices) {
    tempos_entrada.assign(vertices, 0);
    tempos_saida.assign(vertices, 0);
}

void ArvoreDFS::set_tempos(int vertice, int entrada, int saida) {
    if (vertice >= 0 && vertice < qtd_vertices) {
        tempos_entrada[vertice] = entrada;
        tempos_saida[vertice] = saida;
    }
}

void ArvoreDFS::exportar_para_dot(ArvoreDFS arvore, std::string& filename) const {
    std::ofstream file(filename);
    file << "digraph ArvoreDFS {\n";
    file << "  rankdir=TB;\n";

    for (int i = 0; i < qtd_vertices; ++i) {
        file << "  " << i + 1 << " [label=\"" << i + 1 << "\\n" 
             << "PE:" << tempos_entrada[i] << "/PS:" << tempos_saida[i] << "\"];\n";
    }

    for (int i = 0; i < qtd_vertices; ++i) {
        if (predecessores[i] != -1) {
            file << "  " << predecessores[i] + 1 << " -> " << i + 1 << ";\n";
        }
    }

    exportar_arestas_nao_arvore(file);

    file << "}\n";
    file.close();
}