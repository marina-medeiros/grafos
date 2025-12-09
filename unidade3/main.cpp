#include <iostream>
#include <string>
#include <chrono>
#include <numeric>
#include <vector>
#include <utility>
#include <iomanip>
#include <fstream>
#include "../../final/headers/DigrafoMatrizAdj.h"
#include "../headers/insercao-mais-barata.h"
#include "../headers/vizinho-mais-proximo.h"
#include "../headers/buscas-locais.h"
#include "../headers/buscas-locais-testes.h"
#include "../headers/algoritmo-genetico.h"
#include "../headers/algoritmo-memetico.h"

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

struct Estatisticas {
    double melhor_valor;
    double media_valor;
    double tempo_medio_ms;
    std::pair<std::vector<int>, int> melhor_solucao;
};


void rodar_heuristicas_deterministicas_sep(DigrafoMatrizAdj& grafo, const std::string& nome_prob, bool decimal, std::ofstream& arquivo) {
    double div = decimal ? 10.0 : 1.0;

    auto inicio_vp = std::chrono::high_resolution_clock::now();
    
    auto solucao_vp = vizinho_mais_proximo(grafo, 0); 
    solucao_vp = busca_local(solucao_vp, 2, 1, grafo); 
    
    auto fim_vp = std::chrono::high_resolution_clock::now();
    long long tempo_vp = std::chrono::duration_cast<std::chrono::milliseconds>(fim_vp - inicio_vp).count();

    auto inicio_ib = std::chrono::high_resolution_clock::now();
    
    auto solucao_ib = insercao_mais_barata(grafo, 0); 
    solucao_ib = busca_local(solucao_ib, 2, 1, grafo);
    
    auto fim_ib = std::chrono::high_resolution_clock::now();
    long long tempo_ib = std::chrono::duration_cast<std::chrono::milliseconds>(fim_ib - inicio_ib).count();

    arquivo << std::left  << std::setw(15) << nome_prob << " | "
            << std::left  << std::setw(20) << "Vizinho+2Opt" << " | "
            << std::right << std::setw(12) << (solucao_vp.second / div) << " | "
            << std::right << std::setw(10) << tempo_vp << "\n";

    arquivo << std::left  << std::setw(15) << nome_prob << " | "
            << std::left  << std::setw(20) << "Insercao+2Opt" << " | "
            << std::right << std::setw(12) << (solucao_ib.second / div) << " | "
            << std::right << std::setw(10) << tempo_ib << "\n";
            
    arquivo << std::string(67, '-') << "\n";
    arquivo.flush();
}

void imprimir_linha_tabela(std::ofstream& arquivo, 
                           const std::string& instancia, 
                           const std::string& algoritmo, 
                           double melhor, 
                           double media, 
                           long long tempo) {
    
    arquivo << std::left  << std::setw(15) << instancia << " | "
            << std::left  << std::setw(20) << algoritmo << " | "
            << std::right << std::setw(12) << melhor    << " | "
            << std::right << std::setw(12) << media     << " | "
            << std::right << std::setw(10) << tempo     << "\n";
}

void rodar_heuristicas_deterministicas(DigrafoMatrizAdj& grafo, const std::string& nome_prob, bool decimal, std::ofstream& arquivo) {
    double div = decimal ? 10.0 : 1.0;

    auto inicio_vp = std::chrono::high_resolution_clock::now();
    auto solucao_vp = vizinho_mais_proximo(grafo, 0); 
    solucao_vp = busca_local(solucao_vp, 2, 1, grafo); 
    auto fim_vp = std::chrono::high_resolution_clock::now();
    long long tempo_vp = std::chrono::duration_cast<std::chrono::milliseconds>(fim_vp - inicio_vp).count();

    imprimir_linha_tabela(arquivo, nome_prob, "Vizinho+2Opt", solucao_vp.second / div, solucao_vp.second / div, tempo_vp);

    auto inicio_ib = std::chrono::high_resolution_clock::now();
    auto solucao_ib = insercao_mais_barata(grafo, 0); 
    solucao_ib = busca_local(solucao_ib, 2, 1, grafo);
    auto fim_ib = std::chrono::high_resolution_clock::now();
    long long tempo_ib = std::chrono::duration_cast<std::chrono::milliseconds>(fim_ib - inicio_ib).count();

    imprimir_linha_tabela(arquivo, nome_prob, "Insercao+2Opt", solucao_ib.second / div, solucao_ib.second / div, tempo_ib);
}

