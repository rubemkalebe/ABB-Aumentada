#include <iostream>
#include "BinarySearchTree.hpp"
#include "BinarySearchTree.cpp"

/*
    Arvore inserida
             13
           /    \
         10      25
        /  \    /  \
       2    12 20   31
                    /
                   29
*/

int main() {

    BinarySearchTree<int> bst;

    bst.insert(13);
    bst.insert(10);
    bst.insert(25);
    bst.insert(2);
    bst.insert(12);
    bst.insert(20);
    bst.insert(31);
    bst.insert(29);

    std::cout << bst.toString() << std::endl;

    return 0;
}
