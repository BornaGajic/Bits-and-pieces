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

    g.print_graph();

    g.DeleteEdge(2); cout << endl;

    g.print_graph(); cout << endl;

    Graph<char>* x = Graph<char>::MakeSet('A');

    x->AddEdge('A', 'B');
    x->AddEdge('C', 'F');
    x->AddEdge('D', 'Z');
    x->AddEdge('C', 'U');
    x->AddEdge('F', 'G');

    x->print_graph();

    delete x;

    return 0;
}