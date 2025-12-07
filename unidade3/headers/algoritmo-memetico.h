#ifndef ALGORITMO_MEMETICO_H
#define ALGORITMO_MEMETICO_H

#include "algoritmo-genetico.h"
#include "buscas-locais.h"

class AlgoritmoMemetico : public AlgoritmoGenetico {
  public:
    AlgoritmoMemetico(const DigrafoMatrizAdj& g) : AlgoritmoGenetico(g) {}

    std::pair<std::vector<int>, int> executar_com_busca_local(
        int tamanho_populacao, double taxa_reproducao, double taxa_mutacao, int num_geracoes,
        int num_selecionados_para_cruzamento, int max_geracoes_sem_melhoria,
        TipoSelecao tipo_selecao, TipoCruzamento tipo_cruzamento, TipoRenovacao tipo_renovacao);

  private:
    void aplicar_busca_local_nos_filhos(
        std::vector<std::pair<std::vector<int>, int>>& filhos);
};

#endif