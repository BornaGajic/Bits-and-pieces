#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

template <typename T>
class Vertex {
    private:
        T data;
        list<Vertex*> neighbors;
    public:        
        Vertex(T elem) { data = elem; }
        ~Vertex() { delete neighbors; }

        void addNeighbor(Vertex* neighbor)
        {
            neighbors.push_back(neighbor);
            
            if(!neighbor->isNeighbor(this))
            {
                neighbor->addNeighbor(this);
            }
        }
        
        bool isNeighbor(Vertex* vert)
        {
            for(Vertex* x : neighbors)
            {
                if(x == vert) return true;
            }

            return false;
        }

        void removeNeighbor(Vertex* neigbor)
        {
            neighbors.remove(neigbor);

            neigbor->removeNeighbor(this);
        }

        friend ostream& operator<<(ostream& os, const Vertex& v)
        {
            os << "Vertex at " << &v << " with data " << v.data << " and neighbors ";
            
            for(auto& x : v.neighbors)
            {
                os << x->data << " ";
            }

            return os;
        }

        friend main();
};



#endif