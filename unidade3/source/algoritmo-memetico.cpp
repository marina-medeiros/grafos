#include "../headers/algoritmo-memetico.h"
#include <iostream>

/**
 * @brief Aplica busca local em soluções filhas com uma certa probabilidade.
 * Utiliza estratégias e heurísticas aleatórias para diversificar a busca.
 * @param filhos Vetor de soluções filhas a serem aprimoradas.
 */
void AlgoritmoMemetico::aplicar_busca_local_nos_filhos(std::vector<std::pair<std::vector<int>, int>>& filhos) {
    std::uniform_real_distribution<double> dist_prob(0.0, 1.0);
    double chance_busca = 0.10; 
    std::uniform_int_distribution<int> dist_tipo(1, 3); 
    std::uniform_int_distribution<int> dist_heuristica(1, 2);

    for (auto& filho : filhos) {
        if (dist_prob(this->gerador_aleatorio) < chance_busca) {
            int tipo_escolhido = dist_tipo(this->gerador_aleatorio);
            int heuristica_escolhida = dist_heuristica(this->gerador_aleatorio);
            std::pair<std::vector<int>, int> resultado = busca_local(
                filho, 
                tipo_escolhido, 
                heuristica_escolhida, 
                this->grafo
            );
            
            if (resultado.second < filho.second) {
                filho = resultado;
            }
        }
    }
}

/**
 * @brief Executa o algoritmo memético completo com busca local.
 * Inclui etapas de geração inicial, seleção, cruzamento, mutação, busca local e renovação.
 * @param tamanho_populacao Tamanho da população inicial.
 * @param taxa_reproducao Taxa de reprodução para cruzamento.
 * @param taxa_mutacao Taxa de mutação para soluções filhas.
 * @param num_geracoes Número máximo de gerações a serem executadas.
 * @param num_selecionados_para_cruzamento Número de soluções selecionadas para cruzamento.
 * @param max_geracoes_sem_melhoria Número máximo de gerações sem melhoria antes de parar.
 * @param tipo_selecao Tipo de seleção a ser utilizada (TORNEIO, ELITISMO, ALEATORIA).
 * @param tipo_cruzamento Tipo de cruzamento a ser utilizado (UM_X, OX).
 * @param tipo_renovacao Tipo de renovação a ser utilizada (TORNEIO, ELITISMO).
 * @return std::pair<std::vector<int>, int> Melhor solução encontrada (ordem de vértices e custo).
 */
std::pair<std::vector<int>, int> AlgoritmoMemetico::executar_com_busca_local(int tamanho_populacao, double taxa_reproducao, double taxa_mutacao, int num_geracoes,
                                                                                int num_selecionados_para_cruzamento, int max_geracoes_sem_melhoria,
                                                                                TipoSelecao tipo_selecao, TipoCruzamento tipo_cruzamento, TipoRenovacao tipo_renovacao) {
    this->gerar_e_avaliar_populacao_inicial(tamanho_populacao);
                    
    auto melhor_solucao_global = this->obter_melhor_solucao();
    int geracoes_sem_melhoria = 0;
    int geracao_atual = 0;

    while (geracao_atual < num_geracoes && geracoes_sem_melhoria < max_geracoes_sem_melhoria) {
        geracao_atual++;
        auto pais = this->selecionar_populacao(num_selecionados_para_cruzamento, tipo_selecao);
        auto filhos = this->realizar_cruzamento(pais, taxa_reproducao, tipo_cruzamento);
        this->aplicar_mutacao(filhos, taxa_mutacao);
        this->aplicar_busca_local_nos_filhos(filhos);
        this->renovar_populacao(filhos, tipo_renovacao);

        auto melhor_da_geracao = this->obter_melhor_solucao();

        if (melhor_da_geracao.second < melhor_solucao_global.second) {
            melhor_solucao_global = melhor_da_geracao;
            geracoes_sem_melhoria = 0;
            //std::cout << "Melhoria na geracao " << geracao_atual << ": " << melhor_solucao_global.second << std::endl;
        } else {
            geracoes_sem_melhoria++;
        }
    }
    return melhor_solucao_global;
}