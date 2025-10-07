#ifndef ARVORE_DFS_H
#define ARVORE_DFS_H

#include "arvore_busca.h"

class ArvoreDFS : public ArvoreBusca {

    std::vector<int> tempos_entrada; 
    std::vector<int> tempos_saida;   

public:
    ArvoreDFS(int vertices);

    void set_tempos(int vertice, int entrada, int saida);
    
    void exportar_para_dot(ArvoreDFS arvore, std::string& filename) const;
};

#endif