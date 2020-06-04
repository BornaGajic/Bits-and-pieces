#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
using namespace std;

struct Node {
    Node* prev;
    Node* next;
    double value;

    Node(){ prev = next = nullptr; }
    Node(double value)
    { 
        this->value = value;
        prev = next = nullptr;
    }
    Node(const Node& n)
    {
        prev = n.prev;
        next = n.next;
        value = n.value;
    }

    void swap(Node& n)
    {
        double backupValue = value;
        value = n.value;
        n.value = backupValue;

    }
    void print() const
    {
       std::cout << value << " ";
    }
};

#endif