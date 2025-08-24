#include <iostream>
#include <list>
#include <vector>

/*
Código gerado pelo GPT.
Me deu um branco na hora de gerar uma estrutura com 3 listas.
*/

class EstruturaListas {
    std::vector<std::list<int>> listas; // vetor de listas
public:
    // construtor: inicializa com n listas
    EstruturaListas(int n) : listas(n) {}

    // insere um valor na lista "qual"
    void inserir(int valor, int qual) {
        if (qual < 0 || qual >= listas.size()) {
            std::cerr << "Indice de lista invalido!\n";
            return;
        }
        listas[qual].push_back(valor);
    }

    // imprime todas as listas
    void printar() {
        for (int i = 0; i < listas.size(); i++) {
            std::cout << "Lista " << i << ": ";
            for (int v : listas[i]) {
                std::cout << v << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    EstruturaListas e(3); // cria estrutura com 3 listas

    e.inserir(10, 0);  // insere 10 na lista 0
    e.inserir(20, 1);  // insere 20 na lista 1
    e.inserir(30, 2);  // insere 30 na lista 2
    e.inserir(40, 1);  // insere 40 também na lista 1

    e.printar();
}
