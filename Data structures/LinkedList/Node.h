#ifndef NODE_H
#define NODE_H

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
    // prilikom čišćenja ispisujemo adresu
    ~Node()
    {
        cout << "Adresa obrisanog Nodea: " << this << endl;
    }

    //swap premješta sadržaj između dva čvora
    void swap(Node& n)
    {
        double backupValue = value;
        value = n.value;
        n.value = backupValue;

    }
    // ispisujemo adresu, adresu prethodnog, adresu sljedećeg te vrijednost
    void print() const
    {
        cout << "Prev: " << prev << ", At: " << this << ", Next: " << next << " Value: " << value <<endl;
    }
};

#endif