#include <iostream>
#include <list>

using namespace std;

void Reverse (list<int> &lista) 
{
    list<int> temp;
    int n = lista.size();

    while(n--)
    {
        temp.push_front(lista.front());
        lista.pop_front();
    }

    lista = temp;
}

int main ()
{
    list<int> lista = {1, 2, 3};

    Reverse(lista);

    for (int x : lista)
        cout << x << " ";
    
    return 0;
}