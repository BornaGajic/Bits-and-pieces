#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H

#include <vector>
#include <utility>
#include <iostream>

using namespace std;


typedef unsigned int Node;

template <typename K, typename V>
struct CompleteBinaryTree {
    
    vector<pair<K, V>> container;
    

    Node left(Node i) const { return 2 * i + 1; }
    Node right(Node i) const { return 2 * i + 2; }
    Node parent(Node i) const 
    {
        if(i != 0 && i != 1 && i != 2)
            return i / 2;
        else return 0;
     }

    pair<K, V>& element(Node i)
    {
        return container[i];
    }
    const pair<K, V>& element(Node i) const
    {
        return container[i]; 
    }

    void updateLeft(Node i, const pair<K, V>& e)
    {
        container.insert(container.begin() + left(i), e);
    }
    void updateRight(Node i, const pair<K, V>& e)
    {   
        if(left(i) <= container.size())
            container.insert(container.begin() + right(i), e);        
        else cout << "ne mogu to napraviti nisi stavio lijevi list" << endl;
    }
    void updateParent(Node i, const pair<K, V>& e)
    {
        container.insert(container.begin() + parent(i), e);
    }

    bool isLeaf(Node i) const
    { 
        return left(i) >= container.size();
    }

    unsigned int getSize()
    { 
        return container.size();
    }
    
    void setSize(unsigned int newSize)
    { 
       container.resize(newSize);
    }

    bool empty() const { return container.size() == 0; }

    void preorderPrint(Node i) const
    {
        if(isLeaf(i))
        {
            cout << "K: " << container[i].first << ", V: " << container[i].second << "; " << endl;
            return;
        }

         cout << "K: " << container[i].first << ", V: " << container[i].second << "; ";
         cout << endl;
        
         preorderPrint(left(i));

         if(right(i) < container.size())
            preorderPrint(right(i));

    }
    void postorderPrint(Node i) const 
    {
        // TODO
    }

    void swapNodes(Node i, Node j)
    {
        auto temp = element(i);
        element(i) = element(j);
        element(j) = temp;

    }

    const pair<K, V>& operator[](int x) const{ return element(x); }

    pair<K, V>& operator[](int x){ return element(x); }
};



#endif