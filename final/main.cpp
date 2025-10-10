#include <iostream>
#include <string>

#include "headers/Grafo.h"

#include "headers/GrafoListaAdj.h"
#include "headers/GrafoMatrizAdj.h"
#include "headers/GrafoMatrizInc.h"

#include "headers/busca-largura.h"
#include "headers/busca-profundidade.h"
#include "headers/arvore-largura.h"

#include "headers/DigrafoListaAdj.h"
#include "headers/DigrafoMatrizAdj.h"
#include "headers/DigrafoMatrizInc.h"
#include "headers/busca-largura-digrafo.h"
#include "headers/busca-profundidade-digrafo.h"

void grafo(std::string txt);
void digrafo(std::string txt);

void analisar_e_gerar_imagem(Grafo& grafo, const std::string& nome_arquivo, const std::string& tipo_impl, bool eh_digrafo = false) {
    std::cout << "\n\nAnálise do " << nome_arquivo << std::endl;

    grafo.print();

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
        
    // Gera a imagem de visualização   
    std::string arq_dot =  nome_arquivo + "_" + tipo_impl + ".dot";
    std::string arq_png = nome_arquivo + "_" + tipo_impl + ".png";
    
    std::cout << "Gerando imagem em '" << arq_png << "'...\n";
    grafo.exportar_para_dot(arq_dot, eh_digrafo);
    gerar_imagem(arq_dot, arq_png);
}

void menu() {
    std::cout << "\nQual grafo ou digrafo deseja analisar?\n" << std::endl;
    std::cout << "1 | GRAFO_0\t5 | DIGRAFO_0" << std::endl;
    std::cout << "2 | GRAFO_1\t6 | DIGRAFO_1" << std::endl;
    std::cout << "3 | GRAFO_2\t7 | DIGRAFO_2" << std::endl;
    std::cout << "4 | GRAFO_3\t8 | DIGRAFO_3" << std::endl;
    std::cout << "\nDigite 'sair' ou 's' para terminar." << std::endl;
    std::cout << "Insira a opção escolhida: ";
}

int main(){

    const std::map<std::string, std::string> arquivos = {
        {"1", "GRAFO_0.txt"}, {"grafo_0", "GRAFO_0.txt"},
        {"2", "GRAFO_1.txt"}, {"grafo_1", "GRAFO_1.txt"},
        {"3", "GRAFO_2.txt"}, {"grafo_2", "GRAFO_2.txt"},
        {"4", "GRAFO_3.txt"}, {"grafo_3", "GRAFO_3.txt"},
        {"5", "DIGRAFO_0.txt"}, {"digrafo_0", "DIGRAFO_0.txt"},
        {"6", "DIGRAFO_1.txt"}, {"digrafo_1", "DIGRAFO_1.txt"},
        {"7", "DIGRAFO_2.txt"}, {"digrafo_2", "DIGRAFO_2.txt"},
        {"8", "DIGRAFO_3.txt"}, {"digrafo_3", "DIGRAFO_3.txt"}
    };

    while (true) {
        menu();
        std::string entrada;
        std::cin >> entrada;

        std::transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);

        if (entrada == "sair" || entrada == "s") {
            break;
        }

        auto it = arquivos.find(entrada);
        if (it == arquivos.end()) {
            std::cout << "\nOpção inválida. Tente novamente.\n" << std::endl;
            continue;
        }

        if (entrada == "1" || entrada == "2" || entrada == "3" || entrada == "4") {
            //se digrafo
            grafo(it->second);
        } else if (entrada == "5" || entrada == "6" || entrada == "7" || entrada == "8"){
            //se grafo
            digrafo(it->second);
        }
        
        std::cout << "\nAnálise concluída. Pressione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    return 0;

}

