#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class Graph
{   
    // polje listi susjedstva
    vector<list<T>> edges;

    public:
        // u polje dodaj vrh/element i tom vrhu/elementu  
        //  dodaj element/vrh ako ono ne postoji u grafu
        // u suprotnom dodaj element tamo gdje treba
        // u mainu je primjer.
        void AddEdge (const T& edge, const T& element)
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

        // obrisi onu listu u kojoj je element prvi clan
        // i u svim ostalim listama izbaci element
        void DeleteEdge (const T& element)
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

        
        // ispis listi susjedstva
        void print_adj_list () const
        {
            for (auto& edge : edges)
            {
                std::cout << edge.front() << ": ";
                for (auto& adj_edge : edge)
                {
                    if (adj_edge != edge.front())
                        std::cout << adj_edge << " -> ";
                }
                    
                std::cout << "NULL" << endl;
            }
        }

        // ispis vrhova
        void print_edges () const
        {
            for (auto& edge : edges)
                std::cout << edge.front() << " ";
        }

        // breadth-first-search
        /*
        V BFS (const V& start_vertex, const V& vertex) const
        {
            queue q{};
        } */
};

#endif