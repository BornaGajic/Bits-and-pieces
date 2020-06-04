#include <iostream>

#include "B_Tree"
#include "Node.hpp"

using namespace std;

B_Tree::B_Tree(Node* root_node, int degree): root(root_node), min_degree(degree) {}

void B_Tree::InsertElement (int element)
{
    Node* iter = root;
    while (root != nullptr)
    {
        
    }
}

Node* B_Tree::get_root () const
{
    return root;
}

