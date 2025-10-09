#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include "../headers/busca-largura-digrafo.h"
// #include "../headers/DigrafoListaAdj.h"
// #include "../headers/arvore_busca.h"


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

ArvoreBusca busca_largura_digrafo(DigrafoListaAdj& grafo, int verticeInicial){
    std::vector<bool> visitado(grafo.get_qtd_vertices(), false);
    std::vector<int> predecessor(grafo.get_qtd_vertices(), -1);
    std::vector<int> nivel(grafo.get_qtd_vertices(), 0);
    
    ArvoreBusca arvore(grafo.get_qtd_vertices());

    
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
                nivel[vizinho] = nivel[verticeAtual] + 1;

                arvore.set_nivel(vizinho, nivel[verticeAtual] + 1);
                arvore.adicionar_predecessor(vizinho, verticeAtual);
                arvore.adicionar_aresta_arvore(verticeAtual, vizinho);
                fila.push(vizinho);  
            } else {
                if (eh_ancestral(verticeAtual, vizinho, arvore.get_predecessores())) {
                    arvore.adicionar_aresta_retorno(verticeAtual, vizinho);
                } else if (eh_ancestral(vizinho, verticeAtual,  arvore.get_predecessores())) {
                    arvore.adicionar_aresta_avanco(verticeAtual, vizinho);
                } else {
                    arvore.adicionar_aresta_cruzamento(verticeAtual, vizinho);
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

   
    std::cout << std::endl;
    std::cout << "---------------------\n";
    std::cout << "Vértice | Predecessor \n";
    std::cout << "---------------------\n";
    for(int i = 0; i < grafo.get_qtd_vertices(); ++i) {
        if(visitado[i]) {
            std::cout << "| " << i+1 << "\t| "
                      << (arvore.get_predecessores()[i] == -1 ? "Raiz" : std::to_string(arvore.get_predecessores()[i] + 1)) << "\t  | "
                      <<  std::endl;
        }
    }
    std::cout << "---------------------\n";

    // exportar_arvore_bfs_para_dot("arvore_bfs_dirt.dot", grafo.get_qtd_vertices(), arvore);
    // gerar_imagem_bsfd("arvore_bfs_dirt.dot", "arvore_bfs_dirt.png");
    return arvore;
}

void exportar_arvore_bfs_para_dot(const std::string& filename,
                                  int qtd_vertices,
                                  ArvoreBusca& arvore) {

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
        if (arvore.get_predecessores()[i] != -1) {
            // Adiciona o vértice 'i' como filho de seu predecessor
            arvore_adj[arvore.get_predecessores()[i]].push_back(i);
        }
    }
    
    // Desenha as arestas da árvore
    for (int i = 0; i < qtd_vertices; ++i) {
        if (arvore.get_predecessores()[i] != -1) {
            file << "  " << arvore.get_predecessores()[i] + 1 << " -> " << i + 1 << " [penwidth=2];\n";
        }
    }
    file << "\n";

    // Desenha as outras arestas (retorno, avanço, cruzamento)
    for (const auto& aresta : arvore.get_arestas_retorno()) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkorchid, constraint=false];\n";
    }
    for (const auto& aresta : arvore.get_arestas_avanco()) {
        file << "  " << aresta.first + 1 << " -> " << aresta.second + 1 << " [style=dashed, color=darkgreen, constraint=false];\n";
    }
    for (const auto& aresta : arvore.get_arestas_cruzamento()) {
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