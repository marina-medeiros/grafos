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

void agm_kruskal();
void caminho_minimo_dijkstra();

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
        case 3:
            caminho_minimo_dijkstra();
            break;
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

}

void caminho_minimo_dijkstra(){
    // Exemplos dos slides
    GrafoMatrizAdj grafo_dijkstra(0);
    grafo_dijkstra.carregar_de_arquivo("../dados/GRAFO_DIJKSTRA.txt");
    analisar_e_gerar_imagem(grafo_dijkstra, "grafo_slides_dijkstra", "matriz_adj");
    dijkstra_geral(grafo_dijkstra, 0);
    dijkstra_especifico(grafo_dijkstra, 1, 6);

    GrafoMatrizAdj digrafo_dijkstra(0);
    digrafo_dijkstra.carregar_de_arquivo("../dados/DIGRAFO_DIJKSTRA.txt");
    analisar_e_gerar_imagem(digrafo_dijkstra, "dirafo_slides_dijkstra", "matriz_adj");
    dijkstra_geral(digrafo_dijkstra, 0);
    dijkstra_especifico(digrafo_dijkstra, 1, 4);

    // Exemplo do pdf do trabalho
    GrafoMatrizAdj digrafo(0); 
    digrafo.carregar_de_arquivo("../dados/DIGRAFO_0.txt");
    analisar_e_gerar_imagem(digrafo, "digrafo_principal", "matriz_adj");
    dijkstra_geral(digrafo, 0);
    dijkstra_especifico(digrafo, 0, 14);
}