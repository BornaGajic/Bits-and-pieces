#include <iostream>

using namespace std;

#include "CDLL.h"

int main()
{
    CDLL* list = new CDLL();

    for(int x : {1, 2, 3, 4, 5})
    {
        cout << x << endl;
        list->prepend(x);
    }

    list->print();

    delete list;
    return 0;
}