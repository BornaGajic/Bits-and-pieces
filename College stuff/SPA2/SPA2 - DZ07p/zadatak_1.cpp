#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <unordered_set>

using namespace std;

typedef vector<list<pair<int, int>>> Graph;

/*
    Dijkstra without decrease key implementation. Rather than deacrising the keys i pushed the duplicates
    in the priority queue and kept track of the visited nodes with unordered_set.
*/
int solve (const Graph& G, int S, int D)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
    unordered_set<int> visited;
    vector<int> distance(G.size(), INT_MAX);

    distance[S] = 0;

    for (int i = 0; i < G.size(); i++)
        PQ.push(make_pair(distance[i], i));
      
    while (!PQ.empty())
    {
        int top = PQ.top().second;

        if (visited.find(top) != visited.end())
        {   
            PQ.pop();
            continue;
        }

        visited.insert(top);

        PQ.pop();

        for (auto& adj_child : G[top])
        {
            if (distance[top] + adj_child.second < distance[adj_child.first])
            {
                distance[adj_child.first] = distance[top] + adj_child.second;
                PQ.push(make_pair(distance[adj_child.first], adj_child.first));
            } 
        }
    }

    return distance[D];
}

int main ()
{
    vector<Graph> graphs;
    vector<int> results;

    int k;
    cin >> k;

    graphs.resize(k);
    results.resize(k);

    while (k--)
    {
        int N, R, S, D;

        cin >> N >> R >> S >> D;

        graphs[k].resize(N);

        for (int i = 0; i < R; i++)
        {
            int U, V, T;
            cin >> U >> V >> T;

            graphs[k][U-1].push_back(make_pair(V-1, 12 + T));
            graphs[k][V-1].push_back(make_pair(U-1, 12 + T));
        }

        results[k] = solve(graphs[k], S-1, D-1);

    }
    cout << endl;
    for (auto& x : results) cout << x << endl;

    return 0;
}