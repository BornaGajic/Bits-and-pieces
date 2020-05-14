#include <iostream>

#include "Graph.hpp" 

using namespace std;

int main ()
{
    undirected_graph<int> g;

    g.add_edge(3, 2);
    g.add_edge(2, 1);
    g.add_edge(1, 5);
    g.add_edge(5, 4);
    g.add_edge(5, 6);
    g.add_edge(4, 6);
    g.add_edge(4, 1);

    vector<int> path = g.shortest_path(1, 4);
    optional<vector<int>> oAP = g.articulation_points();

    for (auto& x : path)
        cout << x << " ";
    
    cout << endl;
    g.print_graph(); cout << endl;

    optional<vector<int>> v = g.articulation_points();

    for (auto& x : v.value())
        cout << x << " ";

    return 0;
}