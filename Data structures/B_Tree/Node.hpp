#ifndef NODE_HPP
#define NODE_HPP

#include <list>
#include <vector>

class Node
{
    list<int>* elements;

    // ideja: [X, Y, Z, E] X je lijevo dijete parenta a Y je desno
    vector<Node*>* children;

    public:
        Node ();

        int get_element_at (int i);
};

#endif