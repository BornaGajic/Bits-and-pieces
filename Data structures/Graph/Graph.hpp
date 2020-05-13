#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <optional>
#include <stack>

using namespace std;

template <typename T>
class GraphI
{   
    // computes the "time" of discovery of every vertex
    vector<pair<T, int>> _bfs (const T&);
    // computes the "time" of discovery from a to b
    vector<pair<T, int>> _bfs (const T&, const T&);

    protected: 
    vector<pair<T, list<T>>> graph_data;
    unordered_map<T, list<T>> graph_map;
    
    public:

    virtual void add_edge (const T& edge_a, const T& edge_b) = 0;
    virtual void remove_vertex (const T& edge);
    virtual void print_graph () const;

    virtual vector<T> shortest_path (const T&, const T&);

    virtual optional<vector<T>> articulation_points () const;
};

template <typename T>
class undirected_graph : public GraphI<T>
{
    using GraphI<T>::graph_data;
    using GraphI<T>::graph_map;

    public:

    void add_edge (const T&, const T&);
};

template <typename T>
class directed_graph : public GraphI<T>
{
    using GraphI<T>::graph_data;
    using GraphI<T>::graph_map;

    public:

    void add_edge (const T&, const T&);
};

#include "Graph.cpp"

/*
Stuff that I learned along the way:

https://stackoverflow.com/questions/1527849/how-do-you-understand-dependent-names-in-c  -- Two-phase name lookup
*/
#endif