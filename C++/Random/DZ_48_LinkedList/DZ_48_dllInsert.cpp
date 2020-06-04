#include <iostream>
#include "CDLL.hpp"

using namespace std;

int main () 
{
    CDLL list;
    int n;
    cin >> n;
    while(n--)
    {
        int x;
        cin >> x;
        
        list.append(x);
        list.sort();

        list.print();
        cout << endl;
    }

    list.Delete(2);

    list.print();
    
    return 0;
}
