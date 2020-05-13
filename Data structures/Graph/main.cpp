#include <iostream>

#include "Graph.hpp" 

using namespace std;

int main ()
{
    undirected_graph<int> g;

    g.add_edge(1, 2);
    g.add_edge(2, 3);
    g.add_edge(2, 4);
    g.add_edge(2, 5);
    g.add_edge(3, 4);
    g.add_edge(4, 5);
    g.add_edge(1, 6);
    g.add_edge(6, 5);

    vector<int> path = g.shortest_path(1, 4);

    for (auto& x : path)
        cout << x << " ";
    
    cout << endl;
    g.print_graph(); cout << endl;

    return 0;
}