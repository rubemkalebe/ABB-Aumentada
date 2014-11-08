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
        raiz->pai = NULL;
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
    }
}

template <class Type>
Type BinarySearchTree<Type>::findMin() {
    if(raiz == NULL) {
        return -1;
    } else {
        TreeNode<Type> *tmp = findMin(raiz);
        return tmp->info;
    }
}

template <class Type>
Type BinarySearchTree<Type>::findMax() {
    if(raiz == NULL) {
        return -1;
    } else {
        TreeNode<Type> *tmp = findMax(raiz);
        return tmp->info;
    }
}

template <class Type>
Type BinarySearchTree<Type>::sucessor(Type chave) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if((tmp = sucessor(tmp)) != NULL) {
            return tmp->info;
        }
    }
    return -1;
}

template <class Type>
Type BinarySearchTree<Type>::predecessor(Type chave) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if((tmp = predecessor(tmp)) != NULL) {
            return tmp->info;
        }
    }
    return -1;
}

/****************************
 * Metodos privados *
*****************************/

template <class Type>
void BinarySearchTree<Type>::destroy_tree(TreeNode<Type> *node) {
    // Metodo recursivo para desalocar memoria
    if(node != NULL) {
        destroy_tree(node->esq);
        destroy_tree(node->dir);
        delete node;
    }
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::createNode(Type chave) {
    TreeNode<Type> *tmp = new TreeNode<Type>;
    tmp->info = chave;
    tmp->esq = NULL;
    tmp->dir = NULL;
    return tmp;
}

template <class Type>
bool BinarySearchTree<Type>::isLeaf(TreeNode<Type> *node) {
    return (node->esq == NULL) && (node->dir == NULL);
}

template <class Type>
void BinarySearchTree<Type>::insert(Type chave, TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp != NULL) {
        if(chave == tmp->info) {
            std::cout << "O valor " << chave << " ja foi inserido na BST!" << std::endl;
            return;
        } else if(chave > tmp->info) {
            if(tmp->dir != NULL) {
                tmp = tmp->dir;
            } else {
                tmp->dir = createNode(chave);
                tmp->dir->pai = tmp;
                break;
            }
        } else if(chave < tmp->info){
            if(tmp->esq != NULL) {
                tmp = tmp->esq;
            } else {
                tmp->esq = createNode(chave);
                tmp->esq->pai = tmp;
                break;
            }
        }
    }
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::search(Type chave, TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp != NULL) {
        if(chave == tmp->info) {
            return tmp;
        } else if(chave > tmp->info) {
            tmp = tmp->dir;
        } else {
            tmp = tmp->esq;
        }
    }
    return NULL;
}

template <class Type>
void BinarySearchTree<Type>::remove(Type chave, TreeNode<Type> *node) {
    TreeNode<Type> *tmp = search(chave, raiz);
    if(tmp != NULL) {
        if(isLeaf(tmp)) {
            if(tmp->pai->esq == tmp) {
                tmp->pai->esq = NULL;
            } else {
                tmp->pai->dir = NULL;
            }
            delete tmp;
            return;
        } else if(((tmp->esq != NULL) && (tmp->dir == NULL)) ||
                  ((tmp->esq == NULL) && (tmp->dir != NULL))) {
            if(tmp->pai->esq == tmp) {
                tmp->pai->esq = tmp->esq;
            } else {
                tmp->pai->dir = tmp->esq;
            }
            return;
        } else {
            TreeNode<Type> *suc = sucessor(tmp);
            Type infoTemp = suc->info;
            remove(infoTemp);
            tmp->info = infoTemp;
            return;
        }
    }
}

template <class Type>
void BinarySearchTree<Type>::printNode(TreeNode<Type> *node) {
    if(node != NULL) {
        std::cout << node->info << std::endl;
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
        out << tmp->info;
        s = out.str();
        str += s;
        str += ' ';
        if(tmp->esq != NULL)
            fila.push(tmp->esq);
        if(tmp->dir != NULL)
            fila.push(tmp->dir);

    }
    return str;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::findMin(TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp->esq != NULL) {
        tmp = tmp->esq;
    }
    return tmp;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::findMax(TreeNode<Type> *node) {
    // Versao iterativa
    TreeNode<Type> *tmp = node;
    while(tmp->dir != NULL) {
        tmp = tmp->dir;
    }
    return tmp;
}

template <class Type>
TreeNode<Type> *BinarySearchTree<Type>::sucessor(TreeNode<Type> *node) {
    if(node->dir != NULL) {
        return findMin(node->dir);
    } else {
        TreeNode<Type> *p;
        TreeNode<Type> *t;
        p = node->pai;
        t = node;
        while((p != NULL) && (t == p->dir)) {
            // vai subindo na arvore
            t = p;
            p = t->pai;
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
    if(node->esq != NULL) {
        return findMax(node->esq);
    } else {
        TreeNode<Type> *p;
        TreeNode<Type> *t;
        p = node->pai;
        t = node;
        while((p != NULL) && (t == p->esq)) {
            // vai subindo na arvore
            t = p;
            p = t->pai;
        }
        if(p == NULL) {
            // nao tem predecessor
            return NULL;
        } else {
            return p;
        }
    }
}
