#include <iostream>
#include "BinarySearchTree.hpp"

/****************************
 * Metodos publicos *
*****************************/

template <class Type>
BinarySearchTree<Type>::BinarySearchTree() {
    // Como uma arvore eh representada pelo endereço do no raiz
    // uma arvore vazia tem que ser representada pelo valor NULL.
    raiz = NULL;
}

template <class Type>
BinarySearchTree<Type>::~BinarySearchTree() {
    // Chama o metodo para liberar toda a memoria alocada para a arvore
    destroy_tree();
}

template <class Type>
void BinarySearchTree<Type>::insert(Type chave) {
    if(raiz != NULL) {
        insert(chave, raiz);
    } else {
        raiz = createNode(chave);
    }
}

template <class Type>
void BinarySearchTree<Type>::remove(Type chave) {
    if(raiz == NULL) {
        std::cout << "A arvore esta vazia!!" << std::endl;
    } else {
        remove(chave, raiz);
    }
}

template <class Type>
bool BinarySearchTree<Type>::isEmpty() {
    return raiz == NULL;
}

template <class Type>
bool BinarySearchTree<Type>::search(Type chave) {
    return search(chave, raiz) != NULL;
}

template <class Type>
void BinarySearchTree<Type>::destroy_tree() {
    destroy_tree(raiz);
}

template <class Type>
std::string BinarySearchTree<Type>::toString() {
    if(raiz != NULL) {
        std::string str = percorreEmNivel(raiz);
        return str;
    } else {
        return "A arvore esta vazia!!\n";
    }
}

template <class Type>
Type BinarySearchTree<Type>::findMin() {
    if(raiz == NULL) {
        return -1; // Depois melhorar isso daqui!! Se fosse uma BST de char...
    } else {
        TreeNode<Type> *tmp = findMin(raiz);
        return tmp->getInfo();
    }
}

template <class Type>
Type BinarySearchTree<Type>::findMax() {
    if(raiz == NULL) {
        return -1; // Depois melhorar isso daqui!! Se fosse uma BST de char...
    } else {
        TreeNode<Type> *tmp = findMax(raiz);
        return tmp->getInfo();
    }
}

template <class Type>
Type BinarySearchTree<Type>::sucessor(Type chave) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if((tmp = sucessor(tmp)) != NULL) {
            return tmp->getInfo();
        }
    }
    return -1; // Depois melhorar isso daqui!!
}

template <class Type>
Type BinarySearchTree<Type>::predecessor(Type chave) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if((tmp = predecessor(tmp)) != NULL) {
            return tmp->getInfo();
        }
    }
    return -1; // Depois melhorar isso daqui!!
}

/****************************
 * Metodos privados *
*****************************/

template <class Type>
void BinarySearchTree<Type>::destroy_tree(TreeNode<Type> *node) {
    // Metodo recursivo para desalocar memoria
    if(node != NULL) {
        destroy_tree(node->getEsq());
        destroy_tree(node->getDir());
        delete node;
    }
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::createNode(Type chave) {
    TreeNode<Type> *tmp = new TreeNode<Type>(chave);
    return tmp;
}

template <class Type>
bool BinarySearchTree<Type>::isLeaf(TreeNode<Type> *node) {
    return (node->getEsq() == NULL) && (node->getDir() == NULL);
}

template <class Type>
void BinarySearchTree<Type>::insert(Type chave, TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp != NULL) {
        if(chave == tmp->getInfo()) {
            std::cout << "O valor " << chave << " ja foi inserido na BST!" << std::endl;
            return;
        } else if(chave > tmp->getInfo()) {
            if(tmp->getDir() != NULL) {
                tmp = tmp->getDir();
            } else {
                tmp->setDir(createNode(chave));
                tmp->getDir()->setPai(tmp);
                return;
            }
        } else if(chave < tmp->getInfo()){
            if(tmp->getEsq() != NULL) {
                tmp = tmp->getEsq();
            } else {
                tmp->setEsq(createNode(chave));
                tmp->getEsq()->setPai(tmp);
                return;
            }
        }
    }
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::search(Type chave, TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp != NULL) {
        if(chave == tmp->getInfo()) {
            return tmp;
        } else if(chave > tmp->getInfo()) {
            tmp = tmp->getDir();
        } else {
            tmp = tmp->getEsq();
        }
    }
    return NULL;
}

template <class Type>
void BinarySearchTree<Type>::remove(Type chave, TreeNode<Type> *node) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if(isLeaf(tmp)) {
            if(tmp->getPai()->getEsq() == tmp) {
                tmp->getPai()->setEsq(NULL);
            } else {
                tmp->getPai()->setDir(NULL);
            }
            delete tmp;
            return;
        } else if((tmp->getEsq() != NULL) && (tmp->getDir() == NULL)) {
            TreeNode<Type> *filho = tmp->getEsq();
            if(tmp->getPai()->getEsq() == tmp) {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setEsq(filho);
            } else {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setDir(filho);
            }
            return;
        } else if((tmp->getEsq() == NULL) && (tmp->getDir() != NULL)) {
            TreeNode<Type> *filho = tmp->getDir();
            if(tmp->getPai()->getEsq() == tmp) {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setEsq(filho);
            } else {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setDir(filho);
            }
            return;
        } else {
            TreeNode<Type> *suc = sucessor(tmp);
            Type infoTemp = suc->getInfo();
            remove(infoTemp);
            tmp->setInfo(infoTemp);
            return;
        }
    }
}

template <class Type>
void BinarySearchTree<Type>::printNode(TreeNode<Type> *node) {
    if(node != NULL) {
        std::cout << node->getInfo() << std::endl;
    }
}

template <class Type>
std::string BinarySearchTree<Type>::percorreEmNivel(TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp;
    std::string str = "";
    std::string s;
    std::queue<TreeNode<Type>*> fila;
    fila.push(node);
    while(!fila.empty()) {
        tmp = fila.front();
        fila.pop();
        std::stringstream out;
        out << tmp->getInfo();
        s = out.str();
        str += s;
        str += ' ';
        if(tmp->getEsq() != NULL)
            fila.push(tmp->getEsq());
        if(tmp->getDir() != NULL)
            fila.push(tmp->getDir());

    }
    return str;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::findMin(TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp->getEsq() != NULL) {
        tmp = tmp->getEsq();
    }
    return tmp;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::findMax(TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp->getDir() != NULL) {
        tmp = tmp->getDir();
    }
    return tmp;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::sucessor(TreeNode<Type> *node) {
    if(node->getDir() != NULL) {
        return findMin(node->getDir());
    } else {
        TreeNode<Type> *p;
        TreeNode<Type> *t;
        p = node->getPai();
        t = node;
        while((p != NULL) && (t == p->getDir())) {
            // vai subindo na arvore
            t = p;
            p = t->getPai();
        }
        if(p == NULL) {
            // nao tem sucessor
            return NULL;
        } else {
            return p;
        }
    }
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::predecessor(TreeNode<Type> *node) {
    if(node->getEsq() != NULL) {
        return findMax(node->getEsq());
    } else {
        TreeNode<Type> *p;
        TreeNode<Type> *t;
        p = node->getPai();
        t = node;
        while((p != NULL) && (t == p->getEsq())) {
            // vai subindo na arvore
            t = p;
            p = t->getPai();
        }
        if(p == NULL) {
            // nao tem predecessor
            return NULL;
        } else {
            return p;
        }
    }
}
