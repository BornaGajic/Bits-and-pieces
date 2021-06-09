#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

typedef vector<list<int>> Graph;

void dfs (const Graph& G, const int start, vector<int>& count_children)
{
    stack<int> S;
    vector<int> visited;

    count_children.resize(G.size());

    S.push(start);
    visited.push_back(start);
    
    while (!S.empty())
    {
        int index = S.top();

        bool new_visit = false;
        for (const auto& vertex : G[index])
        {
            bool is_visited = false;
            for (const int v : visited)
            {
                if (v == vertex)
                {
                    is_visited = true;
                    break;
                }
            }

            if (!is_visited)
            {
                S.push(vertex);
                visited.push_back(vertex);
                count_children[index]++;

                new_visit = true;

                break;
            }
        }

        if (!new_visit)
            S.pop();
    }
}

// call dfs on all vertices, count the children of every vertex in the bfs tree
// if there are more than 2, print. (vertex is articulation point if it has 2 or more children)
void print_cut_vertices (const Graph& G)
{
    vector<int> count_children;
    vector<bool> cut_vertices;

    cut_vertices.resize(G.size());

    for (int i = 0; i < G.size(); i++)
    {
        count_children.clear();
        count_children.resize(G.size());

        dfs(G, i, count_children);
        
        for (int j = 0; j < count_children.size(); j++)
        {   
            if (count_children[j] >= 2 && !cut_vertices[j])
            {
                cut_vertices[j] = true;
                cout << j + 1 << " ";
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
        G[v - 1].push_back(u - 1);
    }
}

int main ()
{
    Graph G;

    init_graph(G);

    print_cut_vertices(G);

    return 0;
}