Estatisticas executar_bateria_testes(
    DigrafoMatrizAdj& grafo, 
    bool usar_memetico, 
    bool peso_eh_decimal,
    const std::string& nome_instancia) {
    std::vector<double> custos;
    std::vector<long long> tempos;
    std::pair<std::vector<int>, int> melhor_global = {{}, 999999999};

    std::cout << "\n--- Iniciando Bateria de 20 Execucoes: " 
              << (usar_memetico ? "MEMETICO" : "GENETICO") 
              << " [" << nome_instancia << "] ---\n";
    
    int POP_SIZE = 500;
    double TAXA_REP = 0.85;
    double TAXA_MUT = 0.05;
    int MAX_GEN = 1000;
    int ELITE_COUNT = 450;
    int PATIENCE = 50;


    for (int i = 0; i < 20; ++i) {
        auto inicio = std::chrono::high_resolution_clock::now();
        
        std::pair<std::vector<int>, int> solucao;

        if (usar_memetico) {
            AlgoritmoMemetico am(grafo);
            solucao = am.executar_com_busca_local(
                POP_SIZE, TAXA_REP, TAXA_MUT, MAX_GEN, ELITE_COUNT, PATIENCE,
                AlgoritmoGenetico::TipoSelecao::ALEATORIA,
                AlgoritmoGenetico::TipoCruzamento::OX,
                AlgoritmoGenetico::TipoRenovacao::ELITISMO);
        } else {
            AlgoritmoGenetico ag(grafo);
            solucao = ag.executar_algoritmo(
                POP_SIZE, TAXA_REP, TAXA_MUT, MAX_GEN, ELITE_COUNT, PATIENCE,
                AlgoritmoGenetico::TipoSelecao::ALEATORIA,
                AlgoritmoGenetico::TipoCruzamento::OX,
                AlgoritmoGenetico::TipoRenovacao::ELITISMO
            );
        }

        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = std::chrono::duration_cast<std::chrono::milliseconds>(fim - inicio).count();
 
        double custo_real = peso_eh_decimal ? (solucao.second / 10.0) : solucao.second;
        
        custos.push_back(custo_real);
        tempos.push_back(duracao);

        if (solucao.second < melhor_global.second) {
            melhor_global = solucao;
        }

        std::cout << "Exec " << (i+1) << ": " << custo_real << " (" << duracao << "ms)" << std::endl;
    }

    double soma_custos = std::accumulate(custos.begin(), custos.end(), 0.0);
    double soma_tempos = std::accumulate(tempos.begin(), tempos.end(), 0.0);
    
    if (melhor_global.first.empty()) melhor_global.second = 0; 

    Estatisticas stats;
    stats.melhor_valor = peso_eh_decimal ? (melhor_global.second / 10.0) : melhor_global.second;
    stats.media_valor = soma_custos / 20.0;
    stats.tempo_medio_ms = soma_tempos / 20.0;
    stats.melhor_solucao = melhor_global;

    return stats;
}

