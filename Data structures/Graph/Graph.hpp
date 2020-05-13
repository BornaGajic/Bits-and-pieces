#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

template <typename T>
class GraphI
{   
    protected: vector<pair<T, list<T>>> graph_data;

    public:

    virtual void add_edge (const T& edge_a, const T& edge_b) = 0;
    virtual void remove_vertex (const T& edge);
    virtual void print_graph () const;

};

template <typename T>
class undirected_graph : public GraphI<T>
{
    using GraphI<T>::graph_data;

    list<T> _neighbours (const T&);

    vector<pair<T, int>> _bfs (const T&);
    vector<pair<T, int>> _bfs (const T&, const T&);

    public:

    void add_edge (const T&, const T&);

    vector<T> shortest_path (const T&, const T&);
};

template <typename T>
class directed_graph : public GraphI<T>
{
    using GraphI<T>::graph_data;

    public:

    void add_edge (const T&, const T&);
};

#include "Graph.cpp"

/*
Stuff that I learned along the way:

https://stackoverflow.com/questions/1527849/how-do-you-understand-dependent-names-in-c  -- Two-phase name lookup
*/
#endif