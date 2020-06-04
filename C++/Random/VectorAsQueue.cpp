#include <iostream>
#include <queue>
using namespace std;

class VectorQ
{
    queue<int> A, B;

    public:
        void pushBack (int element)
        {
            A.push(element);
        }
        int popBack ()
        {
            int retVal = A.back();

            while (A.size() != 1)
            {
                B.push(A.front());
                A.pop();
            }
            A.pop();

            A = B;

            while (!B.empty())
                B.pop();

            return retVal;
        }

        bool isEmpty(){ return A.empty(); }
};


int main ()
{

    VectorQ vq;

    for (int i = 1; i <= 10; i++)
        vq.pushBack(i);
    
    while(!vq.isEmpty())
        cout << vq.popBack() << " ";

    return 0;
}