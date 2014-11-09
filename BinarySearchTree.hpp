#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "TreeNode.hpp"
#include <queue>
#include <sstream>
#include <algorithm>

template <class Type>
class BinarySearchTree {

    // Raiz da arvore
    TreeNode<Type> *raiz;

    // Quantidade de elementos na arvore
    int _size;

    void destroy_tree(TreeNode<Type> *node);
    void insert(Type chave, TreeNode<Type> *node);
    TreeNode<Type> *createNode(Type chave);
    void printNode(TreeNode<Type> *node);
    bool isLeaf(TreeNode<Type> *node);
    void remove(Type chave, TreeNode<Type> *node);
    TreeNode<Type> *searchToRemove(Type chave, TreeNode<Type> *node); // Atualiza leftSize antes de remover

    std::string percorreEmNivel(TreeNode<Type> *node);

    /* Metodos de busca */
    TreeNode<Type> *findMin(TreeNode<Type> *node);
    TreeNode<Type> *findMax(TreeNode<Type> *node);
    TreeNode<Type> *search(Type chave, TreeNode<Type> *node);
    TreeNode<Type> *sucessor(TreeNode<Type> *node);
    TreeNode<Type> *predecessor(TreeNode<Type> *node);

    /* Metodos de busca com indexacao */
    TreeNode<Type> *enesimoElemento(int index, TreeNode<Type> *node);
    int posicao(TreeNode<Type> *root, TreeNode<Type> *node);

    int altura(TreeNode<Type> *node);
    bool ehCheia(TreeNode<Type> *node);
    bool ehCompleta(TreeNode<Type> *node);

public:

    BinarySearchTree();
    ~BinarySearchTree();

    void insert(Type chave);
    void remove(Type chave);
    void destroy_tree();
    bool isEmpty();

    // Retorna uma string que contem a sequencia de visitacao (percorrimento) da BST por nivel
    std::string toString();

    /* Metodos de busca */
    Type findMin();
    Type findMax();
    bool search(Type chave);
    Type sucessor(Type chave);
    Type predecessor(Type chave);

    /* Metodos de busca com indexacao */
    Type enesimoElemento(int index);
    int posicao(Type elem);
    Type mediana();

    bool ehCheia();
    bool ehCompleta();

    int size();

};

#endif // BINARYSEARCHTREE_HPP
