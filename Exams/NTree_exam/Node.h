#ifndef NODE_H
#define NODE_H

#include <list>
#include <vector>

using namespace std;

template <typename V>
class Tree;

template <typename T>
class Node {
    private:
        T element;
        Node* parent{};
        list<Node*> children;
    public:
        Node(const T& n)
        {
            element = n;
        }
        ~Node(){ delete children; }

        void setElement(const T& elem)
        {
            element = elem;
        }

        const T& getElement() const
        {
            return element;
        }

        void addChild(Node& newChild)
        {
            children.push_back(&newChild);

            newChild.parent = this;
        }

        void removeChild(Node& child)
        {
            children.remove(child);
        }

        void setParent(Node& newParent)
        {
            parent = newParent;
        }

        bool isRoot() const
        {
            return parent == nullptr;
        }

        bool isLeaf() const
        {
            return children.empty();
        }


        template <typename V>
        friend void Tree<V>::preorderWalk(Node<V>*, vector<Node<V>*>&);

        template <typename K>
        friend ostream& operator<<(ostream& os, const Node<K>& n)
        {
            os << "Node with element " << n.element << ", parent ";
            if(n.parent == nullptr) os << -1;
            else os << n.parent->element;
            os << " and children: ";
            for(auto& x : n.children)
            {
                os << x->element << " ";
            }
            
            return os;
        }
};





#endif