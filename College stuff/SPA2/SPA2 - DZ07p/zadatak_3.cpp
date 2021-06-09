#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

typedef vector<list<pair<int, int>>> Graph;

unordered_set<string> dont_calculate;

int shortest_path (const Graph& G, vector<int>& stores, int S, int D)
{
    int diff = 0;

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

        for (auto& adj_child : G[top])
        {
            if (distance[top] + adj_child.second < distance[adj_child.first])
            {
                distance[adj_child.first] = distance[top] + adj_child.second;
                PQ.push(make_pair(distance[adj_child.first], adj_child.first));
            } 
        }        
        visited.insert(top);

        if (top == D) 
            return distance[D] + diff;
        else
        {
            for (auto& x : stores)
                if (x == top)
                {
                    diff += -distance[x];
                    dont_calculate.insert(to_string(x) + "-" + to_string(D));
                    dont_calculate.insert(to_string(D) + "-" + to_string(x));
                }
        }
        
        PQ.pop();
    }

    return distance[D] + diff;
}

int solve (const Graph& G, vector<int>& stores)
{
    int result = 0;

    for (auto& x : stores)
    {
        for (auto& y : stores)
        {
            if (x == y) continue;
            else if (dont_calculate.find(to_string(x) + "-" + to_string(y)) == dont_calculate.end())
            {   
                result += shortest_path(G, stores, x, y);
                dont_calculate.insert(to_string(y) + "-" + to_string(x));
            }
        }
    }

    for (auto& x : dont_calculate)
        cout << x << " ";

    /*
        izracunam nablizi put od 0 do n-1 i pogledam u nazad tko je dio toga
        ako je dio toga ono sto sam vec izracunao oduzmi, trebao bi ostati s result + 2
    */

    return result;
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
        int N, R;

        cin >> N >> R;

        graphs[k].resize(N);

        for (int i = 0; i < R; i++)
        {
            int U, V, T;
            cin >> U >> V >> T;

            graphs[k][U].push_back(make_pair(V, T));
            graphs[k][V].push_back(make_pair(U, T));
        }

        int trg;
        cin >> trg;
        vector<int> stores;

        while (trg--)
        {
            int x;
            cin >> x;
            stores.push_back(x);
        }

        results[k] = solve(graphs[k], stores);
    }

    cout << endl;
    for (auto& x : results) cout << x << endl;

    return 0;
}
/*
1
13 18
0 1 7
0 2 2
0 3 3
1 4 4
1 2 3
2 4 4
2 8 1
3 11 2
4 6 5
7 5 2
8 6 3
8 7 2
9 10 4
10 5 5
11 12 4
11 9 4
12 9 6
12 10 4
3
4
8
5
*/