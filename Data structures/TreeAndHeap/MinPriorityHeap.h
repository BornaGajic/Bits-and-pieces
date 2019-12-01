#ifndef MINPRIORITYHEAP_H
#define MINPRIORITYHEAP_H

#include "CompleteBinaryTree.h"

using namespace std;


template <typename K, typename V>
class MinPriorityHeap {
    public:
    CompleteBinaryTree<K, V> tree;

    MinPriorityHeap(){}
    //MinPriorityHeap(const MinPriorityHeap&){}

    void downHeap(Node i)
    {
        while(true)
        {
            if(tree.isLeaf(i)) break;
            else
            {
                if((tree.container[i].first > tree.container[tree.left(i)].first)&&(tree.container[i].first > tree.container[tree.right(i)].first))
                {
                    Node lowerKeyIndex = tree.container[tree.left(i)].first > tree.container[tree.right(i)].first ? tree.right(i) : tree.left(i);

                    tree.swapNodes(lowerKeyIndex, i);
                }
                else if ((tree.container[i].first > tree.container[tree.left(i)].first)&&(tree.container[i].first < tree.container[tree.right(i)].first))
                {
                    tree.swapNodes(tree.left(i), i);
                }
                else if ((tree.container[i].first < tree.container[tree.left(i)].first)&&(tree.container[i].first > tree.container[tree.right(i)].first))
                {
                    tree.swapNodes(tree.right(i), i);
                }
                else break;
            }
        }

        
    }
    void upHeap(Node i)
    {
        if(i == 0) return;

        while(tree.container[i].first < tree.container[tree.parent(i)].first)
        {
            tree.swapNodes(i, tree.parent(i));
            if(i == 0) break;
        }
        
    }
    
    // s obzirom na prosljeđeni vektor, izgrađujemo prioritetni red
    // (pretpostavljamo da je prioritetni red prazan, ili pregazimo
    // sve dosad pohranjene parove)
    void buildMinHeap(const vector<pair<K, V>>& L)
    {
        tree.container.clear();
        for(auto& x : L)
        {
            insert(x);
        }
    }

    V minimum() const { return tree.container[0]; }

    V extractMin()
    {

        if(tree.getSize() == 1)
        {
            V val = tree.container[0].second;

            tree.container.clear();
             
            return val;
        }
        else if(tree.getSize() == 2)
        {
            V val = tree.container[0].second;

            tree.swapNodes(0, 1);

            tree.setSize(1);
             
            return val;           
        }
        else
        {
            V value = tree.container[0].second;
            K min = tree.container[1].first;
            Node minIndex = 1;

            for(Node i = 2; i < tree.getSize(); i++)
            {
                if(tree.container[i].first < min)
                {
                    min = tree.container[i].first;
                    minIndex = i;
                }
            }

            tree.container.erase(tree.container.begin());

            upHeap(minIndex);

            return value;
        }
   
    }

    // pronalazimo element s indeksom i, te ga postavljamo
    // na odgovarajuće mjesto s obzirom na njegov novi kljuc
    // newKey
    void decreaseKey(Node i, K newKey)
    {
        if(newKey > tree.container[i].first)
        {
            tree.container[i].first = newKey;
            downHeap(i);
        }
        else
        {
            tree.container[i].first = newKey;
            upHeap(i);
        }
    }

    void insert(const pair<K, V>& v)
    {
        if(tree.container.empty())
        {
            tree.updateParent(0, v);
        }
        else
        {
            tree.container.push_back(v);
            
            for(Node i = tree.getSize() - 1; i > 0; i--)
            {
                upHeap(i);
            }
        }
    }
};



#endif