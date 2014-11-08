#ifndef TREENODE_HPP
#define TREENODE_HPP

template <class Type>
class TreeNode {

    // Informacao a ser armazenada (depois sera um campo para a chave e outro para o dado)
    Type info;

    // Apontador para a subarvore a esquerda
    TreeNode *esq;

    // Apontador para a subarvore a direita
    TreeNode *dir;

    // Apontador para o pai do no
    TreeNode *pai;

    // Armazena o numero de nos na subarvore esquerda
    int leftSize;

public:

    TreeNode(Type info) {
        this->info = info;
        esq = NULL;
        dir = NULL;
        pai = NULL;
        leftSize = 0;
    }

    Type getInfo() const {
        return info;
    }

    void setInfo(Type info) {
        this->info = info;
    }

    TreeNode* getEsq() const {
        return esq;
    }

    void setEsq(TreeNode* esq) {
        this->esq = esq;
    }

    TreeNode* getDir() const {
        return dir;
    }

    void setDir(TreeNode* dir) {
        this->dir = dir;
    }

    TreeNode* getPai() const {
        return pai;
    }

    void setPai(TreeNode* pai) {
        this->pai = pai;
    }

    int getLeftSize() const {
        return leftSize;
    }

    // Incrementa leftSize
    void increasesLeftSize() {
        leftSize++;
    }

    // Decrementa leftSize
    void decreasesLeftSize() {
        leftSize--;
    }

};

#endif // TREENODE_HPP
