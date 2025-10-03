#ifndef DIGRAFO_H
#define DIGRAFO_H

#include "grafo.h"

class Digrafo : public Grafo {
public:
    Digrafo(int vertices) : Grafo(vertices) {}
    void inserir_aresta(int u, int v, int peso) override;
    void remover_aresta(int u, int v) override;
    void gerar_matriz_inc() override;
    void exportar_para_dot(const std::string& filename) override;
};

#endif