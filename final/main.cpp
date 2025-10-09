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
    std::string arq_dot = "../dot-files/" + nome_arquivo + "_" + tipo_impl + ".dot";
    std::string arq_png = "../png-files/" + nome_arquivo + "_" + tipo_impl + ".png";
    
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

    DigrafoListaAdj digrafo0_lista(0);
    digrafo0_lista.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    //analisar_e_gerar_imagem(digrafo0_lista, "DIGRAFO_0", "lista_adj", true);

    // 19 - Busca em Largura (BFS) - Implementação para Digrafo
    std::cout << "\n19 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM LARGURA (BFS)\n";
    
    auto arvore_bfs_digrafo = busca_largura_digrafo(digrafo0_lista, 0);
    exportar_arvore_bfs_para_dot("arvore_bfs_digrafo0.dot", arvore_bfs_digrafo.get_qtd_vertices(), arvore_bfs_digrafo);
    gerar_imagem("arvore_bfs_digrafo0.dot", "arvore_bfs_digrafo0.png");


    // 20 - Busca em Profundidade (DFS) - Implementação para Digrafo
    std::cout << "\n20 - IMPLEMENTAÇÃO DIGRAFO: BUSCA EM PROFUNDIDADE (DFS)\n";
    auto arvore_dfs_digrafo = busca_profundidade_digrafo_completa(digrafo0_lista, 0);
    exportar_arvore_dfs_para_dot("arvore_dfs_digrafo0.dot", arvore_dfs_digrafo);
    gerar_imagem("arvore_dfs_digrafo0.dot", "arvore_dfs_digrafo0.png");
}