#include <iostream>

#include <iostream>
#include "SLL.h"
#include "Expression.h"

using namespace std;

int main ()
{   
    SLL<int> s{};


    for(int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
    {
        s.prepend(i);
    }

    s.print();

    for(int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
    {
        bool a = s.removeFromTail();
    }

    for(int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
    {
        s.append(i);
    }

    cout << s << endl;

    for(int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
    {
        bool a = s.removeFromHead();
    }


    SineIntegral sInt{0.0001, 0.0, 3.14159265358979323846264338327950288419716939937510 };

    cout << "EVAL: "<<sInt.evaluate() << endl;


    return 0;
}