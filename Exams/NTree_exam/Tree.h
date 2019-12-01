#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Node.h"

using namespace std;


template <typename T>
class Tree {
    private:
        Node<T>* root;
    public:
        Tree(Node<T>* root)
        {
            this->root = root;
        }
        ~Tree()
        {

        }

        void preorderWalk(Node<T>* node, vector<Node<T>*>& vec)
        {
            if(node->isLeaf())
            {
                return;
            }

            for(Node<T>* x : node->children)
            {
                vec.push_back(x);

                preorderWalk(x, vec);

            }
        }
};



#endif