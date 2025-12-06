#include <iostream>
#include "../../final/headers/DigrafoMatrizAdj.h"
#include "../headers/insercao-mais-barata.h"
#include "../headers/vizinho-mais-proximo.h"
#include "../headers/buscas-locais.h"
#include "../headers/buscas-locais-testes.h"
#include "../headers/algoritmo-genetico.h"

void analisar_digrafo(DigrafoMatrizAdj& grafo, const std::string& nome_arquivo, bool peso_eh_decimal = false) {
    std::cout << "\nAnálise do " << nome_arquivo << std::endl;

    std::cout << "Total de Vertices: " << grafo.get_qtd_vertices() << std::endl;
    std::cout << "Total de Arestas: " << grafo.get_qtd_arestas() << std::endl;
        
    std::string arq_dot =  nome_arquivo + ".dot";
    
    grafo.exportar_para_dot_com_pesos(arq_dot, peso_eh_decimal);
}

void imprimir_resultado(const std::string& nome_algoritmo, 
                        const std::pair<std::vector<int>, int>& resultado, 
                        std::vector<std::string>& rotulos,
                        bool peso_eh_decimal) {
    std::cout << "  >> Algoritmo: " << nome_algoritmo << std::endl;
    
    double custo_formatado = peso_eh_decimal ? (resultado.second / 10.0) : resultado.second;
    
    std::cout << "     Custo Total: " << custo_formatado << std::endl;
    std::cout << "     Rota: [ ";
    for (size_t i = 0; i < resultado.first.size(); ++i) {
        std::cout << rotulos.at(resultado.first[i]);
        if (i < resultado.first.size() - 1) std::cout << " -> ";
    }
    std::cout << " ]\n" << std::endl;
}

void processar_problema(const std::string& caminho_csv, const std::string& nome_problema, bool peso_eh_decimal) {
    DigrafoMatrizAdj digrafo(0);
    digrafo.carregar_de_arquivo_csv(caminho_csv, peso_eh_decimal);
    auto rotulos = digrafo.get_rotulos();

    analisar_digrafo(digrafo, nome_problema, peso_eh_decimal);

    auto res_vizinho = vizinho_mais_proximo(digrafo, 0);
    imprimir_resultado("Vizinho Mais Próximo", res_vizinho, rotulos, peso_eh_decimal);
    imprimir_busca_local(res_vizinho, digrafo);

    auto res_insercao = insercao_mais_barata(digrafo, 0);
    imprimir_resultado("Inserção Mais Barata", res_insercao, rotulos, peso_eh_decimal);
    imprimir_busca_local(res_insercao, digrafo);
    std::cout << "#####################################################################################################################" << std::endl;
}

int main() {
    // processar_problema("../dados/PROBLEMA_1.csv",  "problema_1",  true);
    // processar_problema("../dados/PROBLEMA_2.csv",  "problema_2",  false);
    // processar_problema("../dados/PROBLEMA_3.csv",  "problema_3",  true);
    // processar_problema("../dados/PROBLEMA_4.csv",  "problema_4",  false);
    // processar_problema("../dados/PROBLEMA_5.csv",  "problema_5",  true);
    // processar_problema("../dados/PROBLEMA_6.csv",  "problema_6",  false);
    // processar_problema("../dados/PROBLEMA_7.csv",  "problema_7",  true);
    // processar_problema("../dados/PROBLEMA_8.csv",  "problema_8",  false);
    // processar_problema("../dados/PROBLEMA_9.csv",  "problema_9",  true);
    // processar_problema("../dados/PROBLEMA_10.csv", "problema_10", false);
    // processar_problema("../dados/PROBLEMA_11.csv", "problema_11", true);
    // processar_problema("../dados/PROBLEMA_12.csv", "problema_12", false);

    DigrafoMatrizAdj digrafo(0);
    digrafo.carregar_de_arquivo_csv("../dados/PROBLEMA_1.csv", true);
    auto rotulos = digrafo.get_rotulos();
    AlgoritmoGenetico ag(digrafo);

    auto solucao = ag.executar_algoritmo(
    500, // tamanho_populacao
    0.85, // taxa_reproducao
    0.05, // taxa_mutacao
    1000, // num_geracoes
    450, // num_selecionados_para_cruzamento
    50, // max_geracoes_sem_melhoria
    AlgoritmoGenetico::TipoSelecao::ALEATORIA,
    AlgoritmoGenetico::TipoCruzamento::OX,
    AlgoritmoGenetico::TipoRenovacao::ELITISMO);


    solucao.first.push_back(solucao.first[0]);
    imprimir_resultado("AG", solucao, rotulos, true);

    return 0;
}
