#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

typedef vector<list<pair<int, int>>> Graph;

/*
    Prvi prolaz je klasican Dijkstra, drugi prolaz Dijkstra bez
    bridova iz prvog prolaza
*/
int solve (const Graph& G, int s, int e)
{
    int runners = 2;
    int res1;
    unordered_set<int> visited;
    vector<int> distance;
    unordered_map<string, int> path;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;

    distance.resize(G.size());

    do
    {
        for (int i = 0; i < G.size(); i++)
        {
            distance[i] = i == s ? 0 : INT_MAX;
            PQ.push(make_pair(distance[i], i));
        }
        
        while (!PQ.empty())
        {
            int top = PQ.top().second;

            if (visited.find(top) != visited.end())
            {
                PQ.pop();
                continue;
            }

            for (auto& x : G[top])
            {
                if (path.find(to_string(top) + "-" + to_string(x.first)) != path.end())
                {
                    continue;
                }
                else if (distance[top] == INT_MAX) break;
                else if (distance[top] + x.second < distance[x.first])
                {
                    distance[x.first] = distance[top] + x.second;
                    PQ.push(make_pair(distance[x.first], x.first));
                }
            }

            visited.insert(top);
            PQ.pop();
        }

        if (runners == 2)
        {
            if (distance[e] != INT_MAX)
            {
                int iter_node = e;
                while (iter_node != s)
                {
                    int min_temp = INT_MAX;
                    vector<int> nodes;
                    for (auto& x : G[iter_node])
                    {
                        if (distance[x.first] + x.second <= min_temp)
                        {
                            nodes.push_back(x.first);
                            min_temp = distance[x.first] + x.second;
                        }
                    }

                    for (auto& x : nodes)
                    {
                        path[to_string(x) + "-" + to_string(iter_node)] = 1;
                    }

                    iter_node = nodes[0];
                }
            }
            else return -1;

            res1 = distance[e];
        }
        else
        {
            if (distance[e] == INT_MAX) return -1;

            return distance[e] + res1;
        }
        
        visited.clear();

    } while (runners--);
}


int main ()
{
    Graph G;
    vector<int> results;
    int n;

    while (cin >> n, n != 0)
    {
        G.resize(n);

        int m;
        cin >> m;

        for (int i = 0; i < m; i++)
        {
            int U, V, T;
            cin >> U >> V >> T;

            G[U-1].push_back(make_pair(V-1, T));
            G[V-1].push_back(make_pair(U-1, T));
        }

        results.push_back(solve(G, 0, n-1));
        G.clear();
    }

    for (auto& x : results)
    {
        if (x == -1)
            cout << "Caught" << endl;
        else 
            cout << x << endl;
    }

    return 0;
}