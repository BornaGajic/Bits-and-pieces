#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node
{
    public:
        int value, height = -1;
        Node* parent{};
        Node* leftChild{};
        Node* rightChild{};

    public:
        Node () { parent = leftChild = rightChild = nullptr; }
        Node(int val): value(val) {}
        ~Node()
        {
            leftChild = nullptr;
            rightChild = nullptr;
            value = 0;
        }
};

#endif