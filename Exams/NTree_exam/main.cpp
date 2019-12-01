#include <iostream>
#include <vector>
#include <algorithm>

#include "Shapes.h"
#include "Tree.h"

using namespace std;

bool cmp (double i)
{
    return i > 10;
}

int main()
{
    vector<Shape*> vec;
    vector<double> rez;

    vec.push_back(new Rectangle{5.5, 7.2});
    vec.push_back(new Square{2.5});
    vec.push_back(new Circle{3.1});
    vec.push_back(new Rectangle{7.8, 7.9});
    

    for(Shape* x : vec)
    {
        rez.push_back(x->area());
        cout << x->area() << endl;
    }

    int var = count_if(rez.begin(), rez.end(), cmp);


    cout << var << endl;


    Node<int>* root = new Node<int>{1};

    Tree<int> tree{root};

    for(int i = 2; i <= 8; i++)
    {
        if(i == 2)
        {
            Node<int>* newNode = new Node<int>{2};

            root->addChild(*newNode);

            newNode->addChild(*new Node<int>{9});
            newNode->addChild(*new Node<int>{10});
        }
        else if(i == 5)
        {
            Node<int>* newNode = new Node<int>{5};

            root->addChild(*newNode);

            newNode->addChild(*new Node<int>{11});
            newNode->addChild(*new Node<int>{12});
            newNode->addChild(*new Node<int>{13});   
        }
        else 
        {
            Node<int>* newNode = new Node<int>{i};

            root->addChild(*newNode);
        }
    }

    vector<Node<int>*> elements{};
    elements.push_back(root);
    tree.preorderWalk(root, elements);

    for(auto& x : elements)
    {
        cout << *x << endl;
    }

   

    return 0;
}