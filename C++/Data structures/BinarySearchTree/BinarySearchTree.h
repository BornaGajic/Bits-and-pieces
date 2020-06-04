#ifndef BST
#define BST

#include <iostream>
#include <vector>
#include <utility>

#include "Node.h"

using namespace std;


template <typename K, typename V>
struct BinarySearchTree {

    Node<K, V>* root;

    BinarySearchTree(){ root = nullptr; }
    // copy konstruktor (pripaziti na shallow-copy)
    //BinarySearchTree(const BinarySearchTree& bst);
    ~BinarySearchTree(){}

    // pretrazuj podstablo s korijenom x dok ne pronadeš čvor
    // vrijednoscu key (u suprotnom vrati nullptr)
     Node<K, V>* search(Node<K, V>* x, K key)
     {
        if(x->key == key) return x;

        Node<K, V>* iterator = x;

        while(true)
        {
            if(key == iterator->key) return iterator;
            else
            {
                if(key > iterator->key)  
                iterator = iterator->right;
                else 
                iterator = iterator->left;
            }
        }

        return nullptr;
     }

    // vrati pokazivač na čvor koji ima minimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* minimum(Node<K, V>* x)
    {
        Node<K, V>* iterator = x;
        
        while(true)
        {
            if(iterator->left == nullptr) return iterator;
            else iterator = iterator->left;
        }
    }

    // vrati pokazivač na čvor koji ima maksimalnu vrijednost
    // kljuca u podstablu čiji je korijen x
    Node<K, V>* maximum(Node<K, V>* x)
    {
        Node<K, V>* iterator = x;
        
        while(true)
        {
            if(iterator->right == nullptr) return iterator;
            else iterator = iterator->right;
        }
    }

    // vrati sljedbenika čvora x po vrijednosti key unutar stabla
    Node<K, V>* successor(Node<K, V>* x)
    {
        vector<Node<K, V>*> nodes;
        vector<K> keys;

        inorderWalk(root, nodes);

        for(auto& x : nodes) keys.push_back(x->key);

        // sort(keys.begin(), keys.begin() + keys.size());  ===> nije potreban zbog inorderWalka + definicije BST-a

        for(int i = 0; i < keys.size(); i++)
        {
            if(keys[i] == x->key)
            {
                K successorKey = keys[i + 1];

                return search(root, successorKey);
            }
        }
    }

    // vrati prethodnika čvora x po vrijednosti key unutar stabla
    Node<K, V>* predecessor(Node<K, V>* x)
    {
        vector<Node<K, V>*> nodes;
        vector<K> keys;

        inorderWalk(root, nodes);

        for(auto& x : nodes) keys.push_back(x->key);

        // sort(keys.begin(), keys.begin() + keys.size());  ===> nije potreban zbog inorderWalka + definicije BST-a

        for(int i = 0; i < keys.size(); i++)
        {
            if(keys[i] == x->key)
            {
                K predecessorKey = keys[i - 1];

                return search(root, predecessorKey);
            }
        }
    }

    // unesi novi čvor brinuvši se o definiciji binary search tree-a
    void insert(const K& key, const V& value)
    {
        Node<K, V>* element = new Node<K, V>{key, value};

        if(root == nullptr)
        {
            root = element;
            root->parent = root->left = root->right = nullptr;
        }
        else
        {
            Node<K, V>* iterator = root;

            while(true)
            {
                if(element->key > iterator->key)
                {
                    if(iterator->right == nullptr)
                    {
                        iterator->right = element;

                        element->parent = iterator;
                        
                        break;
                    }
                    else iterator = iterator->right;
                }                
                else
                {
                    if(iterator->left == nullptr)
                    {
                        iterator->left = element;

                        element->parent = iterator;

                        break;
                    }
                    else iterator = iterator->left;
                }
            }
        }
    }

    // obriši čvor x brinuvši se o definiciji binary search tree-a
    void remove(Node<K, V>* x)
    {
        x->parent = nullptr;

        if(x->left == nullptr && x->right == nullptr)
        {
            delete x;
        }
        else 
        {
            vector<Node<K, V>*> nodes;
            vector<pair<K, V>> pairs;

            inorderWalk(x, nodes);

            for(int i = 0; i < nodes.size(); i++)
            {
                if(nodes[i] == x)
                {
                    nodes.erase(nodes.begin() + i);
                    break;
                }
            }
            
            for(int i = 0; i < nodes.size(); i++) pairs.push_back(make_pair(nodes[i]->key, nodes[i]->value));

            for(Node<K, V>* x : nodes)
            {
                delete x;
                x = nullptr;
            }

            root = nullptr;

            for(auto& x : pairs)
            {
                insert(x.first, x.second);
            }

            pairs.clear();
            
        }
    }

    // napravi inorder obilazak, vrijednosti redom pohrani
    // u vektor nodes
    void inorderWalk(Node<K, V>* x, vector<Node<K, V>*>& nodes) const
    {
        if(x == nullptr)
        {
            return;
        }
        
        inorderWalk(x->left, nodes);

        nodes.push_back(x);

        inorderWalk(x->right, nodes);
    }

    // copy pridruživanje (pripaziti na shallow-copy)
   // BinarySearchTree& operator=(const BinarySearchTree& bst);

    
   // friend ostream& operator<<(ostream& os, const BinarySearchTree& bst);
};



#endif