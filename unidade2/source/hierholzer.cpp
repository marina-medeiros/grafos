#include <stack>
#include <list>
#include <algorithm>

#include "../headers/hierholzer.h"

/**
 * Executa o algoritmo de Hierholzer em um grafo não direcionado.
 * * Verifica a existência de um Ciclo Euleriano (todos os vértices com grau par)
 * ou Caminho Euleriano (exatamente 0 ou 2 vértices com grau ímpar).
 * Utiliza uma pilha para encontrar o circuito e imprime a sequência de vértices visitados.
 * * @param grafo O grafo não direcionado (GrafoListaAdj) a ser analisado.
 * @return void (Imprime o resultado diretamente no console).
 */
void hierholzer_grafo(const GrafoListaAdj& grafo) {
  int V = grafo.get_qtd_vertices();

  // Verifica se o grafo possui caminho euleriano ou ciclo euleriano, e determina vertice inicial

  int contador_vertices_grau_impar = 0;
  int vertice_inicial = -1;
  int primeiro_com_arestas = -1;

  for (int i = 0; i < V; i++) {
    int grau = grafo.get_grau_vertice(i);

    if (grau > 0 && primeiro_com_arestas == -1) {
      primeiro_com_arestas = i;
    }

    if (grau % 2 != 0) {
      contador_vertices_grau_impar++;
      if (vertice_inicial == -1) vertice_inicial = i;
    }
  }

  if (contador_vertices_grau_impar == 0) {
    std::cout << "Existe ciclo euleriano no grafo." << std::endl;
    vertice_inicial = primeiro_com_arestas;
  } else if (contador_vertices_grau_impar <= 2) {
    std::cout << "Existe pelo menos um caminho euleriano no grafo." << std::endl;
  } else {
    std::cout << "Não existe caminho euleriano nem ciclo euleriano no grafo." << std::endl;
    return;
  }

  if (vertice_inicial == -1) {
    std::cout << "O grafo não possui arestas." << std::endl;
    return;
  }

  // Algoritmo de Hierholzer

  std::map<int, std::list<int>> adj_copia;
  for (int i = 0; i < V; ++i) {
    adj_copia[i] = grafo.get_vizinhos(i); 
  }

  std::stack<int> P;
  std::list<int> L;
  int u = vertice_inicial;

  while ((!P.empty() || !adj_copia[u].empty())) {
    if (!adj_copia[u].empty()) {
      P.push(u);
      int v = adj_copia[u].front();
      adj_copia[u].pop_front();

      auto& vizinhos_v = adj_copia[v];
      auto it = std::find(vizinhos_v.begin(), vizinhos_v.end(), u);
      if (it != vizinhos_v.end()) {
        vizinhos_v.erase(it);
      }

      u = v;
    } else {
      L.push_front(u);
      if (!P.empty()) {
        u = P.top();
        P.pop();
      }
    }
  }

  L.push_front(u);

  std::cout << "Resultado: ";

  auto rotulos_grafo = grafo.get_rotulos();
  bool primeiro = true;
  for (int v : L) {
      if (!primeiro) {
          std::cout << " -> ";
      }
      std::cout << rotulos_grafo.at(v);
      primeiro = false;
  }
  std::cout << std::endl;
}

/**
 * Executa o algoritmo de Hierholzer em um digrafo (grafo direcionado).
 * * Verifica a conectividade e o balanceamento dos graus de entrada e saída para determinar
 * a existência de Ciclo Euleriano (todos graus in == out) ou Caminho Euleriano 
 * (um vértice com out = in + 1, um com in = out + 1, e o restante iguais).
 * * @param digrafo O digrafo (DigrafoListaAdj) a ser analisado.
 * @return void (Imprime o resultado diretamente no console).
 */
void hierholzer_digrafo(const DigrafoListaAdj& digrafo) {
  int V = digrafo.get_qtd_vertices();

  // Verifica se o digrafo possui caminho euleriano ou ciclo euleriano, e determina vertice inicial

  int contador_vertices_entrada_menos_saida_igual_a_um = 0;
  int contador_vertices_saida_menos_entrada_igual_a_um = 0;
  int contador_vertices_grau_inadequado = 0; // Qualquer grau diferente de -1, 0 ou 1

  int vertice_inicial = -1;
  int primeiro_com_arestas = -1;

  for (int i = 0; i < V; i++) {
    int grau_de_entrada = digrafo.get_grau_entrada(i);
    int grau_de_saida = digrafo.get_grau_saida(i);

    if (grau_de_saida > 0 && primeiro_com_arestas == -1) {
      primeiro_com_arestas = i;
    }

    if (grau_de_entrada == grau_de_saida) {
      continue;
    } else if ((grau_de_entrada - grau_de_saida) == 1) {
      contador_vertices_entrada_menos_saida_igual_a_um++;
    } else if ((grau_de_saida - grau_de_entrada) == 1) {
      contador_vertices_saida_menos_entrada_igual_a_um++;
      vertice_inicial = i;
    } else {
      contador_vertices_grau_inadequado++;
    }
  }

  if (contador_vertices_grau_inadequado > 0) {
    std::cout << "Não existe caminho euleriano nem ciclo euleriano no digrafo." << std::endl;
    return;
  }
  
  if (contador_vertices_entrada_menos_saida_igual_a_um == 0 &&
      contador_vertices_saida_menos_entrada_igual_a_um == 0) {
    std::cout << "Existe ciclo euleriano no digrafo." << std::endl;
    vertice_inicial = primeiro_com_arestas;
  } else if (contador_vertices_entrada_menos_saida_igual_a_um == 1 &&
            contador_vertices_saida_menos_entrada_igual_a_um == 1) {
    std::cout << "Existe caminho euleriano no digrafo." << std::endl;
  } else {
    std::cout << "Não existe caminho euleriano nem ciclo euleriano no digrafo." << std::endl;
    return;
  }

  if (vertice_inicial == -1) {
    std::cout << "O digrafo não possui arestas." << std::endl;
    return;
  }

  // Algoritmo de Hierholzer

  std::map<int, std::list<int>> adj_copia;
  for (int i = 0; i < V; ++i) {
    adj_copia[i] = digrafo.get_vizinhos(i); 
  }

  std::stack<int> P;
  std::list<int> L;
  int u = vertice_inicial;

  while ((!P.empty() || !adj_copia[u].empty())) {
    if (!adj_copia[u].empty()) {
      P.push(u);
      int v = adj_copia[u].front();
      adj_copia[u].pop_front();

      u = v;
    } else {
      L.push_front(u);
      if (!P.empty()) {
        u = P.top();
        P.pop();
      }
    }
  }

  L.push_front(u);

  std::cout << "Resultado: ";

  auto rotulos_digrafo = digrafo.get_rotulos();
  bool primeiro = true;
  for (int v : L) {
      if (!primeiro) {
          std::cout << " -> ";
      }
      std::cout << rotulos_digrafo.at(v);
      primeiro = false;
  }
  std::cout << std::endl;
}
