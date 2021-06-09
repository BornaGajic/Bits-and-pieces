#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
int n, m;

// function that checks whether child x and y share a quarrel with some other child
// i.e. given graph does not have a cycle 
bool is_cyclic (const vector<int>& x, const vector<int>& y)
{
    for (int i = 0; i < n; i++)
        if (x[i] && y[i])
            return true;
        
    return false;
}

int main ()
{   
    cin >> n >> m;

    // there is more than zero kids
    if (n)
    {
        graph.resize(n);

        // graph init
        for (int i = 0; i < n; graph[i++] = vector<int>{}, graph[i - 1].resize(n));

        // input vertices
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            graph[u - 1][v - 1] = 1;
            graph[v - 1][u - 1] = 1;
        }

        bool is_no = false;
        for (int i = 0; i < n; i++)
        {
            bool break_if_cyclic = false;
            for (int j = 0; j < n; j++)
            {
                // if i-th child has a quarrel against j-th child, 
                // then check if they share a quarrel with some other child, 
                // if yes -> graph is not a bipartite graph, otherwise continue
                if (graph[i][j])
                {
                    break_if_cyclic = is_cyclic(graph[i], graph[j]);
                    break;
                }
            }

            if (break_if_cyclic)
            {
                cout << "NO" << endl;
                is_no = true;
                break;
            }
        }

        if (!is_no) cout << "YES\n";
    }
    else
        cout << "YES\n";
        
    return 0;
}