int main() {
     

    struct Instancia {
        std::string caminho;
        std::string nome;
        bool decimal;
    };

    std::vector<Instancia> problemas = {
        {"../dados/PROBLEMA_1.csv", "Problema 1", true},
        {"../dados/PROBLEMA_2.csv", "problema_2", false},
        {"../dados/PROBLEMA_3.csv", "problema_3", true},
        {"../dados/PROBLEMA_4.csv", "problema_4", false},
        {"../dados/PROBLEMA_5.csv", "problema_5", true},
        {"../dados/PROBLEMA_6.csv", "problema_6", false},
        {"../dados/PROBLEMA_7.csv", "problema_7", true},
        {"../dados/PROBLEMA_8.csv", "problema_8", false},
        {"../dados/PROBLEMA_9.csv", "problema_9", true},
        {"../dados/PROBLEMA_10.csv", "problema_10", false},
        {"../dados/PROBLEMA_11.csv", "problema_11", true},
        {"../dados/PROBLEMA_12.csv", "problema_12", false}
    };

    std::ofstream arquivo_evolutivo("resultados_evolutivos.txt");
    std::ofstream arquivo_heuristicas("resultados_heuristicas.txt");
    std::ofstream arquivo_final("resultados_finais.txt");
    if (!arquivo_evolutivo.is_open()|| !arquivo_heuristicas.is_open() || !arquivo_final.is_open()) {
        std::cerr << "Erro ao abrir arquivos de saida!" << std::endl;
        return 1;
    }

    arquivo_evolutivo << std::left;

    arquivo_evolutivo << std::setw(15) << "Instancia" << " | "
                      << std::setw(12) << "Algoritmo" << " | "
                      << std::setw(15) << "Melhor"    << " | "
                      << std::setw(15) << "Media"     << " | "
                      << std::setw(12) << "Tempo(ms)" << "\n";

    arquivo_evolutivo << std::string(82, '-') << "\n";
    arquivo_evolutivo << std::fixed << std::setprecision(2);

    arquivo_heuristicas << std::left  << std::setw(15) << "Instancia" << " | "
                        << std::left  << std::setw(20) << "Heuristica" << " | "
                        << std::right << std::setw(12) << "Custo"      << " | "
                        << std::right << std::setw(10) << "Tempo(ms)"  << "\n";
    arquivo_heuristicas << std::string(67, '-') << "\n";
    arquivo_heuristicas << std::fixed << std::setprecision(2);

    arquivo_final << std::left  << std::setw(15) << "Instancia" << " | "
            << std::left  << std::setw(20) << "Algoritmo" << " | "
            << std::right << std::setw(12) << "Melhor"    << " | "
            << std::right << std::setw(12) << "Media"     << " | "
            << std::right << std::setw(10) << "Tempo(ms)" << "\n";
    
    arquivo_final << std::string(82, '-') << "\n";
    arquivo_final << std::fixed << std::setprecision(2);

    for (const auto& prob : problemas) {
        DigrafoMatrizAdj digrafo(0);
        digrafo.carregar_de_arquivo_csv(prob.caminho, prob.decimal);
        double div = prob.decimal ? 10.0 : 1.0;

        rodar_heuristicas_deterministicas_sep(digrafo, prob.nome, prob.decimal, arquivo_heuristicas);
        rodar_heuristicas_deterministicas(digrafo, prob.nome, prob.decimal, arquivo_final);
        
        Estatisticas statsAG = executar_bateria_testes(digrafo, false, prob.decimal, prob.nome);
        imprimir_linha_tabela(arquivo_final, prob.nome, "Genetico", 
                              statsAG.melhor_valor / div, 
                              statsAG.media_valor / div, 
                              statsAG.tempo_medio_ms);
        imprimir_linha_tabela(arquivo_evolutivo, prob.nome, "Genetico", 
                              statsAG.melhor_valor / div, 
                              statsAG.media_valor / div, 
                              statsAG.tempo_medio_ms);

        Estatisticas statsAM = executar_bateria_testes(digrafo, true, prob.decimal, prob.nome);
        imprimir_linha_tabela(arquivo_final, prob.nome, "Memetico", 
                              statsAM.melhor_valor / div, 
                              statsAM.media_valor / div, 
                              statsAM.tempo_medio_ms);
        imprimir_linha_tabela(arquivo_evolutivo, prob.nome, "Genetico", 
                              statsAG.melhor_valor / div, 
                              statsAG.media_valor / div, 
                              statsAG.tempo_medio_ms);
        
        arquivo_final << std::string(82, '-') << "\n";
        
        arquivo_final.flush(); 
    }

    arquivo_evolutivo.close();
    arquivo_heuristicas.close();
    arquivo_final.close();
    std::cout << "\nProcessamento finalizado. Verifique 'resultados_evolutivos.txt' e 'resultados_heuristicas.txt' e 'resultados_finais'." << std::endl;

    return 0;
}

