#include <iostream>
#include <stdexcept>

#include "Node.hpp"

using namespace std;

Node::Node ()
{
    elements = new list<int>{};
    children = new vector<Node*> {nullptr};
}

int Node::get_element_at (int i)
{
    int k = 0;
    for (int& x : *elements)
    {
        if (k == i)
            return x;
        k++;
    }

    throw out_of_range ("Out of range");
}