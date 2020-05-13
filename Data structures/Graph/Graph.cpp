#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"

using namespace std;

// ---------------------- GRAPHI ----------------------------------
template <typename T>
void GraphI<T>::remove_vertex (const T& vertex)
{
    graph_map.erase(vertex);

    int j = 0;
    for (pair<T, list<T>>& x : graph_data)
    {
        if (vertex == x.first)
            graph_data.erase(graph_data.begin() + j);
            
        int i = 0;
        for (T& adj_node : x.second)
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

template<typename T>
vector<pair<T, int>> GraphI<T>::_bfs (const T& start)
{
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

        for (auto& node : graph_map[front])
        {
            bool is_visited = visited.find(node) == visited.end() ? false : true;
            
            if (!is_visited)
            {
                Q.push(node);
                visited[node] = true;
                discovered->push_back(make_pair(node, last_discovered + 1));
            }
        }

        last_discovered++;
    }

    return *discovered;
}

template<typename T>
vector<pair<T, int>> GraphI<T>::_bfs (const T& start, const T& finish)
{
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

        for (auto& node : graph_map[front])
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
            }
        }

        last_discovered++;
    }

    return *discovered;
}

template<typename T>
vector<T> GraphI<T>::shortest_path (const T& start, const T& finish)
{
    vector<pair<T, int>> discovered = _bfs(start, finish);

    vector<T>* path = new vector<T>{finish};

    T parent = discovered.back().first;

    int d = discovered.back().second - 1;

    for (size_t i = discovered.size() - 1; i != 0; i--)
    {
        if (discovered[i].second == d)
        {
            for (auto& x : graph_map[discovered[i].first])
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
optional<vector<T>> GraphI<T>::articulation_points () const
{
    vector<T> articulation_points;

    for (auto& point : graph_data)
    {
        stack<T> S;
        unordered_map<T, bool> visited;

        S.push(point.first);
        visited[point.first] = true;

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

                counter = S.top() == point.first ? counter + 1 : counter;

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

            if (AP)
            {
                articulation_points.push_back(point.first);
                break;
            }
            else if (!any_visited) S.pop();
        }    
    }

    return make_optional(articulation_points);
}
// ---------------------- END GRAPHI ----------------------------------


// ---------------------- UNDIRECTED GRAPH ----------------------------------
template<typename T>
void undirected_graph<T>::add_edge (const T& vertex_a , const T& vertex_b)
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
void directed_graph<T>::add_edge (const T& vertex_a, const T& vertex_b)
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