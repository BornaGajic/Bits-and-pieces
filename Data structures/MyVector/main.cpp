#include <iostream>

using namespace std;

#include "MyVector.h"

int main()
{
    MyVector* v = new MyVector{};

    for(int i = 0; i < 10; i++) v->pushBack(i);

    cout << *v << endl;

    return 0;
}