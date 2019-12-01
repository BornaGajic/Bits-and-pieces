#ifndef GRAPH_H
#define GRAPH_H

#include <utility>

#include "Vertex.h"

using namespace std;

template <typename T>
class Graph {

private:
    list<Vertex<T>*> vertices;

public:
    Graph(){}
    Graph(const Graph& copyG)
    {
        for(Vertex<T>* x : copyG.vertices)
        {
            vertices.push_back(x);
        }

    }
    ~Graph(){ delete vertices; }

    void addVertex(Vertex<T>* vert)
    {
        vertices.push_back(vert);
    }
    void removeVertex(Vertex<T>* vert)
    {
        for(Vertex<T>* x : vertices)
        {
            if(x->isNeighbor(vert))
            {
                x->removeNeighbor(vert);
            }
        }

        vertices.remove(vert);
    }


    friend ostream& operator<<(ostream& os, const Graph& g)
    {
        for(auto& x : g.vertices)
        {
            os << *x << endl; 
        }

        return os;
    }

    friend unordered_map<Vertex<T>*, Vertex<T>*> traversal(const Graph<T>& g, Vertex<T>& root)
    {
        unordered_map<Vertex<T>*, Vertex<T>*>* myMap = new unordered_map<Vertex<T>*, Vertex<T>*>{};

        for(Vertex<T>* x : g.vertices)
        {
            if(x->isNeighbor(&root))
            {
                for(Vertex<T>* y : g.vertices)
                {
                    if(x->isNeighbor(y))
                    {
                        if(y == &root)
                        {
                            myMap->insert(make_pair(y, nullptr));
                        }
                        else
                            myMap->insert(make_pair(y, x));   
                    }
                }
            }
        
        }

        return *myMap;
    }
};





#endif