#include <iostream>

#include "AVL.hpp"

using namespace std;

int main ()
{
    AVL tree;

    tree.insert(11);
    tree.insert(18);
    tree.insert(7);
    tree.insert(17);
    tree.insert(23);
    tree.insert(19);
    tree.insert(8);
    tree.insert(9);
    
    tree.insert(10);
    tree.insert(21);
    tree.insert(22);

    tree.erase(9);
    tree.erase(17);

    tree.insert(20);
    tree.erase(21);
    tree.erase(18);
    tree.erase(11);
    tree.erase(19);
    tree.erase(20);
    tree.erase(22);
    tree.erase(8);
    tree.erase(10);
    tree.erase(23);
    tree.erase(7);     

    tree.inorderPrint(tree.root);

    cout << "--------------------------" << endl << endl;

    AVL tree200;
    for (int i = 1; i <= 10; i++)
        tree200.insert(i);

    tree200.inorderPrint(tree200.root);

    cout << "Number of nodes greater: " << tree200.numberOfNodesGreater(6) << endl;
    cout << "Number of nodes less: " << tree200.numberOfNodesLess(6) << endl;
    cout << "Number of nodes in range: " << tree200.numberOfNodesInrange(7, 12) << endl;

    for (int i = 1; i <= 10; i++)
        tree200.erase(i);

    cout << "--------------------------" << endl;

    for (int i = 20; i >= 10; i--)
    {
        tree200.insert(i);
    }
    tree200.inorderPrint(tree200.root);
    
    cout << "--------------------------" << endl;

    cout << "DELETE: " << endl << endl;
    for (int i = 20; i >= 10; i--)
    {
        cout << "I: " << i << endl;
        tree200.erase(i);
        tree200.inorderPrint(tree200.root);
        cout << "--------------" << endl;
    }
    cout << "////" << endl;
    cout << "empty" << endl;
    tree200.inorderPrint(tree200.root);
    cout << "////" << endl;

    return 0;
}
