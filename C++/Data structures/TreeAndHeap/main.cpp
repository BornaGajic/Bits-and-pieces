#include <iostream>
#include "MinPriorityQueue.h"
#include "MinPriorityHeap.h"

using namespace std;

int main()
{
    MinPriorityQueue<int, string> mp;

    mp.insert(make_pair(1, "osoba4"), make_pair(2, "osoba7"), make_pair(7, "osoba5"), make_pair(8, "osoba1"), make_pair(5, "osoba6"));

    cout << mp << endl;

    mp.insert(make_pair(6, "osoba9"));

    cout << mp << endl;

    string str = mp.extractMin();

    cout << mp << endl;

    mp.decreaseKey(6, 4);

    cout << mp << endl;


    //----------------------------------------------------------------------------------


    MinPriorityHeap<int, string> mh;

    mh.insert(make_pair(12, "a"));

    mh.insert(make_pair(4, "b"));

    mh.insert(make_pair(7, "c"));

    mh.insert(make_pair(9, "d"));

    mh.insert(make_pair(5, "e"));

    mh.insert(make_pair(3, "f"));

     mh.insert(make_pair(1, "nula"));
   
    mh.decreaseKey(3, 2);
    string var = mh.extractMin();

    cout << endl;
    mh.tree.preorderPrint(0);
    
    for(auto& x : mh.tree.container) cout << x.first << " ";
    
    

    
    return 0;
}