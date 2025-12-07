#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <limits>
#include <set>
#include <algorithm>
#include <numeric>
#include "../headers/DigrafoListaAdjPonderada.h"

/**
 * @brief Estrutura auxiliar para representar uma aresta ponderada.
 *
 * Armazena a origem, destino e peso de uma aresta.
 * Criada para facilitar maninupalacao interna, sem necessitar acessar e modificar a estrutura do grafo principal
 *
 * Inicializa a aresta com um peso infinito (max_int)
 */
struct Aresta {
    int origem, destino, peso;
    Aresta(int u = -1, int v = -1, int p = std::numeric_limits<int>::max())
        : origem(u), destino(v), peso(p) {}
};

using MapaArestas = std::map<std::pair<int, int>, std::pair<int, int>>;

/**
 * @brief Detecta um ciclo no grafo formado pelas arestas de menor custo.
 *
 * Se um nó já visitado na chamada atual for encontrado, um ciclo é
 * identificado e seus nós são retornados.
 *
 * @param aresta_min Vetor com a aresta de entrada de menor custo para cada nó.
 * @param raiz O nó raiz
 * @param n O número total de vértices.
 * @return Uma lista com os nós do ciclo, ou uma lista vazia se não houver ciclo.
 */
static std::list<int> detetar_ciclo(const std::vector<Aresta>& aresta_min, int raiz, int n) {
    std::vector<int> visitado(n, -1);
    int visita_atual = 0;

    for (int i = 0; i < n; ++i) {
        if (i == raiz || visitado[i] == -2) continue;

        int atual = i;
        visita_atual++;

        while (atual != -1 && atual != raiz) {
            if (visitado[atual] == visita_atual) {
                std::list<int> ciclo;
                int no_ciclo = atual;
                do {
                    ciclo.push_back(no_ciclo);
                    no_ciclo = aresta_min[no_ciclo].origem;
                } while (no_ciclo != atual);
                return ciclo;
            }
            if (visitado[atual] == -2) break;
            visitado[atual] = visita_atual;
            atual = aresta_min[atual].origem;
        }
        atual = i;
        while (atual != -1 && atual != raiz && visitado[atual] == visita_atual) {
            visitado[atual] = -2;
            atual = aresta_min[atual].origem;
        }
    }
    return {}; 
}

/**
 * @brief Função recursiva que implementa a lógica central de Chu-Liu/Edmonds.
 *
 * Executa os passos:
 * 1. encontra o conjunto de arestas de entrada de menor custo.
 * 2. verifica se este conjunto forma um ciclo.
 * 3. se não houver ciclo, retorna o conjunto como a arborescencia.
 * 4. se houver ciclo (passo recursivo), contrai o ciclo, recalculando os pesos, e chama a recursão sobre o grafo contraído.
 * 5. expande a arborescencia resultante para formar o resultado final.
 *
 * @param digrafo O grafo que será processado.
 * @param raiz O nó raiz para essa iteração.
 * @param arestas_contraidas Mapa que rastreia a correspondencia entre arestas contraídas e originais.
 * @return Uma lista de Aresta (auxiliar) representando a arborescencia.
 */
