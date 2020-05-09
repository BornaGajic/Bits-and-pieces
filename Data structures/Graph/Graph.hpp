#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <vector>
#include <utility>

using namespace std;

template <typename T>
class Graph
{   
    // first element of a pair represents vertex, and second its neighbours
    vector<pair<T, list<T>>> data;

    public:
        void AddEdge (const T& edge_a , const T& edge_b)
        {
            bool edge_a_pushed = false, edge_b_pushed = false;

            for (pair<T, list<T>>& x : data)
            {
                if (x.first == edge_a)
                    x.second.push_back(edge_b), edge_b_pushed = true;
                else if (x.first == edge_b)
                    x.second.push_back(edge_a), edge_a_pushed = true;
            }
            
            if (!edge_a_pushed)
                data.push_back(make_pair(edge_b, list<T>{edge_a}));
                
            if (!edge_b_pushed)
                data.push_back(make_pair(edge_a, list<T>{edge_b})); 
        }
        
        void DeleteEdge (const T& edge)
        {
            int j = 0;
            for (pair<T, list<T>>& x : data)
            {
                if (edge == x.first)
                    data.erase(data.begin() + j);

                int i = 0;
                for (T& adj_node : x.second)
                {
                    if (adj_node == edge)
                    {
                        typename list<T>::iterator it = x.second.begin();
                        advance(it, i);
                        it = x.second.erase(it);
                        break;
                    }

                    i++;
                }

                j++;
            }
        }

        void print_graph () const
        {
            for (pair<T, list<T>>& edge : data)
            {
                cout << edge.first << ": ";
                for (T& adj_edge : edge.second)
                    cout << adj_edge << " ";
                cout << endl;
            }
        }
};

#endif