void grafo(std::string txt){

    std::string caminho_arquivo = "../dados/" + txt;
    std::string nome_grafo = txt.substr(0, txt.find(".txt"));

    // 1. Criação do Grafo a partir da Lista de Adjacências

    std::cout << "\n1 -IMPLEMENTAÇÃO " + nome_grafo + ": LISTA DE ADJACÊNCIA\n";
    GrafoListaAdj grafo_original_lista(0);
    grafo_original_lista.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(grafo_original_lista, nome_grafo, "lista_adj");

    // 2. Criação do Grafo a partir da Matriz de Adjacências

    std::cout << "\n2 - IMPLEMENTAÇÃO " + nome_grafo + ": MATRIZ DE ADJACÊNCIA\n";
    GrafoMatrizAdj grafo_original_matriz(0);
    grafo_original_matriz.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(grafo_original_matriz, nome_grafo, "matriz_adj");

    // 3. Criação do Grafo a partir da Matriz de Incidência

    std::cout << "\n3 - IMPLEMENTAÇÃO " + nome_grafo + ": MATRIZ DE Incidência\n";
    GrafoMatrizInc grafo_original_inc(0);
    grafo_original_inc.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(grafo_original_inc, nome_grafo, "matriz_inc");

    // 4.1 Converter de matriz de adjacência para lista de adjacência

    std::cout << "\n4.1 - CONVERSÃO: MATRIZ DE ADJACÊNCIA PARA LISTA DE ADJACÊNCIA\n";

    std::cout << "ANTES DA CONVERSÃO - " + nome_grafo + ":\n";
    grafo_original_matriz.print();

    GrafoListaAdj grafo_lista_convertido = grafo_original_matriz.converter_para_lista_adj();

    std::cout << "DEPOIS DA CONVERSÃO - " + nome_grafo + ":\n";
    grafo_lista_convertido.print();

    // 4.2 Converter de lista de adjacência para matriz de adjacência

    std::cout << "\n4.2 CONVERSÃO: LISTA DE ADJACÊNCIA PARA MATRIZ DE ADJACÊNCIA\n";

    std::cout << "ANTES DA CONVERSÃO - " + nome_grafo + ":\n";
    grafo_original_lista.print();

    GrafoMatrizAdj grafo_matriz_convertido = grafo_original_lista.converter_para_matriz_adj();

    std::cout << "DEPOIS DA CONVERSÃO - " + nome_grafo + ":\n";
    grafo_matriz_convertido.print();

    // 5 e 6. Cálculo do grau de cada vértice e função que determina se dois vértices são adjacentes

    std::cout << "\n5 e 6 - CÁLCULO DO GRAU DO VÉRTICE E DETERMINAÇÃO DE ADJACÊNCIA\n";
    std::cout << "Utilizando o " + nome_grafo + " como referência:\n";

    grafo_original_lista.print();

    int qtd_vertices = grafo_original_lista.get_qtd_vertices();
    if (qtd_vertices == 0) {
        std::cout << "O grafo está vazio. Não há vértices para testar.\n";
    } else {
        std::cout << "\nGrau de cada vértice:\n";
        for (int i = 0; i < qtd_vertices; ++i) {
            std::cout << "  - Vértice '" << grafo_original_lista.get_rotulos()[i] 
                    << "' (índice " << i << "): Grau " 
                    << grafo_original_lista.get_grau_vertice(i) << "\n";
        }

        std::cout << "\n--- Determinando se dois vértices são ou não adjacentes ---\n";

        for (int i = 0; i < qtd_vertices; ++i) {
            for (int j = i + 1; j < qtd_vertices; ++j) {
                
                std::string rotulo_i = grafo_original_lista.get_rotulos()[i];
                std::string rotulo_j = grafo_original_lista.get_rotulos()[j];

                std::cout << "  - Par ('" << rotulo_i << "', '" << rotulo_j << "'): ";

                if (grafo_original_lista.existe_aresta(i, j)) {
                    std::cout << "São adjacentes.\n";
                } else {
                    std::cout << "Não são adjacentes.\n";
                }
            }
        }
    }

    // 7 - Número total de vértices. -- já é mostrado ao analisar_e_gerar_imagem

    // 8 - Número total de arestas. -- já é mostrado ao analisar_e_gerar_imagem

    // 9 - Inclusão de um novo vértice usando Lista de Adjacências e Matriz de Adjacências.

    std::cout << "\n9.1 - INCLUSÃO DE UM NOVO VÉRTICE USANDO LISTA DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o " + nome_grafo + " como referência:\n";

    grafo_original_lista.print();

    GrafoListaAdj grafo_com_inclusao_lista = grafo_original_lista;

    int qtd_inicial_lista = grafo_com_inclusao_lista.get_qtd_vertices();
    std::string rotulo_1 = std::to_string(qtd_inicial_lista + 1);
    std::string rotulo_2 = std::to_string(qtd_inicial_lista + 2);

    grafo_com_inclusao_lista.inserir_vertice(rotulo_1);
    grafo_com_inclusao_lista.inserir_vertice(rotulo_2);

    std::cout << "\nApós inclusão do novo vértice:\n";
    grafo_com_inclusao_lista.print();

    std::cout << "\n9.2 - INCLUSÃO DE UM NOVO VÉRTICE USANDO MATRIZ DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o " + nome_grafo + " como referência:\n";

    grafo_original_matriz.print();

    GrafoMatrizAdj grafo_com_inclusao_matriz = grafo_original_matriz;

    int qtd_inicial_matriz = grafo_com_inclusao_matriz.get_qtd_vertices();
    rotulo_1 = std::to_string(qtd_inicial_matriz + 1);
    rotulo_2 = std::to_string(qtd_inicial_matriz + 2);


    grafo_com_inclusao_matriz.inserir_vertice(rotulo_1);
    grafo_com_inclusao_matriz.inserir_vertice(rotulo_2);

    std::cout << "\nApós inclusão do novo vértice:\n";
    grafo_com_inclusao_matriz.print();


    // 10 - Exclusão de um vértice existente usando Lista de Adjacências e Matriz de Adjacências.

    std::cout << "\n10.1 - EXCLUSÃO DE UM VÉRTICE EXISTENTE USANDO LISTA DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo anterior como referência:\n";

    grafo_com_inclusao_lista.print();

    GrafoListaAdj grafo_com_remocao_lista = grafo_com_inclusao_lista;

    int qtd_antes_remocao_lista = grafo_com_remocao_lista.get_qtd_vertices();
    if (qtd_antes_remocao_lista > 0) {
        int indice_para_remover = qtd_antes_remocao_lista - 1;
        std::string rotulo_removido = grafo_com_remocao_lista.get_rotulos()[indice_para_remover];

        std::cout << "\nRemovendo o último vértice (rótulo '" << rotulo_removido << "', índice " << indice_para_remover << ")...\n";

        grafo_com_remocao_lista.remover_vertice(indice_para_remover);

        std::cout << "\nGrafo após a exclusão:\n";
        grafo_com_remocao_lista.print();
    } else {
        std::cout << "\nNão há vértices para remover.\n";
    }

    std::cout << "\n10.2 - EXCLUSÃO DE UM VÉRTICE EXISTENTE USANDO MATRIZ DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo anterior como referência:\n";

    grafo_com_inclusao_matriz.print();

    GrafoMatrizAdj grafo_com_remocao_matriz = grafo_com_inclusao_matriz;

    int qtd_antes_remocao_matriz = grafo_com_remocao_matriz.get_qtd_vertices();
    if (qtd_antes_remocao_matriz > 0) {
        int indice_para_remover = qtd_antes_remocao_matriz - 1;
        std::string rotulo_removido = grafo_com_remocao_matriz.get_rotulos()[indice_para_remover];

        std::cout << "\nRemovendo o último vértice (rótulo '" << rotulo_removido << "', índice " << indice_para_remover << ")...\n";
        
        grafo_com_remocao_matriz.remover_vertice(indice_para_remover);

        std::cout << "\nGrafo após a exclusão:\n";
        grafo_com_remocao_matriz.print();
    } else {
        std::cout << "\nNão há vértices para remover.\n";
    }

    // 11 - Verificar se o grafo é ou não conexo

    std::cout << "\n11 - O " + nome_grafo + " é conexo?\n";
    grafo_original_lista.is_conexo() ? std::cout << "O " + nome_grafo + " é conexo" << std::endl :  std::cout << "O " + nome_grafo + " é não conexo" << std::endl;

    // 12 - Verificar se o grafo é ou não bipartido

    std::cout << "\n12 - O " + nome_grafo + " é bipartido?\n";
    grafo_original_lista.is_bipartido() ? std::cout << "O " + nome_grafo + " é bipartido" << std::endl :  std::cout << "O " + nome_grafo + " é não bipartido" << std::endl;

    // 13 - Busca em Largura (BFS) - Implementação 

    std::cout << "\n13 - IMPLEMENTAÇÃO " + nome_grafo + ": BUSCA EM LARGURA (BFS)\n";
    ArvoreLargura arvore_bfs = busca_largura_arestas_retorno(grafo_original_lista, 0);
    arvore_bfs.exportar_arvore_bfs(arvore_bfs, "arvore_bfs_"+nome_grafo+".dot");
    gerar_imagem("arvore_bfs_"+nome_grafo+".dot", "arvore_bfs_"+nome_grafo+".png");

    // 14 - Busca em Profundidade (DFS) - Implementação 

    std::cout << "\n14 - IMPLEMENTAÇÃO " + nome_grafo + ": BUSCA EM PROFUNDIDADE (DFS)\n";
    auto resultado_dfs = busca_profundidade_lista_adj_recursiva(grafo_original_lista, 0);
    std::map<int, int> predecessores_dfs = resultado_dfs.first;
    std::vector<std::pair<int, int>> arestas_retorno_dfs = resultado_dfs.second;
    exportar_arvore_profundidade_para_dot("dfs_"+nome_grafo+"_com_retorno.dot", predecessores_dfs, arestas_retorno_dfs, grafo_original_lista.get_rotulos());
    gerar_imagem("dfs_"+nome_grafo+"_com_retorno.dot","dfs_"+nome_grafo+"_com_retorno.png");

    // 15 - Determinação de articulações e blocos (biconectividade), utilizando lowpt.

    std::cout << "\n15 - IMPLEMENTAÇÃO " + nome_grafo + ": DETERMINAÇÂO DE ARTICULAÇÔES E BLOCOS COM LOWPT\n";
    grafo_original_lista.determinar_articulacoes_blocos_lowpt();
}

