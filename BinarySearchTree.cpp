#include <iostream>
#include "BinarySearchTree.hpp"

/****************************
 * Metodos publicos *
*****************************/

template <class Type>
BinarySearchTree<Type>::BinarySearchTree() {
    // Como uma arvore eh representada pelo endereco do no raiz
    // uma arvore vazia tem que ser representada pelo valor NULL.
    raiz = NULL;
    _size = 0;
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
    _size = 0;
}

template <class Type>
std::string BinarySearchTree<Type>::toString() {
    if(raiz != NULL) {
        std::string str = percorreEmNivel(raiz);
        return str;
    } else {
        return "A arvore esta vazia!!";
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

template <class Type>
Type BinarySearchTree<Type>::enesimoElemento(int index) {
    if((raiz != NULL) && (index > 0)) {
        TreeNode<Type> *tmp = enesimoElemento(index, raiz);
        if(tmp != NULL) {
            return tmp->getInfo();
        }
    }
    return -1; // Depois melhorar isso daqui!!
}

template <class Type>
int BinarySearchTree<Type>::posicao(Type elem) {
    if(raiz != NULL) {
        TreeNode<Type> *elemNode = search(elem, raiz);
        if(elemNode != NULL) {
            return posicao(raiz, elemNode);
        }
    }
    return -1; // Depois melhorar isso daqui!!
}

template <class Type>
Type BinarySearchTree<Type>::mediana() {
    if(raiz != NULL) {
        int medianIndex;
        if(_size % 2 != 0) {
            medianIndex = (_size / 2) + 1;
        } else {
            medianIndex = (_size / 2);
        }
        return enesimoElemento(medianIndex);
    }
    return -1; // Depois melhorar isso daqui!!
}

template <class Type>
bool BinarySearchTree<Type>::ehCheia() {
    if(raiz != NULL) {
        return ehCheia(raiz);
    } else {
        return false;
    }

}

template <class Type>
bool BinarySearchTree<Type>::ehCompleta() {
    if(raiz != NULL) {
        return ehCompleta(raiz);
    } else {
        return false;
    }
}

template <class Type>
int BinarySearchTree<Type>::size() {
    return _size;
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
                break;
            }
        } else if(chave < tmp->getInfo()){
            if(tmp->getEsq() != NULL) {
                tmp->increasesLeftSize();
                tmp = tmp->getEsq();
            } else {
                tmp->increasesLeftSize();
                tmp->setEsq(createNode(chave));
                tmp->getEsq()->setPai(tmp);
                break;
            }
        }
    }
    _size++;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::search(Type chave, TreeNode<Type> *node) {
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
    TreeNode<Type> *tmp = searchToRemove(chave, node);
    if(tmp != NULL) {
        if(isLeaf(tmp)) {
            if(tmp->getPai()->getEsq() == tmp) {
                tmp->getPai()->setEsq(NULL);
            } else {
                tmp->getPai()->setDir(NULL);
            }
            delete tmp;
        } else if((tmp->getEsq() != NULL) && (tmp->getDir() == NULL)) {
            TreeNode<Type> *filho = tmp->getEsq();
            if(tmp->getPai()->getEsq() == tmp) {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setEsq(filho);
            } else {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setDir(filho);
            }
        } else if((tmp->getEsq() == NULL) && (tmp->getDir() != NULL)) {
            TreeNode<Type> *filho = tmp->getDir();
            if(tmp->getPai()->getEsq() == tmp) {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setEsq(filho);
            } else {
                filho->setPai(tmp->getPai());
                tmp->getPai()->setDir(filho);
            }
        } else {
            TreeNode<Type> *suc = sucessor(tmp);
            Type infoTemp = suc->getInfo();
            remove(infoTemp, tmp->getDir());
            tmp->setInfo(infoTemp);
        }
	_size--;
    }    
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::searchToRemove(Type chave, TreeNode<Type> *node) {
    TreeNode<Type> *tmp = node;
    while(tmp != NULL) {
        if(chave == tmp->getInfo()) {
            return tmp;
        } else if(chave > tmp->getInfo()) {
            tmp = tmp->getDir();
        } else {
            tmp->decreasesLeftSize();
            tmp = tmp->getEsq();
        }
    }
    return NULL;
}

template <class Type>
void BinarySearchTree<Type>::printNode(TreeNode<Type> *node) {
    if(node != NULL) {
        std::cout << node->getInfo() << std::endl;
    }
}

template <class Type>
std::string BinarySearchTree<Type>::percorreEmNivel(TreeNode<Type> *node) {
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
    TreeNode<Type> *tmp = node;
    while(tmp->getEsq() != NULL) {
        tmp = tmp->getEsq();
    }
    return tmp;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::findMax(TreeNode<Type> *node) {
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

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::enesimoElemento(int index, TreeNode<Type> *node) {
    TreeNode<Type> *tmp = node;
    // Index-- para n atrapalhar a logica do leftSize :) q conta a partir do index = 0,
    // mas segundo a especificacao, deve contar a partir do index = 1.
    index--;
    while(tmp != NULL) {
        if(index == tmp->getLeftSize()) {
            return tmp;
        } else if(index < tmp->getLeftSize()) {
            tmp = tmp->getEsq();
        } else {
            index = index - tmp->getLeftSize()-1;
            tmp = tmp->getDir();
        }
    }
    return NULL;
}

template <class Type>
int BinarySearchTree<Type>::posicao(TreeNode<Type> *root, TreeNode<Type> *node) {
    TreeNode<Type> *tmp = node;
    int index = node->getLeftSize() + 1;
    while(tmp != root) {
        if(tmp->getPai()->getDir() == tmp) {
            index = index + tmp->getPai()->getLeftSize() + 1;
        }
        tmp = tmp->getPai();
    }
    return index;
}

template <class Type>
int BinarySearchTree<Type>::altura(TreeNode<Type> *node) {
    int u, v;
    if(node == NULL) {
        return -1;
    }
    u = altura(node->getEsq());
    v = altura(node->getDir());
    if(u > v) {
        return u + 1;
    } else {
        return v + 1;
    }
}

template <class Type>
bool BinarySearchTree<Type>::ehCheia(TreeNode<Type> *node) {
    if((node->getEsq() == NULL) && (node->getDir() == NULL)) {
        return true;
    } else if((node->getEsq() != NULL) && (node->getDir() != NULL)) {
        return ehCheia(node->getEsq()) && ehCheia(node->getDir());
    } else {
        return false;
    }
}

template <class Type>
bool BinarySearchTree<Type>::ehCompleta(TreeNode<Type> *node) {
    if((node->getEsq() == NULL) && (node->getDir() == NULL)) {
        return true;
    } else if((node->getEsq() != NULL) && (node->getDir() != NULL)) {
        return ehCompleta(node->getEsq()) && ehCompleta(node->getDir());
    } else if(node->getEsq() != NULL) {
        if(node->getLeftSize() == 1) {
            return true;
        } else {
            return false;
        }
    } else {
        if((node->getDir()->getEsq() == NULL) && (node->getDir()->getDir() == NULL)) {
            return true;
        } else {
            return false;
        }
    }
}
