#include <queue>
#include <vector>

#include "../headers/Grafo.h"
#include "../headers/busca-largura.h"

bool busca_largura_colorida_grafo(const Grafo& grafo, int vertice_inicial, std::vector<int>& cores) {
    std::queue<int> fila;

    cores[vertice_inicial] = 1;
    fila.push(vertice_inicial);

    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();

        // Itera sobre os vértices adjacentes
        for (int v : grafo.get_vizinhos(u)) {
            // Se o adjacente 'v' ainda não foi colorido
            if (cores[v] == 0) {
                // Vértice adjacente recebe cor oposta
                cores[v] = -cores[u];
                fila.push(v);
            }
            // Se vértices adjacentes tiverem a mesma cor, então não é bipartido
            else if (cores[v] == cores[u]) {
                return false;
            }
        }
    }

    return true;
}