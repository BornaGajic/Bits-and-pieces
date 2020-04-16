#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename T>
class Graph
{   
    vector<list<T>> edges;

    public:
        void AddEdge (T edge, T element)
        {
            bool edge_pushed = false, element_pushed = false;

            for (auto& x : edges)
            {
                if (x.front() == edge)
                    x.push_back(element), element_pushed = true;
                else if (x.front() == element)
                    x.push_back(edge), edge_pushed = true;
            }
            
            if (!edge_pushed)
                edges.push_back(list<T>{element, edge});
                
            if (!element_pushed)
                edges.push_back(list<T>{edge, element}); 
        }

        void DeleteEdge (T element)
        {
            int j = 0;
            for (auto& edge : edges)
            {
                if (element == edge.front())
                    edges.erase(edges.begin() + j);

                int i = 0;
                for (T& adj_node : edge)
                {
                    if (adj_node == element)
                    {
                        typename list<T>::iterator it = edge.begin();
                        advance(it, i);
                        it = edge.erase(it);
                        break;
                    }

                    i++;
                }

                j++;
            }
        }

        void print_graph ()
        {
            for (auto& edge : edges)
            {
                cout << edge.front() << ": ";
                for (auto& adj_edge : edge)
                {
                    if (adj_edge != edge.front())
                        cout << adj_edge << " -> ";
                }
                    
                cout << "NULL" << endl;
            }
        }
        
        static Graph* MakeSet (T element)
        {
            return new Graph<T>{};
        }
};

#endif