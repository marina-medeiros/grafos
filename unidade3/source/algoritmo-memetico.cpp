#include "../headers/algoritmo-memetico.h"
#include <iostream>

void AlgoritmoMemetico::aplicar_busca_local_nos_filhos(
    std::vector<std::pair<std::vector<int>, int>>& filhos, 
    int tipo_busca, 
    int heuristica) {
    for (auto& filho : filhos) {
        std::pair<std::vector<int>, int> resultado = busca_local(filho, tipo_busca, heuristica, this->grafo);
        
        filho = resultado;
    }
}

std::pair<std::vector<int>, int> AlgoritmoMemetico::executar_com_busca_local(int tamanho_populacao, double taxa_reproducao, double taxa_mutacao, int num_geracoes,
                                                                                int num_selecionados_para_cruzamento, int max_geracoes_sem_melhoria,
                                                                                TipoSelecao tipo_selecao, TipoCruzamento tipo_cruzamento, TipoRenovacao tipo_renovacao,
                                                                                int tipo_busca_local, int heuristica_busca) {
    this->gerar_e_avaliar_populacao_inicial(tamanho_populacao);
                    
    auto melhor_solucao_global = this->obter_melhor_solucao();
    int geracoes_sem_melhoria = 0;
    int geracao_atual = 0;

    while (geracao_atual < num_geracoes && geracoes_sem_melhoria < max_geracoes_sem_melhoria) {
        geracao_atual++;
        auto pais = this->selecionar_populacao(num_selecionados_para_cruzamento, tipo_selecao);
        auto filhos = this->realizar_cruzamento(pais, taxa_reproducao, tipo_cruzamento);
        this->aplicar_mutacao(filhos, taxa_mutacao);
        this->aplicar_busca_local_nos_filhos(filhos, tipo_busca_local, heuristica_busca);
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