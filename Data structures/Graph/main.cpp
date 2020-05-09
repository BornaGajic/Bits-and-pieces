#include <iostream>

#include "Graph.hpp" 

using namespace std;

int main ()
{
    Graph<int> g;

    g.AddEdge(1, 2);
    g.AddEdge(1, 5);
    g.AddEdge(2, 3);
    g.AddEdge(2, 4);
    g.AddEdge(2, 5);
    g.AddEdge(3, 4);
    g.AddEdge(4, 5);

    g.DeleteEdge(4);
    
    g.print_graph(); cout << endl;


    return 0;
}