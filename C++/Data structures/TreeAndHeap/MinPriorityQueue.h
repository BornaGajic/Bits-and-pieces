#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <list>
#include <utility>
#include <iostream>

using namespace std;

template <typename K, typename V>
struct MinPriorityQueue {
    
    list<pair<K, V>> container;

    void insert(){}
    template <typename... Args>
    void insert(const pair<K, V>& el, Args... otherPairs)
    {
        container.push_back(el);
        container.sort();

        insert(otherPairs...);
    }

    V extractMin()
    {
        V par;
        for(auto& x : container)
        {
            par = x.second;
            break;
        }
         
        container.pop_front();

        return par;
    }

    // pronalazimo element s kljucem key, te ga postavljamo
    // na odgovarajuće mjesto s obzirom na njegov novi kljuc
    // newKey
    void decreaseKey(const K& key, const K& newKey)
    {
        for(auto& x : container)
        {
            if(x.first == key)
            {
                x.first = newKey;

                container.sort();

                break;
            }
        }
    }

    friend ostream& operator<<(ostream& os, const MinPriorityQueue<K, V>& mp)
    {
        for(auto& x : mp.container)
        {
            os << "K: " << x.first << ", V: " << x.second << "      ";
        }
        os << endl;

        return os;
    }
};



#endif