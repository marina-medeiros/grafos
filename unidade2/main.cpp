#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include "../../final/headers/busca-profundidade.h"
#include "../../final/headers/Grafo.h"
#include "../../final/headers/GrafoListaAdj.h"
#include "../../final/headers/GrafoMatrizAdj.h"
#include "../../final/headers/DigrafoMatrizAdj.h"
#include "headers/arvore-minima.h"
#include "headers/kruskal.h"
#include "headers/dijkstra.h"

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

int main(){
    ///////////// KRUSKAL //////////////////////////
    GrafoMatrizAdj grafo0(5);
    
    grafo0.inserir_aresta(1, 2, 1);
    grafo0.inserir_aresta(1, 3, 20);
    grafo0.inserir_aresta(2, 3, 17);
    grafo0.inserir_aresta(0, 2, 85);
    grafo0.inserir_aresta(0, 3, 22);
    grafo0.inserir_aresta(1, 4, 86);
    grafo0.inserir_aresta(3, 4, 23);
    grafo0.inserir_aresta(0, 4, 86);
    grafo0.inserir_aresta(0, 1, 15);
    grafo0.inserir_aresta(2, 4, 90);
    
    GrafoMatrizAdj AGM = gerar_arvore_minima(grafo0);

    analisar_e_gerar_imagem(grafo0, "grafo_0", "matriz_adj");
    analisar_e_gerar_imagem(AGM, "AGM_grafo0", "matriz_adj");

    std::cout << std::endl << std::endl;

    ///////////// DIJKSTRA //////////////////////////
    GrafoMatrizAdj grafo1(7);
    grafo1.inserir_aresta(0, 1, 2);
    grafo1.inserir_aresta(0, 3, 5);
    grafo1.inserir_aresta(0, 2, 4);
    grafo1.inserir_aresta(1, 3, 2);
    grafo1.inserir_aresta(2, 3, 1);
    grafo1.inserir_aresta(2, 5, 4);
    grafo1.inserir_aresta(3, 4, 2);
    grafo1.inserir_aresta(3, 5, 3);
    grafo1.inserir_aresta(4, 5, 1);
    grafo1.inserir_aresta(4, 6, 5);
    grafo1.inserir_aresta(5, 6, 7);


    DigrafoMatrizAdj digrafo0(6);
    digrafo0.inserir_aresta(0, 1, 5);
    digrafo0.inserir_aresta(0, 2, 2);
    digrafo0.inserir_aresta(1, 2, 1);
    digrafo0.inserir_aresta(1, 3, 4);
    digrafo0.inserir_aresta(1, 4, 2);
    digrafo0.inserir_aresta(2, 4, 7);
    digrafo0.inserir_aresta(3, 4, 6);
    digrafo0.inserir_aresta(3, 5, 3);
    digrafo0.inserir_aresta(4, 5, 1);

    dijkstra_geral(grafo1, 0);
    dijkstra_geral(digrafo0, 0);
    dijkstra_geral(grafo1, 6);
    dijkstra_geral(digrafo0, 5);
    dijkstra_geral(digrafo0, 2);

    dijkstra_especifico(grafo1, 0, 4); // 6
    dijkstra_especifico(grafo1, 6, 3); // 8
    dijkstra_especifico(digrafo0, 2, 3); // 999
}