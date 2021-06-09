#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <queue>
using namespace std;

typedef vector<vector<int>> Graph;

Graph path;

void set_min_path (const Graph& G)
{
    for (int k = 0; k < G.size(); k++)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
        unordered_set<int> visited;
        vector<int>* distance = new vector<int>(G.size(), INT_MAX);

        (*distance)[k] = 0;

        for (int i = 0; i < G.size(); i++)
            PQ.push(make_pair((*distance)[i], i));
        
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

            for (int i = 0; i < G[top].size(); i++)
            {
                if (!G[top][i]) continue;

                if ((*distance)[top] + G[top][i] < (*distance)[i])
                {
                    (*distance)[i] = (*distance)[top] + G[top][i];
                    PQ.push(make_pair((*distance)[i], i));
                } 
            }
        }

        path[k] = (*distance);
        
        visited.clear();

        delete distance;
    }
}
int path_without (const Graph& G, int S, int mask)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
    unordered_set<int> visited;
    vector<int> distance(G.size(), INT_MAX);

    distance[S] = 0;

    mask &= ~(1 << S);
    mask &= ~(1 << 0);

    for (int i = 0; i < G.size(); i++)
    {
        if (mask & (1 << i)) continue;
        
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
        else if (top == INT_MAX) PQ.pop();

        visited.insert(top);

        PQ.pop();

        for (int i = 0; i < G[top].size(); i++)
        {
            if (!G[top][i]) continue;
            else if (mask & (1 << i)) continue;
            else if (distance[top] == INT_MAX) continue;

            if (distance[top] + G[top][i] < distance[i])
            {
                distance[i] = distance[top] + G[top][i];
                PQ.push(make_pair(distance[i], i));
            }
        }
    }

    return distance[0];
}
void shortest_path_to_closest_store (const Graph& G, bool& stores_visited, int mask, int node, 
                                    const vector<int>& stores, pair<int, int>& min_cost, vector<int>& possible)
{
    for (int i = 0; i < G.size(); i++)
    {
        if (G[node][i])
        {
            if (mask & (1 << i)) continue;
            
            if (!stores_visited)
            {
                cout << "i: " << i << endl;
                for (auto& store : stores)
                {
                    if (mask & (1 << store)) continue;
                    if (path[i][store] == 0)
                    {
                        possible[i] = i;
                    }
                    else if (possible[i] != -1) 
                        continue;
                    else
                        min_cost = G[node][i] + path[i][store] < min_cost.second ? make_pair(i, G[node][i] + path[i][store]) : min_cost;
                }
            }
            else
            {    
                cout << "mask: " << mask << endl;
                int path_without_mask = path_without(G, i, mask);
                if (path_without_mask == INT_MAX) continue;
                min_cost = G[node][i] + path_without_mask < min_cost.second ? make_pair(i, G[node][i] + path_without_mask) : min_cost;
            }
        }
    }
}

int bitmask_dp (const Graph& G, const vector<int>& stores, int mask, int node)
{
    vector<int> possible, results; 
    cout << "node: " << node << endl;
    results.resize(G.size());
    possible.resize(G.size(), -1);
    
    mask |= (1 << node);
    
    bool stores_visited = true;
    for (auto& store : stores)
    {
        if (mask & (1 << store)) continue;

        stores_visited = false;
        break;
    }
    if (stores_visited) mask &= ~(1 << 0);

    pair min_cost = {-1, INT_MAX};

    shortest_path_to_closest_store(G, stores_visited, mask, node, stores, min_cost, possible);

    cout << "min_cost: " << min_cost.first << " " << min_cost.second << endl;

    if (min_cost.second == INT_MAX)
    {   
        bool is_store_in_possible = false;
        for (auto& x : possible)
        {
            if (x != -1)
            {
                is_store_in_possible = true;
                break;
            }
        }

        if (is_store_in_possible == false)
            return 0;
    }
    else if (stores_visited)
    {
        if (min_cost.second == 0)
            return G[node][0];
    }

    min_cost.second -= G[node][min_cost.first];

    for (int i = 0; i < G.size(); i++)
    {
        if (!G[node][i]) continue;
        else if (mask & (1 << i)) continue;
        if (!stores_visited)
        {
            for (auto& store : stores)
            {
                if (mask & (1 << store)) continue;

                if (path[i][store] == min_cost.second)
                    possible[i] = possible[i] != -1 ? possible[i] : i;
                else if (path[i][store] == G[node][i])
                    possible[i] = possible[i] != -1 ? possible[i] : i;
            }
        }
        else
        {
            int path_without_mask = path_without(G, i, mask);

            if (path_without_mask == min_cost.second)
                possible[i] = possible[i] != -1 ? possible[i] : i;
            else if (path_without_mask == G[node][i])
                possible[i] = possible[i] != -1 ? possible[i] : i;
        }
    }
    for (auto& x : possible) cout << x << " ";
    cout << endl;

    for (auto& x : possible)
    {
        if (x == -1) continue;
        else if (x == 0 && stores_visited) return G[node][0];
        cout << "mask prije poziva: " << mask << endl;
        cout << "------------ " << x << " pocinje ----------------" << endl;
        int cost = bitmask_dp(G, stores, mask, x);
        results[x] = cost == 0 || cost == INT_MAX ? 0 : G[node][x] + cost;
        cout << "------------ " << x << " gotov ----------------" << endl;
    }
    
    min_cost = make_pair(-1, INT_MAX);
    for (int i = 0; i < results.size(); i++)
    {
        if (results[i] == 0) continue;

        min_cost = results[i] < min_cost.second ? make_pair(i, results[i]) : min_cost;
    }
    cout << "Node: " << node << ", min_cost: " << min_cost.second << endl;
    return min_cost.second;
}


int solve (const Graph& G, const vector<int>& stores)
{
    int mask = 0;
    int num_stores = bitmask_dp(G, stores, mask, 0);

    return num_stores;
}

int main ()
{
    vector<Graph> graphs;
    vector<int> results;

    int k;
    std::cin >> k;

    graphs.resize(k);
    results.resize(k);

    while (k--)
    {
        int N, R;

        std::cin >> N >> R;

        graphs[k].resize(N);

        if (path.size() == 0)
        {
            path.resize(N);
            for (int i = 0; i < path.size(); path[i++].resize(N));
        }

        for (int i = 0; i < R; i++)
        {
            int U, V, T;
            std::cin >> U >> V >> T;

            if (graphs[k][V].size() == 0) graphs[k][V].resize(N);
            if (graphs[k][U].size() == 0) graphs[k][U].resize(N);

            graphs[k][U][V] = T;
            graphs[k][V][U] = T;
        }

        int trg;
        std::cin >> trg;
        vector<int> stores;

        while (trg--)
        {
            int x;
            std::cin >> x;
            stores.push_back(x);
        }

        for (auto& x : graphs[k])
        {
            for (auto& y : x)
                cout << y << " ";
            cout << endl;
        }cout << endl;

        set_min_path(graphs[k]);

        for (auto& x : path)
        {
            for (auto& y : x)
                cout << y << " ";
            cout << endl;
        }
        
        results[k] = solve(graphs[k], stores);
        path.clear();
    }

    cout << endl;
    for (auto& x : results) cout << x << endl;

    return 0;
}
/*
1
8 11
0 1 2
0 3 1
3 2 1
1 2 3
3 5 2
5 7 1
7 6 2
6 5 4
6 2 1
6 4 5
4 2 1
4
5
6
3
1
*/