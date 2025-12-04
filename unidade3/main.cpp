#include <iostream>
#include "../../final/headers/DigrafoMatrizAdj.h"
#include "../headers/insercao-mais-barata.h"
#include "../headers/vizinho-mais-proximo.h"
#include "../headers/buscas-locais.h"
#include "../headers/buscas-locais-testes.h"

void analisar_digrafo(DigrafoMatrizAdj& grafo, const std::string& nome_arquivo, bool peso_eh_decimal = false) {
    std::cout << "\nAnálise do " << nome_arquivo << std::endl;

    // Testa os algoritmos
    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
        
    // Gera a imagem de visualização   
    std::string arq_dot =  nome_arquivo + ".dot";
    
    grafo.exportar_para_dot_com_pesos(arq_dot, peso_eh_decimal);
}

void imprimir_resultado(const std::string& nome_algoritmo, 
                        const std::pair<std::vector<int>, int>& resultado, 
                        bool peso_eh_decimal) {
    std::cout << "  >> Algoritmo: " << nome_algoritmo << std::endl;
    
    double custo_formatado = peso_eh_decimal ? (resultado.second / 10.0) : resultado.second;
    
    std::cout << "     Custo Total: " << custo_formatado << std::endl;
    std::cout << "     Rota: [ ";
    for (size_t i = 0; i < resultado.first.size(); ++i) {
        std::cout << resultado.first[i];
        if (i < resultado.first.size() - 1) std::cout << " -> ";
    }
    std::cout << " ]\n" << std::endl;
}

void imprimir_busca_local(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "Solucoes encontradas a partir da busca local: " << std::endl;
    std::cout << "------------ Metodo 'first improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 1, grafo));
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 2, grafo));
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 3, grafo));
    std::cout << "------------ Metodo 'best improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 1, grafo));
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 2, grafo));
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 3, grafo));
    std::cout << "----------------------------------------------------------" << std::endl;
}

void imprimir_busca_local(std::pair<std::vector<int>, int> solucao, const DigrafoMatrizAdj &grafo){
    std::cout << "----------------------------------------------------------" << std::endl;
    std::cout << "Solucoes encontradas a partir da busca local: " << std::endl;
    std::cout << "------------ Metodo 'first improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 1, grafo));
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 2, grafo));
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 1, 3, grafo));
    std::cout << "------------ Metodo 'best improvement': ------------" << std::endl;
    std::cout << ">>> Heuristica SWAP': " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 1, grafo));
    std::cout << ">>> Heuristica SHIFT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 2, grafo));
    std::cout << ">>> Heuristica INVERT': : " << std::endl;
    imprimir_solucao(busca_local(solucao, 2, 3, grafo));
    std::cout << "----------------------------------------------------------" << std::endl;
}

void testes_buscas_locais(){
  DigrafoMatrizAdj grafo(0);
  grafo.carregar_de_arquivo_csv("../dados/testes.csv", true);

  std::vector<int> ordem = {0, 1, 2, 3, 4};
  double custo = calcula_custo(ordem, grafo);
  std::pair<std::vector<int>, int> solucao(ordem, custo);

  testar_swap(grafo, solucao);
  testar_shift(grafo, solucao);
  testar_invert(grafo, solucao);

  testar_vizinhanca_swap(grafo, solucao);
  testar_vizinhanca_shift(grafo, solucao);
  testar_vizinhanca_invert(grafo, solucao);
}

