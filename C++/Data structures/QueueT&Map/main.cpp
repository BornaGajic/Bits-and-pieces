#include <iostream>

using namespace std;

#include "QueueT.h"
#include "Map.h"

int main()
{
    Queue<int, 5>* q = new Queue<int, 5>{};

    int field[5];

    for(int i = 0; i < 5; i++) q->enqueue(i);

    for(int i = 0; i < 5; i++) cout << q->container[i] << " ";

    for(int i = 0; i < 3; i++) 
    {
        field[i] = q->dequeue();
    }

    cout << endl;

    for(int i = 0; i < 5; i++) cout << q->container[i] << " "; cout << endl << endl;

    cout << "Head: " << *q->head << endl;

    cout << "Tail: "<< *q->tail << endl;

    q->enqueue(42, 33, 19, 25); cout << endl;

    for(int i = 0; i < 5; i++) cout << q->container[i] << " ";

    //------------------------------------------------------------

    Map<char, unsigned int>* mapa = new Map<char, unsigned int>{};
    vector<unsigned int> arr;

    
    for(char x : "abeceda")
    {
       
    }

    return 0;
}