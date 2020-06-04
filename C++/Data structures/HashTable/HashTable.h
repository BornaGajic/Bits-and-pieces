#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <utility>
#include <iostream>

using namespace std;

template <typename T, size_t S>
struct HashTable
{
    list<pair<const string, T>> container [S];

    void insert(const string& key, T value)
    {
        int i = hashFuntion(key);

        container[i].push_back(make_pair(key, value));
    }

    T search(const string& key)
    {
        int i = hashFuntion(key);

        for(pair<const string, T>& x : container[i])
        {
            if(x.first == key)
            {
                return x.second;
            }
        }
    }

    void remove(const string& key)
    {
        int i = hashFuntion(key);

        for(pair<const string, T>& x : container[i])
        {
            if(x.first == key)
            {
                container[i].remove(x);
            }
        }
    }

    private:        
        int hashFuntion (const string& str)
        {
            unsigned int acc = 0;

            for(const char& letter : str)
            {
                acc += letter % S;
                
            }

            return acc % S;
        }

};

#endif