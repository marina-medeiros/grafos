#include <iostream>
#include <vector>
#include <utility> // std::pair

// Pensei em usar listas, mas elas não permitem o acesso aleatório

class Estrela {
    std::vector<int> pesos;
    std::vector<std::pair<int, int>> inicio_fim;
    std::vector<int> pont;

    public:
    Estrela(const std::vector<std::vector<int>>& matriz_adj) {
        gerar_estrela(matriz_adj);
    }

    void gerar_estrela(std::vector<std::vector<int>> matriz_adj);

    void imprimir_estrela();
};