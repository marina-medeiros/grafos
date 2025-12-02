#include <iostream>
#include "../../final/headers/DigrafoMatrizAdj.h"

void analisar_digrafo(DigrafoMatrizAdj& grafo, const std::string& nome_arquivo, bool peso_eh_decimal = false) {
    std::cout << "\nAnálise do " << nome_arquivo << std::endl;

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
        
    // Gera a imagem de visualização   
    std::string arq_dot =  nome_arquivo + ".dot";
    
    grafo.exportar_para_dot_com_pesos(arq_dot, peso_eh_decimal);
}

int main() {
  DigrafoMatrizAdj digrafo_problema1(0);
  digrafo_problema1.carregar_de_arquivo_csv("../dados/PROBLEMA_1.csv", true);
  analisar_digrafo(digrafo_problema1, "problema_1", true);

  DigrafoMatrizAdj digrafo_problema2(0);
  digrafo_problema2.carregar_de_arquivo_csv("../dados/PROBLEMA_2.csv");
  analisar_digrafo(digrafo_problema2, "problema_2");

  DigrafoMatrizAdj digrafo_problema3(0);
  digrafo_problema3.carregar_de_arquivo_csv("../dados/PROBLEMA_3.csv", true);
  analisar_digrafo(digrafo_problema3, "problema_3", true);

  DigrafoMatrizAdj digrafo_problema4(0);
  digrafo_problema4.carregar_de_arquivo_csv("../dados/PROBLEMA_4.csv");
  analisar_digrafo(digrafo_problema4, "problema_4");

DigrafoMatrizAdj digrafo_problema5(0);
  digrafo_problema5.carregar_de_arquivo_csv("../dados/PROBLEMA_5.csv", true);
  analisar_digrafo(digrafo_problema5, "problema_5", true);

  DigrafoMatrizAdj digrafo_problema6(0);
  digrafo_problema6.carregar_de_arquivo_csv("../dados/PROBLEMA_6.csv");
  analisar_digrafo(digrafo_problema6, "problema_6");

  DigrafoMatrizAdj digrafo_problema7(0);
  digrafo_problema7.carregar_de_arquivo_csv("../dados/PROBLEMA_7.csv", true);
  analisar_digrafo(digrafo_problema7, "problema_7", true);

  DigrafoMatrizAdj digrafo_problema8(0);
  digrafo_problema8.carregar_de_arquivo_csv("../dados/PROBLEMA_8.csv");
  analisar_digrafo(digrafo_problema8, "problema_8");

  DigrafoMatrizAdj digrafo_problema9(0);
  digrafo_problema9.carregar_de_arquivo_csv("../dados/PROBLEMA_9.csv", true);
  analisar_digrafo(digrafo_problema9, "problema_9", true);

  DigrafoMatrizAdj digrafo_problema10(0);
  digrafo_problema10.carregar_de_arquivo_csv("../dados/PROBLEMA_10.csv");
  analisar_digrafo(digrafo_problema10, "problema_10");

  DigrafoMatrizAdj digrafo_problema11(0);
  digrafo_problema11.carregar_de_arquivo_csv("../dados/PROBLEMA_11.csv", true);
  analisar_digrafo(digrafo_problema11, "problema_11", true);

  DigrafoMatrizAdj digrafo_problema12(0);
  digrafo_problema12.carregar_de_arquivo_csv("../dados/PROBLEMA_12.csv");
  analisar_digrafo(digrafo_problema12, "problema_12");
}