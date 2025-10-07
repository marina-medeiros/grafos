#include <iostream>
#include <string>
#include <filesystem>

#include "headers/Grafo.h"
#include "headers/GrafoListaAdj.h"
#include "headers/GrafoMatrizAdj.h"
#include "headers/GrafoMatrizInc.h"
// #include "headers/digrafo.h"

void analisar_e_gerar_imagem(Grafo& grafo, const std::string& nome_arquivo, const std::string& tipo_impl) {
    std::cout << "\n\nAnálise do " << nome_arquivo << std::endl;

    grafo.print();

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
    
    grafo.is_conexo() ? std::cout << "O grafo é conexo" << std::endl :  std::cout << "O grafo é não conexo" << std::endl;
    grafo.is_bipartido() ? std::cout << "O grafo é bipartido" << std::endl :  std::cout << "O grafo é não bipartido" << std::endl;

    // Gera a imagem de visualização   
    std::string arq_dot = "dot-files/" + nome_arquivo + "_" + tipo_impl + ".dot";
    std::string arq_png = "png-files/" + nome_arquivo + "_" + tipo_impl + ".png";
    
    std::cout << "Gerando imagem em '" << arq_png << "'...\n";
    grafo.exportar_para_dot(arq_dot);
    grafo.gerar_imagem(arq_dot, arq_png);
}

int main(){

    std::filesystem::create_directory("dot-files");
    std::filesystem::create_directory("png-files");

    // 1. Criação do Grafo a partir da Lista de Adjacências

    std::cout << "\nIMPLEMENTAÇÃO: LISTA DE ADJACÊNCIA\n";
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

    std::cout << "\nIMPLEMENTAÇÃO: MATIRZ DE ADJACÊNCIA\n";
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

    std::cout << "\nIMPLEMENTAÇÃO: MATIRZ DE Incidência\n";
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
}