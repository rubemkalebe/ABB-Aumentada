#include <iostream>
#include <cstdlib>
#include <fstream>
#include "BinarySearchTree.hpp"
#include "BinarySearchTree.cpp"

using std::string;

// Abre arquivo contendo os elementos a serem inseridos na arvore
void readBST(string &entrada, BinarySearchTree<int> &bst);

// Abre arquivo contendo as instrucoes
void readCommands(string &comandos, BinarySearchTree<int> &bst);

// Executa um comando
void runCommand(string &comando, std::ifstream &fin, BinarySearchTree<int> &bst);
bool runCommand(string &comando, BinarySearchTree<int> &bst);

int main(int argc, char** argv) {

    BinarySearchTree<int> bst;

    if(argc == 3) {
        string entrada = argv[1];
        string comandos = argv[2];
        readBST(entrada, bst);
        readCommands(comandos, bst);
    } else {
        string comando;
        while(std::cin >> comando) {
            if(runCommand(comando, bst)) {
                break;
            }
        }
    }

    std::cout << "**FIM DE EXECUCAO**" << std::endl;

    return 0;
}

void readBST(string &entrada, BinarySearchTree<int> &bst) {
    std::ifstream fin(entrada.c_str());
    if(fin.is_open()) {
        int elem;
        while(fin >> elem) {
            bst.insert(elem);
        }
        return;
    } else {
        std::cout << "Erro ao abrir arquivo \'" << entrada << "\'." << std::endl;
        exit(1);
    }
}

void readCommands(string &comandos, BinarySearchTree<int> &bst) {
    std::ifstream fin(comandos.c_str());
    if(fin.is_open()) {
        string comando;
        int n;
        while(fin >> comando) {
            runCommand(comando, fin, bst);
        }
        return;
    } else {
        std::cout << "Erro ao abrir arquivo \'" << comandos << "\'." << std::endl;
        exit(1);
    }
}

void runCommand(string &comando, std::ifstream &fin, BinarySearchTree<int> &bst) {
    int n;
    if(comando == "ENESIMO") {
        fin >> n;
        std::cout << bst.enesimoElemento(n) << std::endl;
    } else if(comando == "POSICAO") {
        fin >> n;
        std::cout << bst.posicao(n) << std::endl;
    } else if(comando == "MEDIANA") {
        std::cout << bst.mediana() << std::endl;
    } else if(comando == "CHEIA") {
        std::cout << bst.ehCheia() << std::endl;
    } else if(comando == "COMPLETA") {
        std::cout << bst.ehCompleta() << std::endl;
    } else if(comando == "IMPRIMA") {
        std::cout << bst.toString() << std::endl;
    } else if(comando == "REMOVA") {
        fin >> n;
        bst.remove(n);
    } else {
        std::cout << "ERRO!! Comando desconhecido!!" << std::endl;
    }
}

bool runCommand(string &comando, BinarySearchTree<int> &bst) {
    int n;
    if(comando == "ENESIMO") {
        std::cin >> n;
        std::cout << bst.enesimoElemento(n) << std::endl;
    } else if(comando == "POSICAO") {
        std::cin >> n;
        std::cout << bst.posicao(n) << std::endl;
    } else if(comando == "MEDIANA") {
        std::cout << bst.mediana() << std::endl;
    } else if(comando == "CHEIA") {
        std::cout << bst.ehCheia() << std::endl;
    } else if(comando == "COMPLETA") {
        std::cout << bst.ehCompleta() << std::endl;
    } else if(comando == "IMPRIMA") {
        std::cout << bst.toString() << std::endl;
    } else if(comando == "REMOVA") {
        std::cin >> n;
        bst.remove(n);
    } else if(comando == "INSERE") {
        std::cin >> n;
        bst.insert(n);
    } else if(comando == "SAIR") {
        return true;
    } else {
        std::cout << "ERRO!! Comando desconhecido!!" << std::endl;
    }
}
