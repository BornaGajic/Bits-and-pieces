#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/*
    Arguments:
        A => linear data structure
        s => most left border index (start)
        f => most right border index (finish)
        x => value that is being searched
        n => length of subsequence
     
    Binarysearch until A has length of n.
    Then traverse vector sequentially until x is found.
    
    Function return index of element x.

    Input:
        A => V[i] = {3 * i : i = {1..99}}
        s => 0
        f => V.size() - 1
        x => 159
        n => 29

    Output: 53
*/
int HybridSearch(vector<int>& A, int s, int f, int x, int n)
{
    int middle = floor((f + s) / 2);
    
    if((f - s) + 1 != n)
    {
        if(x == A[middle]) return middle;
        else if(x < A[middle])
        {
            if(middle - s + 1 < n)
                return HybridSearch(A, s, s + (n - (middle - s)) , x, n);    
            else
                return HybridSearch(A, s, middle, x, n);
        }
        else
        {
            if(f - middle + 1 < n)
               return HybridSearch(A, middle - (n - (f - middle + 1)), f, x, n);
            else
                return HybridSearch(A, middle, f, x, n);
        }
    }
    else
    {
        for(int i = s; i <= f; i++)
        {
            if(A[i] == x)
                return i;
        }

        return -1;
    }

    cout << "shit, not good" << endl;
}

int main()
{
    vector<int> V;

    for(int i = 0; i < 100; i++)
    {
        V.push_back(3 * i);
    }
    
    cout << HybridSearch(V, 0, V.size() - 1, 159, 29) << endl;

    return 0;
}
