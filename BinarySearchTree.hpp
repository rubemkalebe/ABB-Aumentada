#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include "TreeNode.hpp"
#include <queue>
#include <sstream>

template <class Type>
class BinarySearchTree {

    // Raiz da arvore
    TreeNode<Type> *raiz;

    void destroy_tree(TreeNode<Type> *node);
    void insert(Type chave, TreeNode<Type> *node);
    TreeNode<Type> *createNode(Type chave);
    void printNode(TreeNode<Type> *node);
    bool isLeaf(TreeNode<Type> *node);
    void remove(Type chave, TreeNode<Type> *node);

    std::string percorreEmNivel(TreeNode<Type> *node);

    /* Metodos de busca */
    TreeNode<Type> *findMin(TreeNode<Type> *node);
    TreeNode<Type> *findMax(TreeNode<Type> *node);
    TreeNode<Type> *search(Type chave, TreeNode<Type> *node);
    TreeNode<Type> *sucessor(TreeNode<Type> *node);
    TreeNode<Type> *predecessor(TreeNode<Type> *node);

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

};

#endif // BINARYSEARCHTREE_HPP
