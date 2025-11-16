#include <map>
#include <set>
#include <stack>
#include <utility> 
#include <vector>
#include <algorithm>
#include <iostream>
#include "../final/headers/busca-profundidade.h"
#include "../final/headers/Grafo.h"
#include "../final/headers/GrafoListaAdj.h"
#include "../final/headers/GrafoMatrizAdj.h"
#include "headers/arvore-minima.h"
#include "headers/bellmanford.h"
#include "headers/kruskal.h"
#include "headers/dijkstra.h"
#include "headers/prim.h"
#include "headers/boruvka.h"

void agm_kruskal();
void caminho_minimo_dijkstra();
void caminho_minimo_bellmanford();
void agm_prim();
void agm_boruvka();

void analisar_e_gerar_imagem(Grafo& grafo, const std::string& nome_arquivo, const std::string& tipo_impl, bool eh_digrafo = false) {
    std::cout << "\n\nAnálise do " << nome_arquivo << std::endl;

    grafo.print();

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
        
    // Gera a imagem de visualização   
    std::string arq_dot =  nome_arquivo + "_" + tipo_impl + ".dot";
    std::string arq_png = nome_arquivo + "_" + tipo_impl + ".png";
    
    std::cout << "Gerando imagem em '" << arq_png << "'...\n\n";
    grafo.exportar_para_dot(arq_dot, eh_digrafo);
    gerar_imagem(arq_dot, arq_png);
}

void menu() {
    std::cout << "\nO que deseja fazer?\n" << std::endl;
    std::cout << "1 | Árvore Geradora Mínima: Kruskal" << std::endl;
    std::cout << "2 | Árvore Geradora Mínima: Prim" << std::endl;
    std::cout << "3 | Árvore Geradora Mínima: Boruvka" << std::endl;
    std::cout << "4 | Árvore Geradora Mínima: Chu-Liu/Edmonds" << std::endl;
    std::cout << "5 | Caminho Mais Curto: Dijkstra" << std::endl;
    std::cout << "6 | Caminho Mais Curto: Bellman-Ford" << std::endl;
    std::cout << "7 | Caminho Mais Curto: Floyd-Warshall" << std::endl;
    std::cout << "8 | Grafos Eulerianos: Hierholzer para ciclos" << std::endl;
    std::cout << "9 | Grafos Eulerianos: Hierholzer para caminhos" << std::endl;
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

        int num_entrada = stoi(entrada);

        switch (num_entrada){
        case 1:
            agm_kruskal();
            break;
        case 2:
            agm_prim();
            break;
        case 3:
            agm_boruvka();
            break;
        case 5:
            caminho_minimo_dijkstra();
            break;
        case 6:
            caminho_minimo_bellmanford();
        default:
            break;
        }

    }
}

void agm_kruskal(){
    //Exemplo dos slides
    GrafoMatrizAdj grafo_kruskal(0);
    grafo_kruskal.carregar_de_arquivo("../dados/GRAFO_KRUSKAL.txt");
    analisar_e_gerar_imagem(grafo_kruskal, "grafo_slides_kruskal", "matriz_adj");
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_kruskal = gerar_agm_kruskal(grafo_kruskal);
    analisar_e_gerar_imagem(agm_kruskal, "agm_slides_kruskal", "matriz_adj");

    // Exemplo do pdf do trabalho
    GrafoMatrizAdj digrafo(0); 
    digrafo.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    analisar_e_gerar_imagem(digrafo, "digrafo_principal", "matriz_adj");
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_kruskal_digrafo =  gerar_agm_kruskal(digrafo);
    analisar_e_gerar_imagem(agm_kruskal_digrafo, "digrafo_principal_kruskal", "matriz_adj");

    // Exemplo do pdf do trabalho como grafo não direcionado
    GrafoMatrizAdj grafo_principal(0); 
    grafo_principal.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo_principal, "grafo_principal", "matriz_adj");
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_kruskal_grafo =  gerar_agm_kruskal(grafo_principal);
    analisar_e_gerar_imagem(agm_kruskal_grafo, "grafo_principal_kruskal", "matriz_adj");

}

void agm_prim(){
    // Exemplos dos slides
    GrafoMatrizAdj grafo_prim(0);
    grafo_prim.carregar_de_arquivo("../dados/GRAFO_PRIM.txt");
    analisar_e_gerar_imagem(grafo_prim, "grafo_slides_prim", "matriz_adj");
    //grafo_prim.print();
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_prim = prim(grafo_prim);
    analisar_e_gerar_imagem(agm_prim, "agm_slides_prim", "matriz_adj");

    // Exemplo do pdf do trabalho
    GrafoMatrizAdj grafo(0); 
    grafo.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo, "grafo_principal", "matriz_adj");
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_prim_digrafo =  prim(grafo);
    analisar_e_gerar_imagem(agm_prim_digrafo, "grafo_principal_prim", "matriz_adj");
    
}

