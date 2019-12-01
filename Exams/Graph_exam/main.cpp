#include <iostream>


#include "Vertex.h"
#include "Graph.h"
#include "Employee.h"


using namespace std;



int main()
{
    Vertex<int>* v3 = new Vertex<int>{3};
    Vertex<int>* v5 = new Vertex<int>{5};
    Vertex<int>* v7 = new Vertex<int>{7};
    Vertex<int>* v17 = new Vertex<int>{17};

    v3->addNeighbor(v5);
    v3->addNeighbor(v7);

    v5->addNeighbor(v7);

    v7->addNeighbor(v17);

    Graph<int>* g = new Graph<int>{};

    g->addVertex(v3);
    g->addVertex(v5);
    g->addVertex(v7);
    g->addVertex(v17);


    cout << *g << endl;
    auto pred = traversal(*g, *v17);

    for(auto& x : pred)
    {
        cout << "Predecessor of " << x.first->data << " in traversal with root 17: ";
        if(x.second == nullptr) cout << "nullptr" << endl;
        else cout << x.second->data << endl;
    }

    Person* p1, * p2, * p3;
    Person p4{ "Marko", "Maric", 25 };

    p1 = new Employee{"Borna", "Gajic", 20, "none"};
    p2 = new Employee{"Karlo", "Gajic", 19, "none"};
    p3 = new Employee{"Ivona", "Vidovic", 20, "T - com"};

    Person* people [5] = {p1, p2, p3, &p4};

    for(auto& x : people)
    {
        x->printPerson(cout);
    }

    cout << " XXXXXXXXXXXXXXxxxx";
    return 0;
}