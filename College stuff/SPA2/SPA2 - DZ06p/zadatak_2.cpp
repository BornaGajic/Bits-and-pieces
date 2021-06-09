#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<list<pair<int, int>>> Graph;

// bellman_ford with negative cycle check 
bool bellman_ford_wormhole (Graph& g)
{
    vector<int> distance ((int)g.size(), INT_MAX);

    distance[0] = 0;

    for (int j = 0; j < g.size(); j++)
    {   
        bool is_changed = false;
        for (int i = 0; i < g.size(); i++)
        {   
            for (auto& adj_node : g[i])
            {
                if (distance[i] != INT_MAX && distance[i] + adj_node.second < distance[adj_node.first])
                {
                    distance[adj_node.first] = distance[i] + adj_node.second;
                    is_changed = true;
                }
            }
        }    

        if (!is_changed) break;
    }

    for (int i = 0; i < g.size(); i++)
        for (auto& adj_node : g[i])
            if (distance[i] + adj_node.second < distance[adj_node.first])
                return true;
    
    return false;
}

int main ()
{
    vector<Graph> graphs;
    vector<bool> results;

    int N;
    cin >> N;

    results.resize(N);
    graphs.resize(N);

    while (N--)
    {
        int n, m;

        cin >> n >> m;

        graphs[N].resize(n);

        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;

            graphs[N][a].push_back(make_pair(b, c));
        }

        results[N] = bellman_ford_wormhole(graphs[N]);
    }

    reverse(results.begin(), results.end());

    for (int i = 0; i < results.size(); i++)
    {
        if (results[i] == true)
            cout << "possible" << endl;  
        else
            cout << "not possible" << endl;  
    }

    return 0;
}