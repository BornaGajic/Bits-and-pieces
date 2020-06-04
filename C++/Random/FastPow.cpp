#include <iostream>
#include <math.h>
using namespace std;

double FastPow (double a, int n)
{
    if (n == 0) return 1;
    else if (n == 1) return a;
    
    int result;

    if (n % 2 == 1)
        result = a * FastPow (a, n - 1);
    else
        result = pow(FastPow (a, n / 2), 2);

    return result;
}

int main ()
{
    return 0;
}