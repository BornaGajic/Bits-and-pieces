#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
    BinarySearchTree<int, char> bst;
    vector<Node<int, char>*> nodes;

    bst.insert(8, 'a');
    bst.insert(6, 'b');
    bst.insert(9, 'c');
    bst.insert(4, 'd');
    bst.insert(7, 'e');
    bst.insert(2, 'f');
    bst.insert(5, 'g');

    Node<int, char>* elem = bst.search(bst.root, 7);

    cout << elem->value << endl;

    bst.inorderWalk(bst.root, nodes);
    
    for(auto& x : nodes) cout << x->key << " ";
    cout << endl;

    Node<int, char>* succ = bst.successor(bst.root);

    cout << succ->value << endl;

    Node<int, char>* pred = bst.predecessor(bst.root);

    cout << pred->value << endl;
    
    bst.remove(bst.root);
   
    for(auto& x : nodes)
    {
        nodes.pop_back();
    }
    
    bst.inorderWalk(bst.root, nodes);
    
    for(auto& x : nodes) cout << x->key << " ";

    return 0;
}