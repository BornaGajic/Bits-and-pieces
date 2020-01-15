#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Queue
{
    vector<int> A;

    public:
        void push (int element)
        {
            A.push_back(element);
        }
        int pop ()
        {
            int retVal = A[0];

            reverse(A.begin(), A.end());
            A.pop_back();
            reverse(A.begin(), A.end());

            return retVal;
        }

        bool isEmpty() { return A.empty(); }
};

int main ()
{
    Queue q;

    for (int i = 1; i <= 10; i++)
        q.push(i);
    
    while (!q.isEmpty())
        cout << q.pop() << " ";

    return 0;
}