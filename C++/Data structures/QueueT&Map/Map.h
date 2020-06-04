#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename T, typename V>
class Map
{
    private:
       vector<pair<T, V>> container;
    public:
        Map(){}
        Map(const Map<T, V>& mapa)
        {
            for(auto& x : mapa)
            {
                container.push_back(x);
            }
        }
        ~Map(){ container.clear(); }

        V& operator[](const T& t)
        {
            for(auto& x : container)
            {
                if(x.first == t) return x.second; 
            }

            container.push_back(make_pair(t, V()));

            return V();
        }

        pair<T, V>* begin(){ return container.begin(); }
        pair<T, V>* end(){ return container.end(); }
};



#endif