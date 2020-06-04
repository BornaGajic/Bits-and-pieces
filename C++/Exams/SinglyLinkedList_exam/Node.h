#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename Y> class SLL;
template <typename X> ostream& operator<<(ostream&, const SLL<X>&);

template <typename T>
class Node {
    protected:
        T value;
        Node* next;
    public:
        Node(): next(nullptr){}
        Node(const T& val): value(val) {}
        Node(const Node& copyNode)
        {
            next = copyNode.next;
            value = copyNode.value;
        }
        ~Node()
        {
            value = 0;
            next = nullptr;
        }

        template <typename A>
        friend class SLL;

        template <typename B>
        friend ostream& operator<<(ostream& os, const SLL<B>& s);

        template <typename C>
        friend ostream& operator<<(ostream& os, const Node<C>& n);
};


#endif