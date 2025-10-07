#ifndef ARVORE_BFS_H
#define ARVORE_BFS_H

#include "arvore_busca.h"

class ArvoreBFS : public ArvoreBusca {
    std::vector<int> niveis; 

public:
    ArvoreBFS(int vertices);

    void set_nivel(int vertice, int nivel_v){
        this->niveis[vertice] = nivel_v;
    }
    int get_nivel(int vertice){
        return this->niveis[vertice];
    }

    void exportar_para_dot(std::string& filename) const;
};

#endif