int main() {  
  DigrafoMatrizAdj digrafo_problema1(0);
  digrafo_problema1.carregar_de_arquivo_csv("../dados/PROBLEMA_1.csv", true);
  analisar_digrafo(digrafo_problema1, "problema_1", true);
  auto res_vizinho1 = vizinho_mais_proximo(digrafo_problema1, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho1, true);
  imprimir_busca_local(res_vizinho1, digrafo_problema1); /////////////
  auto res_insercao1 = insercao_mais_barata(digrafo_problema1, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao1, true);
  imprimir_busca_local(res_insercao1, digrafo_problema1); /////////////

  DigrafoMatrizAdj digrafo_problema2(0);
  digrafo_problema2.carregar_de_arquivo_csv("../dados/PROBLEMA_2.csv");
  analisar_digrafo(digrafo_problema2, "problema_2");
  auto res_vizinho2 = vizinho_mais_proximo(digrafo_problema2, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho2, false);
  imprimir_busca_local(res_vizinho2, digrafo_problema2); /////////////
  auto res_insercao2 = insercao_mais_barata(digrafo_problema2, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao2, false);
  imprimir_busca_local(res_insercao2, digrafo_problema2); /////////////

  DigrafoMatrizAdj digrafo_problema3(0);
  digrafo_problema3.carregar_de_arquivo_csv("../dados/PROBLEMA_3.csv", true);
  analisar_digrafo(digrafo_problema3, "problema_3", true);
  auto res_vizinho3 = vizinho_mais_proximo(digrafo_problema3, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho3, true);
  imprimir_busca_local(res_vizinho3, digrafo_problema3); /////////////
  auto res_insercao3 = insercao_mais_barata(digrafo_problema3, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao3, true);
  imprimir_busca_local(res_insercao3, digrafo_problema3); /////////////

  DigrafoMatrizAdj digrafo_problema4(0);
  digrafo_problema4.carregar_de_arquivo_csv("../dados/PROBLEMA_4.csv");
  analisar_digrafo(digrafo_problema4, "problema_4");
  auto res_vizinho4 = vizinho_mais_proximo(digrafo_problema4, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho4, false);
  imprimir_busca_local(res_vizinho4, digrafo_problema4); /////////////
  auto res_insercao4 = insercao_mais_barata(digrafo_problema4, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao4, false);
  imprimir_busca_local(res_insercao4, digrafo_problema4); /////////////

  DigrafoMatrizAdj digrafo_problema5(0);
  digrafo_problema5.carregar_de_arquivo_csv("../dados/PROBLEMA_5.csv", true);
  analisar_digrafo(digrafo_problema5, "problema_5", true);
  auto res_vizinho5 = vizinho_mais_proximo(digrafo_problema5, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho5, true);
  imprimir_busca_local(res_vizinho5, digrafo_problema5); /////////////
  auto res_insercao5 = insercao_mais_barata(digrafo_problema5, 0);
  imprimir_busca_local(res_insercao5, digrafo_problema5); /////////////
  imprimir_resultado("Inserção Mais Barata", res_insercao5, true);

  DigrafoMatrizAdj digrafo_problema6(0);
  digrafo_problema6.carregar_de_arquivo_csv("../dados/PROBLEMA_6.csv");
  analisar_digrafo(digrafo_problema6, "problema_6");
  auto res_vizinho6 = vizinho_mais_proximo(digrafo_problema6, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho6, false);
  imprimir_busca_local(res_vizinho6, digrafo_problema6); /////////////
  auto res_insercao6 = insercao_mais_barata(digrafo_problema6, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao6, false);
  imprimir_busca_local(res_insercao6, digrafo_problema6); /////////////

  DigrafoMatrizAdj digrafo_problema7(0);
  digrafo_problema7.carregar_de_arquivo_csv("../dados/PROBLEMA_7.csv", true);
  analisar_digrafo(digrafo_problema7, "problema_7", true);
  auto res_vizinho7 = vizinho_mais_proximo(digrafo_problema7, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho7, true);
  imprimir_busca_local(res_vizinho7, digrafo_problema7); /////////////
  auto res_insercao7 = insercao_mais_barata(digrafo_problema7, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao7, true);
  imprimir_busca_local(res_insercao7, digrafo_problema7); /////////////

  DigrafoMatrizAdj digrafo_problema8(0);
  digrafo_problema8.carregar_de_arquivo_csv("../dados/PROBLEMA_8.csv");
  analisar_digrafo(digrafo_problema8, "problema_8");
  auto res_vizinho8 = vizinho_mais_proximo(digrafo_problema8, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho8, false);
  imprimir_busca_local(res_vizinho8, digrafo_problema8); /////////////
  auto res_insercao8 = insercao_mais_barata(digrafo_problema8, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao8, false);
  imprimir_busca_local(res_insercao8, digrafo_problema8); /////////////

  DigrafoMatrizAdj digrafo_problema9(0);
  digrafo_problema9.carregar_de_arquivo_csv("../dados/PROBLEMA_9.csv", true);
  analisar_digrafo(digrafo_problema9, "problema_9", true);
  auto res_vizinho9 = vizinho_mais_proximo(digrafo_problema9, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho9, true);
  imprimir_busca_local(res_vizinho9, digrafo_problema9); /////////////
  auto res_insercao9 = insercao_mais_barata(digrafo_problema9, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao9, true);
  imprimir_busca_local(res_insercao9, digrafo_problema9); /////////////

  DigrafoMatrizAdj digrafo_problema10(0);
  digrafo_problema10.carregar_de_arquivo_csv("../dados/PROBLEMA_10.csv");
  analisar_digrafo(digrafo_problema10, "problema_10");
  auto res_vizinho10 = vizinho_mais_proximo(digrafo_problema10, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho10, false);
  imprimir_busca_local(res_vizinho10, digrafo_problema10); /////////////
  auto res_insercao10 = insercao_mais_barata(digrafo_problema10, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao10, false);
  imprimir_busca_local(res_insercao10, digrafo_problema10); /////////////

  DigrafoMatrizAdj digrafo_problema11(0);
  digrafo_problema11.carregar_de_arquivo_csv("../dados/PROBLEMA_11.csv", true);
  analisar_digrafo(digrafo_problema11, "problema_11", true);
  auto res_vizinho11 = vizinho_mais_proximo(digrafo_problema11, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho11, true);
  imprimir_busca_local(res_vizinho11, digrafo_problema11); /////////////
  auto res_insercao11 = insercao_mais_barata(digrafo_problema11, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao11, true);
  imprimir_busca_local(res_insercao11, digrafo_problema11); /////////////

  DigrafoMatrizAdj digrafo_problema12(0);
  digrafo_problema12.carregar_de_arquivo_csv("../dados/PROBLEMA_12.csv");
  analisar_digrafo(digrafo_problema12, "problema_12");
  auto res_vizinho12 = vizinho_mais_proximo(digrafo_problema12, 0);
  imprimir_resultado("Vizinho Mais Próximo", res_vizinho12, false);
  imprimir_busca_local(res_vizinho12, digrafo_problema12); /////////////
  auto res_insercao12 = insercao_mais_barata(digrafo_problema12, 0);
  imprimir_resultado("Inserção Mais Barata", res_insercao12, false);
  imprimir_busca_local(res_insercao12, digrafo_problema12); /////////////
}