void agm_boruvka(){
    // Exemplos dos slides
    GrafoMatrizAdj grafo_boruvka(0);
    grafo_boruvka.carregar_de_arquivo("../dados/GRAFO_BORUVKA.txt");
    analisar_e_gerar_imagem(grafo_boruvka, "grafo_slides_boruvka", "matriz_adj");
    grafo_boruvka.print();
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_boruvka = boruvka(grafo_boruvka);
    analisar_e_gerar_imagem(agm_boruvka, "agm_slides_boruvka", "matriz_adj");

    // Exemplo do pdf do trabalho
    GrafoMatrizAdj grafo(0); 
    grafo.carregar_de_arquivo("../dados/GRAFO_0.txt");
    analisar_e_gerar_imagem(grafo, "grafo_principal", "matriz_adj");
    // ----- Árvore mínima gerada:
    GrafoMatrizAdj agm_boruvka_digrafo =  boruvka(grafo);
    analisar_e_gerar_imagem(agm_boruvka_digrafo, "grafo_principal_boruvka", "matriz_adj");
}

void caminho_minimo_dijkstra(){
    // Exemplos dos slides
    std::cout << "------------------ exemplo dos slides --------------------------------------" << std::endl;
    DigrafoMatrizAdj grafo_dijkstra(0);
    grafo_dijkstra.carregar_de_arquivo("../dados/GRAFO_DIJKSTRA.txt");
    int inicio = grafo_dijkstra.get_indice_do_rotulo("0");
    int fim = grafo_dijkstra.get_indice_do_rotulo("6");
    dijkstra_geral(grafo_dijkstra, inicio);
    dijkstra_especifico(grafo_dijkstra, inicio, fim);

    DigrafoMatrizAdj digrafo_dijkstra(0);
    digrafo_dijkstra.carregar_de_arquivo("../dados/DIGRAFO_DIJKSTRA.txt");
    inicio = digrafo_dijkstra.get_indice_do_rotulo("0");
    fim = digrafo_dijkstra.get_indice_do_rotulo("5");
    dijkstra_geral(digrafo_dijkstra, inicio);
    dijkstra_especifico(digrafo_dijkstra, inicio, fim);

    // Exemplo do pdf do trabalho
    DigrafoMatrizAdj digrafo(0); 
    digrafo.carregar_de_arquivo("../dados/DIGRAFO_LISTA.txt");
    inicio = digrafo.get_indice_do_rotulo("0");
    fim = digrafo.get_indice_do_rotulo("14");
    dijkstra_geral(digrafo, inicio);
    dijkstra_especifico(digrafo, inicio, fim);
}

void caminho_minimo_bellmanford(){
    std::cout << "------------------ exemplo com ciclo negativo --------------------------------------" << std::endl;
    DigrafoListaAdjPonderada digrafo_ciclo(0); 
    digrafo_ciclo.carregar_de_arquivo("../dados/DIGRAFO_BELLMANFORD_1.txt");
    //analisar_e_gerar_imagem(digrafo_ciclo, "digrafo_ciclo_negativo", "matriz_adj", true); 
    bellman_ford_geral(digrafo_ciclo, 0);
    bellman_ford_especifico(digrafo_ciclo, 0, 3);

    std::cout << "------------------ exemplo sem ciclo negativo --------------------------------------" << std::endl;
    DigrafoListaAdjPonderada digrafo_sem_ciclo(0); 
    digrafo_sem_ciclo.carregar_de_arquivo("../dados/DIGRAFO_BELLMANFORD_0.txt");
    //analisar_e_gerar_imagem(digrafo_sem_ciclo, "digrafo_sem_ciclo", "matriz_adj", true); 
    bellman_ford_geral(digrafo_sem_ciclo, 0);
    bellman_ford_especifico(digrafo_sem_ciclo, 0, 3);

    std::cout << "------------------ exemplo sem ciclo negativo --------------------------------------" << std::endl;
    DigrafoListaAdjPonderada digrafo_lista(0); 
    digrafo_lista.carregar_de_arquivo("../dados/DIGRAFO_LISTA.txt");
    //analisar_e_gerar_imagem(digrafo_sem_ciclo, "digrafo_sem_ciclo", "matriz_adj", true); 
    bellman_ford_geral(digrafo_lista, 0);
    bellman_ford_especifico(digrafo_lista, 0, 14);
}