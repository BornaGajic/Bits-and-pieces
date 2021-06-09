#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

typedef vector<list<int>> Graph;

// calculate max path from every vertex in graph
void dfs_longest_path (const Graph& g, int index, vector<pair<bool, int>>& v, int prev_len)
{
    for (const auto& vertex : g[index])
    {
        // if vertex wasn't visited call dfs on it, mark it as visited and 
        // add 1 + previous length to the current length.
        // otherwise, if needed, call dfs to update path lenghts on other vertices.
        if (!v[vertex].first)
        {
            v[vertex] = make_pair(true, 1 + prev_len);

            dfs_longest_path(g, vertex, v, 1 + prev_len);
        }
        else
        {
            if (v[vertex].second < prev_len + 1)
            {
                v[vertex].second = prev_len + 1;

                for (auto& x : g[vertex])
                {
                    v[x].second = v[vertex].second + 1;

                    dfs_longest_path(g, x, v, v[x].second);
                }
            }
        }
    }
}

// graph initialization
void init_graph (Graph& G)
{
    int n, m;

    cin >> n >> m;

    G.resize(n);
    for (int i = 0; i < n; G[i++] = list<int>{});

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u - 1].push_back(v - 1);
    }
}

int main ()
{
    vector<pair<bool, int>> visited_vertices;
    Graph G;

    int max_path = 0;

    init_graph(G);
    visited_vertices.resize(G.size());

    // call dfs on all vertices
    for (int i = 0; i < G.size(); i++)
        dfs_longest_path(G, i, visited_vertices, 0);
        
    // find max path in the graph
    for (const auto& x : visited_vertices)
        max_path = x.second >= max_path ? x.second : max_path;

    cout << max_path;

    return 0;
}