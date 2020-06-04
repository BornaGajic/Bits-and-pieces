#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename K, typename V>
struct Node
{
    K key;
    V value; 
    Node* parent, * left, * right;

    Node(K ki, V val): key(ki), value(val) { parent = left = right = nullptr; }

    template <typename A, typename B>
    friend ostream& operator<<(ostream& os, const Node<A, B>& node);
};


#endif