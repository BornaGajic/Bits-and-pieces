#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"

using namespace std;

// ---------------------- GRAPHI ----------------------------------
template <typename T>
void GraphI<T>::remove_vertex (const T& vertex)
{
    int j = 0;
    for (pair<T, list<T>>& x : graph_data)
    {
        if (vertex == x.first)
            this->graph_data.erase(graph_data.begin() + j);

        int i = 0;
        for (T& adj_node : x.second)
        {
            if (adj_node == vertex)
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

template <typename T>
void GraphI<T>::print_graph () const
{
    for (auto& edge : graph_data)
    {
        cout << edge.first << ": ";
        for (auto& adj_edge : edge.second)
            cout << adj_edge << " ";
        cout << endl;
    }
}
// ---------------------- END GRAPHI ----------------------------------


// ---------------------- UNDIRECTED GRAPH ----------------------------------
template<typename T>
list<T> undirected_graph<T>::_neighbours (const T& vertex)
{
    for (auto& node : graph_data)
    {
        if (node.first == vertex)
            return node.second;
    }

    // optional?
    return list<T>{};
}

template<typename T>
vector<pair<T, int>> undirected_graph<T>::_bfs (const T& vertex)
{
    queue<pair<T, list<T>>> Q;
    vector<T> visited;
    vector<pair<T, int>>* discovered = new vector<pair<T, int>>{};

    int last_discovered = 1;

    Q.push(make_pair(vertex, _neighbours(vertex)));
    visited.push_back(vertex);
    discovered->push_back(make_pair(vertex, last_discovered));

    while (Q.size() != 0)
    {
        pair<T, list<T>> front = Q.front();
        Q.pop();

        for (auto& node : front.second)
        {
            bool is_visited = false;
            for (auto& visited_node : visited)
            {
                if (node == visited_node)
                {
                    is_visited = true;
                    break;
                }
            }
            
            if (!is_visited)
            {
                Q.push(make_pair(node, _neighbours(node)));
                visited.push_back(node);
                discovered->push_back(make_pair(node, last_discovered + 1));
            }
        }

        last_discovered++;
    }

    return *discovered;
}

template<typename T>
vector<pair<T, int>> undirected_graph<T>::_bfs (const T& vertex, const T& finish)
{
    queue<pair<T, list<T>>> Q;
    vector<T> visited;
    vector<pair<T, int>>* discovered = new vector<pair<T, int>>{};

    int last_discovered = 1;

    Q.push(make_pair(vertex, _neighbours(vertex)));
    visited.push_back(vertex);
    discovered->push_back(make_pair(vertex, last_discovered));

    while (Q.size() != 0)
    {
        pair<T, list<T>> front = Q.front();
        Q.pop();

        for (auto& node : front.second)
        {
            if (node == finish)
            {
                discovered->push_back(make_pair(node, last_discovered + 1));
                return *discovered;
            }

            bool is_visited = false;
            for (auto& visited_node : visited)
            {
                if (node == visited_node)
                {
                    is_visited = true;
                    break;
                }
            }
            
            if (!is_visited)
            {
                Q.push(make_pair(node, _neighbours(node)));
                visited.push_back(node);
                discovered->push_back(make_pair(node, last_discovered + 1));
            }
        }

        last_discovered++;
    }

    return *discovered;
}

template<typename T>
void undirected_graph<T>::add_edge (const T& vertex_a , const T& vertex_b)
{
    bool edge_a_pushed = false, edge_b_pushed = false;

    for (pair<T, list<T>>& x : graph_data)
    {
        if (x.first == vertex_a)
            x.second.push_back(vertex_b), edge_b_pushed = true;
        else if (x.first == vertex_b)
            x.second.push_back(vertex_a), edge_a_pushed = true;
    }
    
    if (!edge_a_pushed)
        graph_data.push_back(make_pair(vertex_b, list<T>{vertex_a}));
        
    if (!edge_b_pushed)
        graph_data.push_back(make_pair(vertex_a, list<T>{vertex_b})); 
}

template<typename T>
vector<T> undirected_graph<T>::shortest_path (const T& start, const T& finish)
{
    vector<pair<T, int>> discovered = _bfs(start, finish);

    vector<T>* path = new vector<T>{finish};

    T parent = discovered.back().first;

    int d = discovered.back().second - 1;

    for (size_t i = discovered.size() - 1; i != 0; i--)
    {
        if (discovered[i].second == d)
        {
            list<T> neighbours = _neighbours(discovered[i].first); 

            for (auto& x : neighbours)
            {
                if (x == parent)
                {
                    path->push_back(discovered[i].first);
                    parent = path->back();
                    d--;
                    break;
                }
            }
        }
    }

    path->push_back(start);

    reverse(path->begin(), path->end());
    
    return *path;
}
// ---------------------- END UNDIRECTED GRAPH ----------------------------------


// ---------------------- DIRECTED GRAPH ----------------------------------
template <typename T>
void directed_graph<T>::add_edge (const T& vertex_a, const T& vertex_b)
{
    for (pair<T, list<T>>& edge : graph_data)
    {
        if (edge.first == vertex_a)
            edge.second.push_back(vertex_b);
    }
}
// ---------------------- END DIRECTED GRAPH ----------------------------------

#endif