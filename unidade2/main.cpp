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

void agm_basico();

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
    std::cout << "\nO que deseja fazer?\n" << std::endl;
    std::cout << "1 | Árvore Geradora Mínima: Kruskal, Prim e Boruvka" << std::endl;
    std::cout << "2 | Árvore Geradora Mínima: Chu-Liu/Edmonds" << std::endl;
    std::cout << "3 | Caminho Mais Curto" << std::endl;
    std::cout << "4 | Grafos Eulerianos" << std::endl;
    std::cout << "\nDigite 'sair' ou 's' para terminar." << std::endl;
    std::cout << "Insira a opção escolhida: ";
}

int main(){
    while(true){
        menu();
        std::string entrada;
        std::cin >> entrada;

        std::transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);

        if (entrada == "sair" || entrada == "s") {
            break;
        }

        if(entrada == "1"){
            agm_basico();
        }

    }


    // ///////////// KRUSKAL //////////////////////////
    // GrafoMatrizAdj grafo0(5);

    // GrafoMatrizAdj AGM = gerar_agm_kruskal(grafo0);

    // analisar_e_gerar_imagem(grafo0, "grafo_0", "matriz_adj");
    // analisar_e_gerar_imagem(AGM, "AGM_grafo0", "matriz_adj");

    // std::cout << std::endl << std::endl;

    // ///////////// DIJKSTRA //////////////////////////
    // GrafoMatrizAdj grafo1(7);
    // DigrafoMatrizAdj digrafo0(6);
    // dijkstra_geral(grafo1, 0);
    // dijkstra_geral(digrafo0, 0);
    // dijkstra_geral(grafo1, 6);
    // dijkstra_geral(digrafo0, 5);
    // dijkstra_geral(digrafo0, 2);
    // dijkstra_especifico(grafo1, 0, 4); // 6
    // dijkstra_especifico(grafo1, 6, 3); // 8
    // dijkstra_especifico(digrafo0, 2, 3); // 999
}

void agm_basico(){
    GrafoMatrizAdj digrafo_AGM(0); // grafo grande que está no arquivo do trabalho
    digrafo_AGM.carregar_de_arquivo("../dados/DIGRAFO_0.txt");

    //------------------------------------ kruskal -----------------------------------------
    // Exemplo dos slides
    GrafoMatrizAdj grafo_kruskal(0);
    grafo_kruskal.carregar_de_arquivo("../dados/GRAFO_KRUSKAL.txt");
    analisar_e_gerar_imagem(grafo_kruskal, "grafo_kruskal", "matriz_adj");

    GrafoMatrizAdj agm_kruskal = gerar_agm_kruskal(grafo_kruskal);
    analisar_e_gerar_imagem(agm_kruskal, "agm_kruskal", "matriz_adj");

    // Exemplo do pdf do trabalho
    GrafoMatrizAdj agm_kruskal_digrafo =  gerar_agm_kruskal(digrafo_AGM);
    analisar_e_gerar_imagem(agm_kruskal_digrafo, "agm_kruskal_digrafo", "matriz_adj");

    //------------------------------------ prim -----------------------------------------


    //------------------------------------ boruvka -----------------------------------------
}

void caminho_minimo(){
    GrafoMatrizAdj grafo(0);
}