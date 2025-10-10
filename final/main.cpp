#include <iostream>
#include <string>
#include <filesystem>

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

void analisar_e_gerar_imagem(Grafo& grafo, const std::string& nome_arquivo, const std::string& tipo_impl, bool eh_digrafo = false) {
    std::cout << "\n\nAnálise do " << nome_arquivo << std::endl;

    grafo.print();

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
    
    grafo.is_conexo() ? std::cout << "O grafo é conexo" << std::endl :  std::cout << "O grafo é não conexo" << std::endl;
    grafo.is_bipartido() ? std::cout << "O grafo é bipartido" << std::endl :  std::cout << "O grafo é não bipartido" << std::endl;

    // Gera a imagem de visualização   
    std::string arq_dot =  nome_arquivo + "_" + tipo_impl + ".dot";
    std::string arq_png = nome_arquivo + "_" + tipo_impl + ".png";
    
    std::cout << "Gerando imagem em '" << arq_png << "'...\n";
    grafo.exportar_para_dot(arq_dot, eh_digrafo);
    gerar_imagem(arq_dot, arq_png);
}

int main(){

    std::filesystem::create_directory("dot-files");
    std::filesystem::create_directory("png-files");

    // 1. Criação do Grafo a partir da Lista de Adjacências

    std::cout << "\n1 -IMPLEMENTAÇÃO GRAFO: LISTA DE ADJACÊNCIA\n";
    GrafoListaAdj grafo0_lista(0);
    grafo0_lista.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo0_lista, "GRAFO_0", "lista_adj");

    GrafoListaAdj grafo1_lista(0);
    grafo1_lista.carregar_de_arquivo("../dados/GRAFO_1.txt");
    analisar_e_gerar_imagem(grafo1_lista, "GRAFO_1", "lista_adj");

    GrafoListaAdj grafo2_lista(0);
    grafo2_lista.carregar_de_arquivo("../dados/GRAFO_2.txt");
    analisar_e_gerar_imagem(grafo2_lista, "GRAFO_2", "lista_adj");

    GrafoListaAdj grafo3_lista(0);
    grafo3_lista.carregar_de_arquivo("../dados/GRAFO_3.txt");
    analisar_e_gerar_imagem(grafo3_lista, "GRAFO_3", "lista_adj");

    // 2. Criação do Grafo a partir da Matriz de Adjacências

    std::cout << "\n2 - IMPLEMENTAÇÃO GRAFO: MATRIZ DE ADJACÊNCIA\n";
    GrafoMatrizAdj grafo0_matriz(0);
    grafo0_matriz.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo0_matriz, "GRAFO_0", "matriz_adj");

    GrafoMatrizAdj grafo1_matriz(0);
    grafo1_matriz.carregar_de_arquivo("../dados/GRAFO_1.txt");
    analisar_e_gerar_imagem(grafo1_matriz, "GRAFO_1", "matriz_adj");

    GrafoMatrizAdj grafo2_matriz(0);
    grafo2_matriz.carregar_de_arquivo("../dados/GRAFO_2.txt");
    analisar_e_gerar_imagem(grafo2_matriz, "GRAFO_2", "matriz_adj");

    GrafoMatrizAdj grafo3_matriz(0);
    grafo3_matriz.carregar_de_arquivo("../dados/GRAFO_3.txt");
    analisar_e_gerar_imagem(grafo3_matriz, "GRAFO_3", "matriz_adj");

    // 3. Criação do Grafo a partir da Matriz de Incidência

    std::cout << "\n3 - IMPLEMENTAÇÃO GRAFO: MATRIZ DE Incidência\n";
    GrafoMatrizInc grafo0_inc(0);
    grafo0_inc.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo0_inc, "GRAFO_0", "matriz_inc");

    GrafoMatrizInc grafo1_inc(0);
    grafo1_inc.carregar_de_arquivo("../dados/GRAFO_1.txt");
    analisar_e_gerar_imagem(grafo1_inc, "GRAFO_1", "matriz_inc");

    GrafoMatrizInc grafo2_inc(0);
    grafo2_inc.carregar_de_arquivo("../dados/GRAFO_2.txt");
    analisar_e_gerar_imagem(grafo2_inc, "GRAFO_2", "matriz_inc");

    GrafoMatrizInc grafo3_inc(0);
    grafo3_inc.carregar_de_arquivo("../dados/GRAFO_3.txt");
    analisar_e_gerar_imagem(grafo3_inc, "GRAFO_3", "matriz_inc");

    // 4.1 Converter de matriz de adjacência para lista de adjacência

    std::cout << "\n4.1 - CONVERSÃO: MATRIZ DE ADJACÊNCIA PARA LISTA DE ADJACÊNCIA\n";

    std::cout << "ANTES DA CONVERSÃO - Grafo 0:\n";
    grafo0_matriz.print();

    GrafoListaAdj grafo0_lista_convertido = grafo0_matriz.converter_para_lista_adj();

    std::cout << "DEPOIS DA CONVERSÃO - Grafo 0:\n";
    grafo0_lista_convertido.print();

    // 4.2 Converter de lista de adjacência para matriz de adjacência

    std::cout << "\n4.2 CONVERSÃO: LISTA DE ADJACÊNCIA PARA MATRIZ DE ADJACÊNCIA\n";

    std::cout << "ANTES DA CONVERSÃO - Grafo 0:\n";
    grafo0_lista.print();

    GrafoMatrizAdj grafo0_matriz_convertido = grafo0_lista.converter_para_matriz_adj();

    std::cout << "DEPOIS DA CONVERSÃO - Grafo 0:\n";
    grafo0_matriz_convertido.print();

    // 5 e 6. Cálculo do grau de cada vértice e função que determina se dois vértices são adjacentes

    std::cout << "\n5 e 6 - CÁLCULO DO GRAU DO VÉRTICE E DETERMINAÇÃO DE ADJACÊNCIA\n";
    std::cout << "Utilizando o grafo_0 como referência:\n";

    grafo0_lista.print();

    std::cout << "Grau do vértice a(0): " << grafo0_lista.get_grau_vertice(0) << "\n";
    std::cout << "Grau do vértice b(1): " << grafo0_lista.get_grau_vertice(1) << "\n";
    std::cout << "Grau do vértice f(5): " << grafo0_lista.get_grau_vertice(5) << "\n";

    if (grafo0_lista.existe_aresta(0, 1)) {
        std::cout << "Os vértices " << grafo0_lista.get_rotulos()[0] << " e " << grafo0_lista.get_rotulos()[1] << " são adjacentes.\n";
    } else {
        std::cout << "Os vértices " << grafo0_lista.get_rotulos()[0] << " e " << grafo0_lista.get_rotulos()[1] << " não são adjacentes.\n";
    }

    if (grafo0_lista.existe_aresta(0, 5)) {
        std::cout << "Os vértices " << grafo0_lista.get_rotulos()[0] << " e " << grafo0_lista.get_rotulos()[5] << " são adjacentes.\n";
    } else {
        std::cout << "Os vértices " << grafo0_lista.get_rotulos()[0] << " e " << grafo0_lista.get_rotulos()[5] << " não são adjacentes.\n";
    }

     // 9 - Inclusão de um novo vértice usando Lista de Adjacências e Matriz de Adjacências.

    std::cout << "\n9.1 - INCLUSÃO DE UM NOVO VÉRTICE USANDO LISTA DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo_2 como referência:\n";

    grafo2_lista.print();

    std::cout << "\nApós inclusão do novo vértice:\n";

    grafo2_lista.inserir_vertice("12");
    grafo2_lista.inserir_vertice("13");
    grafo2_lista.print();

    std::cout << "\n9.2 - INCLUSÃO DE UM NOVO VÉRTICE USANDO MATRIZ DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo_2 como referência:\n";

    grafo2_matriz.print();

    std::cout << "\nApós inclusão do novo vértice:\n";

    grafo2_matriz.inserir_vertice("12");
    grafo2_matriz.inserir_vertice("13");
    grafo2_matriz.print();

    // 10 - Exclusão de um vértice existente usando Lista de Adjacências e Matriz de Adjacências.

    std::cout << "\n10.1 - EXCLUSÃO DE UM VÉRTICE EXISTENTE USANDO LISTA DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo_2 anterior como referência:\n";

    grafo2_lista.print();

    std::cout << "\nApós remoção do vértice com rótulo 1\n";

    grafo2_lista.remover_vertice(0);
    grafo2_lista.print();

    std::cout << "\n10.2 - EXCLUSÃO DE UM VÉRTICE EXISTENTE USANDO MATRIZ DE ADJACÊNCIAS\n";
    std::cout << "Utilizando o grafo_2 como referência:\n";

    grafo2_matriz.print();

    std::cout << "\nApós remoção do vértice com rótulo 2\n";

    grafo2_matriz.remover_vertice(1);
    grafo2_matriz.print();

    // 13 - Busca em Largura (BFS) - Implementação 

    std::cout << "\n13 - IMPLEMENTAÇÃO GRAFO: BUSCA EM LARGURA (BFS)\n";
    ArvoreLargura arvore_bfs = busca_largura_arestas_retorno(grafo0_lista, 0);
    arvore_bfs.exportar_arvore_bfs(arvore_bfs, "arvore_bfs_grafo0.dot");
    gerar_imagem("arvore_bfs_grafo0.dot", "arvore_bfs_grafo0.png");

    // 14 - Busca em Profundidade (DFS) - Implementação 

    std::cout << "\n14 - IMPLEMENTAÇÃO GRAFO: BUSCA EM PROFUNDIDADE (DFS)\n";
    auto resultado_dfs = busca_profundidade_lista_adj_recursiva(grafo0_lista, 0);
    std::map<int, int> predecessores_dfs = resultado_dfs.first;
    std::vector<std::pair<int, int>> arestas_retorno_dfs = resultado_dfs.second;
    exportar_arvore_profundidade_para_dot("dfs_grafo0_com_retorno.dot", predecessores_dfs, arestas_retorno_dfs);
    gerar_imagem("dfs_grafo0_com_retorno.dot", "dfs_grafo0_com_retorno.png");

    // 15 - Determinação de articulações e blocos (biconectividade), utilizando lowpt.

    std::cout << "\n15 - IMPLEMENTAÇÃO GRAFO: DETERMINAÇÂO DE ARTICULAÇÔES E BLOCOS COM LOWPT\n";
    grafo2_lista.determinar_articulacoes_blocos_lowpt();

    // 16 - Representação do Digrafo a partir da Matriz de Adjacências.

    std::cout << "\n16 - IMPLEMENTAÇÃO DIGRAFO: MATRIZ DE ADJACÊNCIA\n";
    DigrafoMatrizAdj digrafo0_matriz(0);
    digrafo0_matriz.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    analisar_e_gerar_imagem(digrafo0_matriz, "DIGRAFO_0", "matriz_adj", true);

    DigrafoMatrizAdj digrafo1_matriz(0);
    digrafo1_matriz.carregar_de_arquivo("../dados/DIGRAFO_1.txt");
    analisar_e_gerar_imagem(digrafo1_matriz, "DIGRAFO_1", "matriz_adj", true);

    DigrafoMatrizAdj digrafo2_matriz(0);
    digrafo2_matriz.carregar_de_arquivo("../dados/DIGRAFO_2.txt");
    analisar_e_gerar_imagem(digrafo2_matriz, "DIGRAFO_2", "matriz_adj", true);

    DigrafoMatrizAdj digrafo3_matriz(0);
    digrafo3_matriz.carregar_de_arquivo("../dados/DIGRAFO_3.txt");
    analisar_e_gerar_imagem(digrafo3_matriz, "DIGRAFO_3", "matriz_adj", true);

    // 16.2 - Representação do Digrafo a partir da Lista de Adjacências.

    DigrafoListaAdj digrafo0_lista(0);
    digrafo0_lista.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    analisar_e_gerar_imagem(digrafo0_lista, "DIGRAFO_0", "lista_adj", true);

    DigrafoListaAdj digrafo1_lista(0);
    digrafo1_lista.carregar_de_arquivo("../dados/DIGRAFO_1.txt");
    analisar_e_gerar_imagem(digrafo1_lista, "DIGRAFO_1", "lista_adj", true);

    DigrafoListaAdj digrafo2_lista(0);
    digrafo2_lista.carregar_de_arquivo("../dados/DIGRAFO_2.txt");
    analisar_e_gerar_imagem(digrafo2_lista, "DIGRAFO_2", "lista_adj", true);

    DigrafoListaAdj digrafo3_lista(0);
    digrafo3_lista.carregar_de_arquivo("../dados/DIGRAFO_3.txt");
    analisar_e_gerar_imagem(digrafo3_lista, "DIGRAFO_3", "lista_adj", true);

    // 17 - Representação do Digrafo a partir da Matriz de Incidência.
    std::cout << "\n17 - IMPLEMENTAÇÃO DIGRAFO: MATRIZ DE INCIDÊNCIA\n";
    DigrafoMatrizInc digrafo0_inc(0);
    digrafo0_inc.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    analisar_e_gerar_imagem(digrafo0_inc, "DIGRAFO_0", "matriz_inc", true);

    DigrafoMatrizInc digrafo1_inc(0);
    digrafo1_inc.carregar_de_arquivo("../dados/DIGRAFO_1.txt");
    analisar_e_gerar_imagem(digrafo1_inc, "DIGRAFO_1", "matriz_inc", true);

    DigrafoMatrizInc digrafo2_inc(0);
    digrafo2_inc.carregar_de_arquivo("../dados/DIGRAFO_2.txt");
    analisar_e_gerar_imagem(digrafo2_inc, "DIGRAFO_2", "matriz_inc", true);

    DigrafoMatrizInc digrafo3_inc(0);
    digrafo3_inc.carregar_de_arquivo("../dados/DIGRAFO_3.txt");
    analisar_e_gerar_imagem(digrafo3_inc, "DIGRAFO_3", "matriz_inc", true);

    // 18 - Determinação do Grafo subjacente

    std::cout << "\n18 - DETERMINAÇÃO DO GRAFO SUBJACENTE\n";
    GrafoListaAdj grafo_subjacente_d0 = digrafo0_lista.obter_grafo_subjacente(digrafo0_lista);
    grafo_subjacente_d0.exportar_para_dot("GRAFO_SUBJACENTE_DIGRAFO_0_lista_adj.dot", false);
    gerar_imagem("GRAFO_SUBJACENTE_DIGRAFO_0_lista_adj.dot", "GRAFO_SUBJACENTE_DIGRAFO_0_lista_adj.png");
    
    GrafoListaAdj grafo_subjacente_d1 = digrafo1_lista.obter_grafo_subjacente(digrafo1_lista);
    grafo_subjacente_d1.exportar_para_dot("GRAFO_SUBJACENTE_DIGRAFO_1_lista_adj.dot", false);
    gerar_imagem("GRAFO_SUBJACENTE_DIGRAFO_1_lista_adj.dot", "GRAFO_SUBJACENTE_DIGRAFO_1_lista_adj.png");

    GrafoListaAdj grafo_subjacente_d2 = digrafo2_lista.obter_grafo_subjacente(digrafo2_lista);
    grafo_subjacente_d2.exportar_para_dot("GRAFO_SUBJACENTE_DIGRAFO_2_lista_adj.dot", false);
    gerar_imagem("GRAFO_SUBJACENTE_DIGRAFO_2_lista_adj.dot", "GRAFO_SUBJACENTE_DIGRAFO_2_lista_adj.png");   

    GrafoListaAdj grafo_subjacente_d3 = digrafo3_lista.obter_grafo_subjacente(digrafo3_lista);
    grafo_subjacente_d3.exportar_para_dot("GRAFO_SUBJACENTE_DIGRAFO_3_lista_adj.dot", false);
    gerar_imagem("GRAFO_SUBJACENTE_DIGRAFO_3_lista_adj.dot", "GRAFO_SUBJACENTE_DIGRAFO_3_lista_adj.png");   
    

    // 19 - Busca em Largura (BFS) - Implementação para Digrafo
    std::cout << "\n19 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM LARGURA (BFS)\n";
    
    auto arvore_bfs_digrafo0 = busca_largura_digrafo(digrafo0_lista, 0);
    exportar_arvore_bfs_para_dot("ARVORE_BFS_DIGRAFO0.dot", arvore_bfs_digrafo0.get_qtd_vertices(), arvore_bfs_digrafo0);
    gerar_imagem("ARVORE_BFS_DIGRAFO0.dot", "ARVORE_BFS_DIGRAFO0.png");

    auto arvore_bfs_digrafo1 = busca_largura_digrafo(digrafo1_lista, 0);
    exportar_arvore_bfs_para_dot("ARVORE_BFS_DIGRAFO1.dot", arvore_bfs_digrafo1.get_qtd_vertices(), arvore_bfs_digrafo1);
    gerar_imagem("ARVORE_BFS_DIGRAFO1.dot", "ARVORE_BFS_DIGRAFO1.png");

    auto arvore_bfs_digrafo2 = busca_largura_digrafo(digrafo2_lista, 0);
    exportar_arvore_bfs_para_dot("ARVORE_BFS_DIGRAFO2.dot", arvore_bfs_digrafo2.get_qtd_vertices(), arvore_bfs_digrafo2);
    gerar_imagem("ARVORE_BFS_DIGRAFO2.dot", "ARVORE_BFS_DIGRAFO2.png");

    auto arvore_bfs_digrafo3 = busca_largura_digrafo(digrafo3_lista, 0);
    exportar_arvore_bfs_para_dot("ARVORE_BFS_DIGRAFO3.dot", arvore_bfs_digrafo3.get_qtd_vertices(), arvore_bfs_digrafo3);
    gerar_imagem("ARVORE_BFS_DIGRAFO3.dot", "ARVORE_BFS_DIGRAFO3.png");

    // 20 - Busca em Profundidade (DFS) - Implementação para Digrafo
    std::cout << "\n20 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM PROFUNDIDADE (DFS)\n";
    auto arvore_dfs_digrafo0 = busca_profundidade_digrafo_completa(digrafo0_lista, 0);
    exportar_arvore_dfs_para_dot("ARVORE_DFS_DIGRAFO0.dot", arvore_dfs_digrafo0);
    gerar_imagem("ARVORE_DFS_DIGRAFO0.dot", "ARVORE_DFS_DIGRAFO0.png");

    auto arvore_dfs_digrafo1 = busca_profundidade_digrafo_completa(digrafo1_lista, 0);
    exportar_arvore_dfs_para_dot("ARVORE_DFS_DIGRAFO1.dot", arvore_dfs_digrafo1);
    gerar_imagem("ARVORE_DFS_DIGRAFO1.dot", "ARVORE_DFS_DIGRAFO1.png");

    auto arvore_dfs_digrafo2 = busca_profundidade_digrafo_completa(digrafo2_lista, 0);
    exportar_arvore_dfs_para_dot("ARVORE_DFS_DIGRAFO2.dot", arvore_dfs_digrafo2);
    gerar_imagem("ARVORE_DFS_DIGRAFO2.dot", "ARVORE_DFS_DIGRAFO2.png");

    auto arvore_dfs_digrafo3 = busca_profundidade_digrafo_completa(digrafo3_lista, 0);
    exportar_arvore_dfs_para_dot("ARVORE_DFS_DIGRAFO3.dot", arvore_dfs_digrafo3);
    gerar_imagem("ARVORE_DFS_DIGRAFO3.dot", "ARVORE_DFS_DIGRAFO3.png");
    
}