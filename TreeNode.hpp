#ifndef TREENODE_HPP
#define TREENODE_HPP

template <class Type>
class TreeNode {

public:

    // Informacao a ser armazenada (depois sera um campo para a chave e outro para o dado)
    Type info;

    // Apontador para a subarvore a esquerda
    TreeNode *esq;

    // Apontador para a subarvore a direita
    TreeNode *dir;

    // Apontador para o pai do no
    TreeNode *pai;

};

#endif // TREENODE_HPP