void digrafo(std::string txt){
    std::string caminho_arquivo = "../dados/" + txt;
    std::string nome_grafo = txt.substr(0, txt.find(".txt"));

    // 16 - Representação do Digrafo a partir da Matriz de Adjacências.

    std::cout << "\n16 - IMPLEMENTAÇÃO DIGRAFO: MATRIZ DE ADJACÊNCIA\n";
    DigrafoMatrizAdj digrafo_matriz(0);
    digrafo_matriz.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(digrafo_matriz, nome_grafo, "matriz_adj", true);

    // 16.2 - Representação do Digrafo a partir da Lista de Adjacências.

    DigrafoListaAdj digrafo_lista(0);
    digrafo_lista.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(digrafo_lista, nome_grafo, "lista_adj", true);

    // 17 - Representação do Digrafo a partir da Matriz de Incidência.
    std::cout << "\n17 - IMPLEMENTAÇÃO DIGRAFO: MATRIZ DE INCIDÊNCIA\n";
    DigrafoMatrizInc digrafo_inc(0);
    digrafo_inc.carregar_de_arquivo(caminho_arquivo);
    analisar_e_gerar_imagem(digrafo_inc, nome_grafo, "matriz_inc", true);

    // 18 - Determinação do Grafo subjacente

    std::cout << "\n18 - DETERMINAÇÃO DO GRAFO SUBJACENTE\n";
    GrafoListaAdj grafo_subjacente = digrafo_lista.obter_grafo_subjacente(digrafo_lista);
    grafo_subjacente.exportar_para_dot("GRAFO_SUBJACENTE_"+nome_grafo+"_lista_adj.dot", false);
    analisar_e_gerar_imagem(grafo_subjacente, nome_grafo, "lista_adj_subjacente", true);
    
    // 19 - Busca em Largura (BFS) - Implementação para Digrafo
    std::cout << "\n19 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM LARGURA (BFS)\n";
    
    auto arvore_bfs_digrafo = busca_largura_digrafo(digrafo_lista, 0);
    exportar_arvore_bfs_para_dot("ARVORE_BFS_"+nome_grafo+".dot", arvore_bfs_digrafo.get_qtd_vertices(), arvore_bfs_digrafo);
    gerar_imagem("ARVORE_BFS_"+nome_grafo+".dot", "ARVORE_BFS_"+nome_grafo+".png");

    // 20 - Busca em Profundidade (DFS) - Implementação para Digrafo
    std::cout << "\n20 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM PROFUNDIDADE (DFS)\n";
    auto arvore_dfs_digrafo = busca_profundidade_digrafo_completa(digrafo_lista, 0);
    exportar_arvore_dfs_para_dot("ARVORE_DFS_"+nome_grafo+".dot", arvore_dfs_digrafo);
    gerar_imagem("ARVORE_DFS_"+nome_grafo+".dot", "ARVORE_DFS_"+nome_grafo+".png");
    
}