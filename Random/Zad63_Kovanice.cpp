#include <iostream>
#include <vector>

using namespace std;

int solve (int cifra, int n, int &counter)
{
    if (n - cifra < 0) return n;

    while (n >= 0)
    {
        if (n - cifra < 0)
            return n;
        else
        {    
            n -= cifra;
            counter++;
        }
    }
}

int main ()
{    
    int n, counter = 0;
    vector<int> kovanice = {1, 2, 5, 10, 20, 50};

    cin >> n;

    for(int i = 5; i >= 0; i--)
        n = solve(kovanice[i], n, counter);

    cout << "Result: " << counter << endl;

    return 0;
}