#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<list<pair<int, int>>> Graph;

// bellman_ford alghoritm
int bellman_ford (Graph& g, const int S, const int T)
{
    vector<int> distance ((int)g.size(), INT_MAX);

    distance[S] = 0;

    for (int j = 0; j < g.size(); j++)
    {   
        bool is_changed = false;
        for (int i = 0; i < g.size(); i++)
        {
            if (distance[i] == INT_MAX) continue;

            for (auto& adj_node : g[i])
            {
                if (distance[i] + adj_node.second < distance[adj_node.first])
                {
                    distance[adj_node.first] = distance[i] + adj_node.second;
                    is_changed = true;
                }
            }
        }
        
        if (!is_changed) return distance[T];       
    }

    return distance[T];
}

int main ()
{
    vector<Graph> graphs;
    vector<int> results;

    int N;
    cin >> N;

    results.resize(N);
    graphs.resize(N);

    while (N--)
    {
        int n, m, S, T;

        cin >> n >> m >> S >> T;

        graphs[N].resize(n);

        for (int i = 0; i < m; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;

            graphs[N][a].push_back(make_pair(b, c));
            graphs[N][b].push_back(make_pair(a, c));
        }

        results[N] = bellman_ford(graphs[N], S, T);
    }

    reverse(results.begin(), results.end());

    for (int i = 0; i < results.size(); i++)
    {
        if (results[i] == INT_MAX)
            cout << "Case#" << i + 1 << ": unreachable" << endl;  
        else
            cout << "Case#" << i + 1 << ": " << results[i] << endl;  
    }
    
    return 0;
}