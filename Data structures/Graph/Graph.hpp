#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>

#include <utility>
#include <algorithm>
#include <optional>

using namespace std;

template <typename T>
class IGraph
{   
    typedef unordered_map<T, int> umap_t_i;
    typedef unordered_map<T, T> umap_t_t;
    typedef unordered_map<T, bool> umap_t_b;

    // computes the "time" of discovery of every vertex
    vector<pair<T, int>> _bfs (const T&);
    // computes the "time" of discovery from a to b
    vector<pair<T, int>> _bfs (const T&, const T&);
    //
    void _articulation_points (umap_t_i& low, umap_t_i& disc, umap_t_b& visited, 
                               umap_t_t& parent, vector<T>& AP, T& vertex, int time);
    protected: 
    vector<pair<T, list<T>>> graph_data;
    unordered_map<T, list<T>> graph_map;
    
    public:

    virtual void add_edge (const T&, const T&) = 0;
    virtual void remove_vertex (const T&);
    virtual void print_graph () const;

    virtual bool is_articulation_point (const T& vertex) const;

    virtual vector<T> shortest_path (const T&, const T&);
    
    virtual optional<vector<T>> articulation_points ();
};

template <typename T>
class undirected_graph : public IGraph<T>
{
    using IGraph<T>::graph_data;
    using IGraph<T>::graph_map;

    public:

    void add_edge (const T&, const T&);
};

template <typename T>
class directed_graph : public IGraph<T>
{
    using IGraph<T>::graph_data;
    using IGraph<T>::graph_map;

    public:

    void add_edge (const T&, const T&);
};

template <typename T>
class w_undirected_graph : public IGraph<T>
{
    using IGraph<T>::graph_data;
    using IGraph<T>::graph_map;

    // something for weight

    public:

    void add_edge (const T&, const T&);
};

template <typename T>
class w_directed_graph : public IGraph<T>
{
    using IGraph<T>::graph_data;
    using IGraph<T>::graph_map;

    // something for weight

    public:

    void add_edge (const T&, const T&);
};

#include "Graph.cpp"

/*
Stuff that I learned along the way:

https://stackoverflow.com/questions/1527849/how-do-you-understand-dependent-names-in-c  -- Two-phase name lookup
*/
#endif