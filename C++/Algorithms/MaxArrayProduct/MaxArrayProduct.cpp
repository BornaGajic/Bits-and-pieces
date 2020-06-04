#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    MaxArrayProduct, with one restriction:
        if element is in A, then its neighbours cannot be part of array B

    Input:
        Array of integers,
        Array for memoization,
        index for array,
        boolean value

    Output:
        Maximum product of elements in subarray of given array
        
    Example:
        A = {-1, 2, -3, -10, 4}

        result:
            array B = {4, -3, -1} = 12

*/

int MaxArrayProduct (vector<int>& A, vector<int>& dp,  int i, bool isNegative)
{
    if (i < 0) return 1;
    else
    {
        int leftResult, rightResult;

        if(dp[i] != 0)
            return dp[i];

        if(A[i] < 0)
        {
            leftResult = A[i] * MaxArrayProduct(A, dp, i - 2, true);
            rightResult = MaxArrayProduct(A, dp, i - 1, isNegative);
        }
        else
        {   
            leftResult = A[i] * MaxArrayProduct(A, dp, i - 2, isNegative);
            rightResult = MaxArrayProduct(A, dp, i - 1, isNegative);
        }

        if((leftResult < 0 || rightResult < 0) && isNegative)
        {
            dp[i] = min(leftResult, rightResult);

            return dp[i];
        }
            
        dp[i] = max(leftResult, rightResult);

        return dp[i];
    }
}

int main()
{
    vector<int> v = {-1, 2, -3, -10, 4}, dp;

    dp.resize(v.size());

    cout << MaxArrayProduct(v, dp, v.size() - 1, false) << endl;

    return 0;
}