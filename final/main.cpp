#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>   
#include <algorithm>
#include <limits>

#include "headers/grafo.h"
#include "headers/digrafo.h"
#include "headers/arvore_bfs.h"

void menu(); 
std::unique_ptr<Grafo> loadFile(const std::string& nome_arquivo);
void grafo(Grafo& grafo_simples, const std::string& nome_base);
void digrafo(Digrafo& grafo_direcionado, const std::string& nome_base);

int main(){

    const std::map<std::string, std::string> arquivos = {
        {"1", "GRAFO_0.txt"}, {"grafo_0", "GRAFO_0.txt"},
        {"2", "GRAFO_1.txt"}, {"grafo_1", "GRAFO_1.txt"},
        {"3", "GRAFO_2.txt"}, {"grafo_2", "GRAFO_2.txt"},
        {"4", "GRAFO_3.txt"}, {"grafo_3", "GRAFO_3.txt"},
        {"5", "DIGRAFO_0.txt"}, {"digrafo_0", "DIGRAFO_0.txt"},
        {"6", "DIGRAFO_1.txt"}, {"digrafo_1", "DIGRAFO_1.txt"},
        {"7", "DIGRAFO_2.txt"}, {"digrafo_2", "DIGRAFO_2.txt"},
        {"8", "DIGRAFO_3.txt"}, {"digrafo_3", "DIGRAFO_3.txt"}
    };

    while (true) {
        menu();
        std::string entrada;
        std::cin >> entrada;

        std::transform(entrada.begin(), entrada.end(), entrada.begin(), ::tolower);

        if (entrada == "sair" || entrada == "s") {
            break;
        }

        auto it = arquivos.find(entrada);
        if (it == arquivos.end()) {
            std::cout << "\nOpção inválida. Tente novamente.\n" << std::endl;
            continue;
        }

        std::string nome_arquivo = it->second;
        std::string caminho_completo = "../dados/" + nome_arquivo;

        std::cout << "\nAnalisando o arquivo: " << caminho_completo << "...\n" << std::endl;

        auto ptr_grafo = loadFile(caminho_completo);

        if (!ptr_grafo) {
            std::cout << "Erro ao carregar o arquivo " << nome_arquivo << std::endl;
            continue;
        }

        // dynamic_cast para identificar se grafo ou digrafo
        Digrafo* d_ptr = dynamic_cast<Digrafo*>(ptr_grafo.get());
        
        std::string nome_base = nome_arquivo.substr(0, nome_arquivo.find("."));

        if (d_ptr) {
            //se digrafo
            digrafo(*d_ptr, nome_base);
        } else {
            //se grafo
            grafo(*ptr_grafo, nome_base);
        }
        
        std::cout << "\nAnálise concluída. Pressione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    return 0;

}

void grafo(Grafo& grafo_simples, const std::string& nome_base){

    std::cout << "----------- GRAFO NÃO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    std::string nome_dot = nome_base + ".dot";
    std::string nome_png = nome_base + ".png";
    grafo_simples.exportar_para_dot(nome_dot);
    grafo_simples.gerar_imagem(nome_dot, nome_png);

    //grafo_simples.remover_aresta(5,6);

    std::cout << "Matriz de adjacência após remover a aresta(5-6):"  << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

   // grafo_simples.remover_vertice(3);

    std::cout << "Matriz de adjacência após remover o vértice 3:" << std::endl << std::endl;
    grafo_simples.print_matriz_adj();

    grafo_simples.gerar_matriz_inc();

    std::cout << "Matriz de incidência:" << std::endl << std::endl;
    grafo_simples.print_matriz_inc();

    grafo_simples.exportar_para_dot("grafo_simples.dot");
    grafo_simples.gerar_imagem("grafo_simples.dot", "grafo_simples.png");

    grafo_simples.gerar_lista_adj();

    std::cout << "Lista de adjacência:" << std::endl;
    grafo_simples.print_lista_adj();

    // 11 - Função que determina se um grafo é conexo ou não.

    grafo_simples.is_conexo() ? std::cout << "O grafo é conexo" << std::endl :  std::cout << "O grafo é não conexo" << std::endl;

    // 12 - Determinar se um grafo é bipartido

    grafo_simples.is_bipartido() ? std::cout << "O grafo é bipartido" << std::endl :  std::cout << "O grafo é não bipartido" << std::endl;



}

void digrafo(Digrafo& grafo_direcionado, const std::string& nome_base){

    std::cout << "----------- GRAFO DIRECIONADO ----------------------" << std::endl;

    std::cout << "Matriz de adjacência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matriz_adj();

    grafo_direcionado.gerar_matriz_inc();

    std::cout << "Matriz de incidência do grafo direcionado:" << std::endl << std::endl;

    grafo_direcionado.print_matriz_inc();


    std::string nome_dot = nome_base + ".dot";
    std::string nome_png = nome_base + ".png";
    grafo_direcionado.exportar_para_dot(nome_dot);
    grafo_direcionado.gerar_imagem(nome_dot, nome_png);

}

void menu() {
    std::cout << "\nQual grafo ou digrafo deseja analisar?\n" << std::endl;
    std::cout << "1 | GRAFO_0\t5 | DIGRAFO_0" << std::endl;
    std::cout << "2 | GRAFO_1\t6 | DIGRAFO_1" << std::endl;
    std::cout << "3 | GRAFO_2\t7 | DIGRAFO_2" << std::endl;
    std::cout << "4 | GRAFO_3\t8 | DIGRAFO_3" << std::endl;
    std::cout << "\nDigite 'sair' ou 's' para terminar." << std::endl;
    std::cout << "Insira a opção escolhida: ";
}


std::unique_ptr<Grafo> loadFile(const std::string& nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        return nullptr;
    }

    bool is_digrafo = (nome_arquivo.find("DIGRAFO") != std::string::npos);

    int num_vertices;
    arquivo >> num_vertices;

    std::unique_ptr<Grafo> grafo;
    if (is_digrafo) {
        grafo = std::make_unique<Digrafo>(num_vertices);
    } else {
        grafo = std::make_unique<Grafo>(num_vertices);
    }
    
    std::map<std::string, int> map_vertices;
    int proximo_indice = 0;

    std::string linha;
    std::getline(arquivo, linha); 

    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string u_str, v_str;

        std::getline(ss, u_str, ',');
        std::getline(ss, v_str);

        if (u_str.empty() || v_str.empty()) continue;

        if (map_vertices.find(u_str) == map_vertices.end()) {
            int novo_indice = proximo_indice++;
            map_vertices[u_str] = novo_indice;
            grafo->set_rotulo_vertice(novo_indice, u_str);
        }
        if (map_vertices.find(v_str) == map_vertices.end()) {
            int novo_indice = proximo_indice++;
            map_vertices[v_str] = novo_indice;
            grafo->set_rotulo_vertice(novo_indice, v_str); 
        }

        int u_idx = map_vertices[u_str];
        int v_idx = map_vertices[v_str];

        grafo->inserir_aresta(u_idx, v_idx, 1);
    }

    return grafo;
}
