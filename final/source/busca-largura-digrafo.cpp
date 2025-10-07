#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include "../headers/busca-largura-digrafo.h"

void gerar_imagem_bsfd(const std::string& dotfile, const std::string& imgfile){
    std::string cmd = "dot -Tpng " + dotfile + " -o " + imgfile;
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        std::cerr << "Erro ao executar Graphviz\n";
    } else {
        pclose(pipe);
    }
}

bool eh_ancestral(int u_descendente, int v_ancestral, const std::vector<int>& predecessor) {
    int p = u_descendente;
    while (p != -1) {
        if (p == v_ancestral) {
            return true;
        }
        p = predecessor[p];
    }
    return false;
}

void busca_largura_digrafo(Grafo grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::vector<int> nivel(grafo.get_qtd_vertices(), 0);
    
    std::vector<std::pair<int, int>> arestas_arvore;
    std::vector<std::pair<int, int>> arestas_retorno;
    std::vector<std::pair<int, int>> arestas_avanco;
    std::vector<std::pair<int, int>> arestas_cruzamento;
    
    visitado[verticeInicial] = true;
    
    std::queue<int> fila;

    fila.push(verticeInicial); 

    std::map<int, std::list<int>> lista_adj = grafo.get_lista_adj();
    
    std::cout << "\n--- Iniciando Busca em Largura de um Digrafo a partir de " << verticeInicial + 1 << " ---\n";
    std::cout << "Ordem de visitação: ";

    while(!fila.empty()) { 
        int verticeAtual = fila.front();
        std::cout << verticeAtual + 1 << " ";
        fila.pop(); 
        
        for(int vizinho : lista_adj[verticeAtual]) { 
            if(!visitado[vizinho]) { 
                visitado[vizinho] = true; 
                predecessor[vizinho] = verticeAtual; 
                nivel[vizinho] = nivel[verticeAtual] + 1;
                arestas_arvore.push_back({verticeAtual, vizinho});
                fila.push(vizinho);  
            } else {
                if (eh_ancestral(verticeAtual, vizinho, predecessor)) {
                    arestas_retorno.push_back({verticeAtual, vizinho});
                } else if (eh_ancestral(vizinho, verticeAtual, predecessor)) {
                    arestas_avanco.push_back({verticeAtual, vizinho});
                } else {
                    arestas_cruzamento.push_back({verticeAtual, vizinho});
                }
            }
        }
        if(fila.empty()) {
            for(int i = 0; i < grafo.get_qtd_vertices(); i++) {
                if(!visitado[i]) {
                    fila.push(i);
                    visitado[i] = true;
                    break;
                }
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Lista de predecessores: ";
    for(int v = 0; v < grafo.get_qtd_vertices(); v++){
        std::cout << predecessor[v]+1 << " ";
    }
    std::cout << std::endl;
    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(int i = 0; i < grafo.get_qtd_vertices(); ++i) {
        if(visitado[i]) {
            std::cout << "| " << i+1 << "\t| "
                      << (predecessor[i] == -1 ? "Raiz" : std::to_string(predecessor[i] + 1)) << "\t  | "
                      <<  std::endl;
        }
    }
    std::cout << "---------------------\n";

    exportar_arvore_bfs_para_dot("arvore_bfs_dir.dot", grafo.get_qtd_vertices(), predecessor, arestas_retorno, arestas_avanco, arestas_cruzamento);
    gerar_imagem_bsfd("arvore_bfs_dir.dot", "arvore_bfs_dir.png");
}

// void exportar_arvore_bfs_para_dot(const std::string& filename, 
//                                     int qtd_vertices,
//                                     std::vector<int> predecessores,
//                                     const std::vector<std::pair<int, int>>& arestas_arvore,
//                                     const std::vector<std::pair<int, int>>& arestas_retorno,
//                                     const std::vector<std::pair<int, int>>& arestas_avanco,
//                                     const std::vector<std::pair<int, int>>& arestas_cruzamento) {
                                      
//     std::ofstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
//         return;
//     }

//     file << "digraph Arvore_BFS {\n";
//     file << "  rankdir=TB;\n"; // Organiza a árvore de cima para baixo
//     file << "  node [shape=circle];\n\n";

//     for (int i = 0; i < qtd_vertices; ++i) {
//         if (predecessores[i] != -1) { // Se o vértice não for uma raiz
//             file << "  " << predecessores[i] + 1 << " -> " << i + 1 << " [penwidth=2];\n";
//         }
//     }

//     for (const auto& aresta : arestas_retorno) {
//         file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkorchid, constraint=false];\n";
//     }

//     for (const auto& aresta : arestas_avanco) {
//         file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgreen, constraint=false];\n";
//     }

//     for (const auto& aresta : arestas_cruzamento) {
//         file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgoldenrod, constraint=false];\n";
//     }

//     file << "}\n";
//     file.close();

//     std::cout << "\nÁrvore BFS exportada para: " << filename << std::endl;
    
// }

void exportar_arvore_bfs_para_dot(const std::string& filename,
                                  int qtd_vertices,
                                  std::vector<int> predecessores,
                                  const std::vector<std::pair<int, int>>& arestas_retorno,
                                  const std::vector<std::pair<int, int>>& arestas_avanco,
                                  const std::vector<std::pair<int, int>>& arestas_cruzamento) {

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    file << "digraph Arvore_BFS {\n";
    file << "  rankdir=TB;\n"; // Organiza a árvore de cima para baixo
    file << "  node [shape=circle];\n\n";

    // 1. RECONSTRUIR A ÁRVORE PARA TER ACESSO AOS FILHOS DE CADA NÓ
    // A chave é o nó pai, o valor é um vetor com seus filhos.
    std::map<int, std::vector<int>> arvore_adj;
    for (int i = 0; i < qtd_vertices; ++i) {
        if (predecessores[i] != -1) {
            // Adiciona o vértice 'i' como filho de seu predecessor
            arvore_adj[predecessores[i]].push_back(i);
        }
    }
    
    // Desenha as arestas da árvore
    for (int i = 0; i < qtd_vertices; ++i) {
        if (predecessores[i] != -1) {
            file << "  " << predecessores[i] + 1 << " -> " << i + 1 << " [penwidth=2];\n";
        }
    }
    file << "\n";

    // Desenha as outras arestas (retorno, avanço, cruzamento)
    for (const auto& aresta : arestas_retorno) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkorchid, constraint=false];\n";
    }
    for (const auto& aresta : arestas_avanco) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgreen, constraint=false];\n";
    }
    for (const auto& aresta : arestas_cruzamento) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgoldenrod, constraint=false];\n";
    }
    file << "\n";

    // 2. ADICIONAR RESTRIÇÕES DE ORDENAMENTO COM ARESTAS INVISÍVEIS
    // Isso força os filhos a aparecerem na ordem em que foram adicionados.
    for (const auto& par : arvore_adj) {
        const std::vector<int>& filhos = par.second;
        if (filhos.size() > 1) {
            file << "  { rank=same; ";
            for (size_t i = 0; i < filhos.size() - 1; ++i) {
                file << filhos[i] + 1 << " -> " << filhos[i+1] + 1 << " [style=invis]; ";
            }
            file << "}\n";
        }
    }

    file << "}\n";
    file.close();

    std::cout << "\nÁrvore BFS exportada para: " << filename << std::endl;
}