static std::list<Aresta> chu_liu_recursivo(const DigrafoListaAdjPonderada& digrafo, int raiz, MapaArestas& arestas_contraidas) {
    int n = digrafo.get_qtd_vertices();
    if (n <= 0) return {};

    std::map<int, std::list<Aresta>> arestas_de_entrada;
    for (int i = 0; i < n; ++i) {
        for (const auto& par : digrafo.get_arestas_saindo(i)) {
            arestas_de_entrada[par.first].push_back(Aresta(i, par.first, par.second));
        }
    }

    std::vector<Aresta> aresta_min(n);
    for (int j = 0; j < n; ++j) {
        if (j == raiz) continue;
        for (const auto& aresta : arestas_de_entrada[j]) {
            if (aresta.peso < aresta_min[j].peso) {
                aresta_min[j] = aresta;
            }
        }
        if (aresta_min[j].origem == -1) {
            return {};
        }
    }

    std::list<int> ciclo = detetar_ciclo(aresta_min, raiz, n);

    if (ciclo.empty()) {
        std::list<Aresta> arvore;
        for (int k = 0; k < n; ++k) {
            if (k != raiz) arvore.push_back(aresta_min[k]);
        }
        return arvore;
    }

    int custo_min = std::numeric_limits<int>::max();
    for (int k : ciclo) {
        custo_min = std::min(custo_min, aresta_min[k].peso);
    }

    int num_contraido = n - ciclo.size() + 1;
    int temp = num_contraido - 1;
    DigrafoListaAdjPonderada digrafo_contraido(num_contraido);
    
    std::map<int, int> nos;
    std::set<int> nos_ciclo(ciclo.begin(), ciclo.end());
    int id = 0;
    for (int i = 0; i < n; ++i) {
        if (nos_ciclo.count(i)) {
            nos[i] = temp;
        } else {
            if(id == temp) id++; 
            nos[i] = id++;
        }    
    }
    raiz = nos[raiz];

    for (int i = 0; i < n; ++i) {
        for (const auto& par : digrafo.get_arestas_saindo(i)) {
            int u = par.first;
            int peso_original = par.second;
            int novo_i = nos[i];
            int novo_u = nos[u];

            if (novo_i == novo_u) continue;
            if (novo_u == temp) { 
                int novo_peso = peso_original - (aresta_min[u].peso - custo_min);
                if (!digrafo_contraido.existe_aresta(novo_i, novo_u) || novo_peso < digrafo_contraido.get_peso(novo_i, novo_u)) {
                    digrafo_contraido.remover_aresta(novo_i, novo_u); 
                    digrafo_contraido.inserir_aresta(novo_i, novo_u, novo_peso);
                    arestas_contraidas[{novo_i, novo_u}] = {i, u}; 
                }
            } else { 
               if (!digrafo_contraido.existe_aresta(novo_i, novo_u) || peso_original < digrafo_contraido.get_peso(novo_i, novo_u)) {
                    digrafo_contraido.remover_aresta(novo_i, novo_u);
                    digrafo_contraido.inserir_aresta(novo_i, novo_u, peso_original);
                    arestas_contraidas[{novo_i, novo_u}] = {i, u};
                }
            }
        }
    }
    std::list<Aresta> arvore_contraida = chu_liu_recursivo(digrafo_contraido, raiz, arestas_contraidas);
    std::list<Aresta> arvore;
    Aresta aresta_entrada;

    for (const auto& aresta : arvore_contraida) {
        if (arestas_contraidas.find({aresta.origem, aresta.destino}) == arestas_contraidas.end()) {
             continue;
        }
        auto par_original = arestas_contraidas.at({aresta.origem, aresta.destino});
        Aresta aresta_original(par_original.first, par_original.second, digrafo.get_peso(par_original.first, par_original.second));
        arvore.push_back(aresta_original);
        if (nos_ciclo.count(aresta_original.destino)) {
            aresta_entrada = aresta_original;
        }
    }

    for (int c : ciclo) {
        if (aresta_min[c].destino != aresta_entrada.destino) {
            arvore.push_back(aresta_min[c]);
        }
    }
    return arvore;
}

/**
 * @brief Função responsável por inicializar o processo
 *
 * Inicializa o processo, chamando a função 'chu_liu_recursivo' para
 * obter a lista de arestas, depois constrói o grafo da (AGM) a partir dessa lista.
 *
 * A função também imprime o resultado (arestas e custo total) no console.
 *
 * @param grafo O digrafo ponderado de entrada.
 * @param raiz O índice do nó de origem (raiz) da arborescência.
 * @return Um novo 'DigrafoListaAdjPonderada' contendo a arborescência.
 * Retorna um grafo vazio se nenhuma arborescência for encontrada.
 */
DigrafoListaAdjPonderada chu_liu(const DigrafoListaAdjPonderada& grafo, int raiz) {

    DigrafoListaAdjPonderada agm(grafo.get_qtd_vertices());
    std::cout << "Executando Chu-Liu/Edmonds, origem " << raiz+1 << "..." << std::endl;

    if (raiz < 0 || raiz >= grafo.get_qtd_vertices()) {
        std::cerr << "Erro: Vértice de origem " << raiz+1 << " fora do intervalo." << std::endl;
        return agm;
    }

    MapaArestas mapa_arestas;
    std::list<Aresta> arestas_agm = chu_liu_recursivo(grafo, raiz, mapa_arestas);

    if (arestas_agm.empty() || arestas_agm.size() != (grafo.get_qtd_vertices() - 1)) {
        std::cout << "RESULTADO: Nao foi encontrada uma arborescencia geradora.\n" << std::endl;
        return agm;
    } else {
        std::cout << "\n--- AGM Encontrada ---\n";

        int custo = 0;
        for (const auto& aresta : arestas_agm) {
            std::cout << "  (" << aresta.origem+1 << " -> " << aresta.destino+1 << ") com peso: " << aresta.peso << std::endl;
            custo += aresta.peso;
            agm.inserir_aresta(aresta.origem, aresta.destino, aresta.peso);
        }

        std::cout << "------------------------------------------------\n";
        std::cout << "Custo Total: " << custo << std::endl << std::endl;
    }
    return agm;
}