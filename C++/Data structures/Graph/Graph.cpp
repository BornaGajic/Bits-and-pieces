#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"

using namespace std;

// ---------------------- IGRAPH ----------------------------------
template <typename T>
void IGraph<T>::remove_vertex (const T& vertex)
{
    assert(graph_map.find(vertex) != graph_map.end());

    graph_map.erase(vertex);

    int j = 0;
    for (pair<T, list<T>>& x : graph_data)
    {
        if (vertex == x.first)
            graph_data.erase(graph_data.begin() + j);
            
        int i = 0;
        for (const T& adj_node : x.second)
        {
            if (adj_node == vertex)
            {
                typename list<T>::iterator it = x.second.begin();
                advance(it, i);
                it = x.second.erase(it);

                graph_map[x.first] = x.second;

                break;
            }

            i++;
        }

        j++;
    }
}

template <typename T>
void IGraph<T>::print_graph () const noexcept
{
    for (auto& edge : graph_data)
    {
        cout << edge.first << ": ";
        for (const auto& adj_edge : edge.second)
            cout << adj_edge << " ";
        cout << endl;
    }
}

template<typename T>
vector<pair<T, int>> IGraph<T>::_bfs (const T& start)
{
    assert(graph_map.find(start) != graph_map.end());

    queue<T> Q;
    unordered_map<T, bool> visited{make_pair(start, true)};
    vector<pair<T, int>>* discovered = new vector<pair<T, int>>{};

    int last_discovered = 1;

    Q.push(start);
    discovered->push_back(make_pair(start, last_discovered));

    while (Q.size() != 0)
    {
        T front = Q.front();
        Q.pop();

        bool any_visited = false;
        for (const auto& node : graph_map[front])
        {
            bool is_visited = visited.find(node) == visited.end() ? false : true;
            
            if (!is_visited)
            {
                Q.push(node);
                visited[node] = true;
                discovered->push_back(make_pair(node, last_discovered + 1));

                any_visited = true;
            }
        }

        last_discovered = any_visited ? last_discovered + 1 : last_discovered;
    }

    return *discovered;
}

template<typename T>
vector<pair<T, int>> IGraph<T>::_bfs (const T& start, const T& finish)
{
    assert(graph_map.find(start) != graph_map.end());
    assert(graph_map.find(finish) != graph_map.end());

    queue<T> Q;
    unordered_map<T, bool> visited{make_pair(start, true)};
    vector<pair<T, int>>* discovered = new vector<pair<T, int>>{};

    int last_discovered = 1;

    Q.push(start);
    discovered->push_back(make_pair(start, last_discovered));

    while (Q.size() != 0)
    {
        T front = Q.front();
        Q.pop();

        bool any_visited = false;
        for (const auto& node : graph_map[front])
        {
            if (node == finish)
            {
                discovered->push_back(make_pair(node, last_discovered + 1));
                return *discovered;
            }

            bool is_visited = visited.find(node) == visited.end() ? false : true;
            
            if (!is_visited)
            {
                Q.push(node);
                visited[node] = true;
                discovered->push_back(make_pair(node, last_discovered + 1));

                any_visited = true;
            }
        }

        last_discovered = any_visited ? last_discovered + 1 : last_discovered;
    }

    return *discovered;
}

template<typename T>
vector<T> IGraph<T>::shortest_path (const T& start, const T& finish)
{
    vector<pair<T, int>> discovered = _bfs(start, finish);

    vector<T>* path = new vector<T>{finish};

    T parent = discovered.back().first;

    int d = discovered.back().second - 1;

    for (size_t i = discovered.size() - 1; i != 0; i--)
    {
        if (discovered[i].second == d)
        {
            for (const auto& x : graph_map[discovered[i].first])
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

template <typename T>
constexpr bool IGraph<T>::is_articulation_point (const T& vertex) const
{
    assert(graph_map.find(vertex) != graph_map.end());

    stack<T> S;
    unordered_map<T, bool> visited;

    S.push(vertex);
    visited[vertex] = true;

    int counter = 0;

    while(!S.empty())
    {
        bool AP = false;
        bool any_visited = false;

        for (auto& adj_vertex : graph_map.at(S.top()))
        {
            if (visited.find(adj_vertex) != visited.end())
            {
                continue;
            }

            counter = S.top() == vertex ? counter + 1 : counter;

            if (counter == 2)
            {
                AP = true;
                break;
            }

            S.push(adj_vertex);
            visited[adj_vertex] = true;
            any_visited = true;
            
            break;
        }

        if (AP) return true;
        else if (!any_visited) S.pop();
    }

    return false;
}

template <typename T>
void IGraph<T>::_articulation_points (umap_t_i& low, umap_t_i& disc, umap_t_b& visited, umap_t_t& parent, vector<T>& AP, T& vertex, int time)                                             
{
    visited[vertex] = true;
    disc[vertex] = time + 1;
    low[vertex] = time + 1;

    int children = 0;

    for (auto& adj_vertex : graph_map[vertex])
    {
        if (visited.find(adj_vertex) == visited.end())
        {
            children++;
            parent[adj_vertex] = vertex;
            _articulation_points(low, disc, visited, parent, AP, adj_vertex, time + 1);

            low[vertex] = min(low[vertex], low[adj_vertex]);

            if (parent.find(vertex) == parent.end() && children > 1)
                AP.push_back(vertex);
            if (parent.find(vertex) != parent.end() && low[adj_vertex] >= disc[vertex])
                AP.push_back(vertex);
        }
        else if (parent[vertex] != adj_vertex)
            low[vertex] = min(low[vertex], disc[adj_vertex]);
    }
}

template <typename T>
optional<vector<T>> IGraph<T>::articulation_points ()
{
   umap_t_b visited;
   umap_t_i disc, low;
   umap_t_t parent;
   vector<T>* AP = new vector<T>{};

   _articulation_points(low, disc, visited, parent, *AP, graph_data[0].first, 0);

   return *AP;
}
// ---------------------- END IGRAPH ----------------------------------


// ---------------------- UNDIRECTED GRAPH ----------------------------------
template<typename T>
void undirected_graph<T>::add_edge (const T& vertex_a , const T& vertex_b) noexcept
{
    bool edge_a_pushed = false, edge_b_pushed = false;

    for (pair<T, list<T>>& x : graph_data)
    {
        if (x.first == vertex_a)
        {
            x.second.push_back(vertex_b);
            graph_map[vertex_a] = x.second;

            edge_b_pushed = true;
        }
            
        else if (x.first == vertex_b)
        {
            x.second.push_back(vertex_a);
            graph_map[vertex_b] = x.second;
            edge_a_pushed = true;
        }
    }
    
    if (!edge_a_pushed)
    {
        graph_data.push_back(make_pair(vertex_b, list<T>{vertex_a}));
        graph_map[vertex_b] = graph_data.back().second;
    }
        
    if (!edge_b_pushed)
    {
        graph_data.push_back(make_pair(vertex_a, list<T>{vertex_b}));
        graph_map[vertex_a] = graph_data.back().second;
    }
        
}
// ---------------------- END UNDIRECTED GRAPH ----------------------------------


// ---------------------- DIRECTED GRAPH ----------------------------------
template <typename T>
void directed_graph<T>::add_edge (const T& vertex_a, const T& vertex_b) noexcept
{
    for (pair<T, list<T>>& edge : graph_data)
    {
        if (edge.first == vertex_a)
        {
            edge.second.push_back(vertex_b);
            graph_map[vertex_a] = edge.second;
        }
            
    }
}
// ---------------------- END DIRECTED GRAPH ----------------------------------

#endif