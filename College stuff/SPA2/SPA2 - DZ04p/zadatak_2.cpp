#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<list<int>> Graph;

vector<pair<int, int>> critical_edges;


/*
    whole idea is to find a cut edge, and look through
    its neighbours. Ones that aren't in the cycle are 
    critical edges

    dfs is a helper function for a find_cut_edge
    print_cut_edges does the work of finding the cut edge:
    firstly it fills vector cut_vertices (true on i-th place is for corespondig vertex with the same number as i)
    after that, select all edges that have a cut edge as their neighbour, furthermore if these two edges don't
    share any of their neighbours, add it to critical_link vector. Lastly, add all edges that have just one 
    neighbour.

    cin was ambiguous -> std:: 
*/

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

void print_cut_edges (const Graph& G)
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
                cut_vertices[j] = true;
        }
    }

    vector<int> temp;
    for (int i = 0; i < cut_vertices.size(); i++)
    {
        if (cut_vertices[i] == true)
        {
            for (const auto& x : G[i])
            {
                if (cut_vertices[x] == true)
                {
                    bool gate = true;
                    for (const auto& k : G[i])
                    {
                        for (const auto& l : G[x])
                        {
                            if (k == l)
                            {
                                gate = false;
                                break;
                            }
                        }
                    }

                    if (gate)
                    {
                        bool flag = false;
                        for (const auto& y : temp)
                        {
                            if (y == x)
                            {
                                flag = true;
                                break;
                            }
                        }

                        if (!flag)
                        {
                            critical_edges.push_back(make_pair(x, i));
                            temp.push_back(i);
                        }  
                    }
                }
            }
        }
    }

    temp.clear();
    for (int i = 0; i < G.size(); i++)
    {
        if (G[i].size() == 1 && G[G[i].front()].size() == 1)
        {
            bool is_distinct = true;
            for (const auto& x : temp)
            {
                if (x == i)
                {
                    is_distinct = false;
                    break;
                }
            }

            if (is_distinct)
            {
                critical_edges.push_back(make_pair(i, G[i].front()));
                temp.push_back(G[i].front());
            }
        }
        else if (G[i].size() == 1)
        {
            critical_edges.push_back(make_pair(i, G[i].front()));
        }
    }

    sort(critical_edges.begin(), critical_edges.end());

    cout << critical_edges.size() << " critical links" << endl;
    for (auto& x : critical_edges)
        cout << x.first << " - " << x.second << endl;
}

// graph initialization
void init_graph (Graph& G)
{
    int n;
    std::cin >> n;

    G.resize(n);

    for (int i = 0; i < n; G[i++] = list<int>{});
    
    for (int i = 0; i < n; i++)
    {
        int index, m;
        std::cin >> index;
        
        for (char c = ' '; c != ')'; std::cin >> c)
        {
            if (isdigit(c))
                m = c - '0';
        }

        for (int j = 0; j < m; j++)
        {
            int vertex;
            std::cin >> vertex;
            G[index].push_back(vertex);
        }
    }    
}

int main ()
{
    Graph G;

    init_graph(G);

    print_cut_edges(G);

    return 0;
}