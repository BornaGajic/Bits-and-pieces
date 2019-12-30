#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/*
    You are given a matrix with int values.
    Values stored in the matrix are the cost for
    passing through that field.

    We want to go from the top left corner to a 
    bottom right corner of the matrix,
    just by moving down or right,
    with a lowest passing cost.
    
    Example:
        1 2 
        3 4
        => 1, 2, 4.

    Bottom up approach:
*/
vector<int> LowestCostPath(vector<vector<int>>& cost)
{
    int n = cost.size();
    vector<int>* result = new vector<int>{};
    vector<vector<int>> temp {n, vector<int>{n}};
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            temp[i][j] = cost[i][j];
    
    for(int i = 1; i < n; i++)
        temp[0][i] += temp[0][i - 1], temp[i][0] += temp[i - 1][0];

    for(int i = 1; i < n; i++)
        for(int j = 1; j < n; j++)
            temp[i][j] += min(temp[i - 1][j], temp[i][j - 1]);
        
    int i, j; i = j = n - 1; 
    result->push_back(cost[i][j]);
    while (i != 0 || j != 0)
    {
        if (min(temp[i - 1][j], temp[i][j - 1]) == temp[i - 1][j]) i--;
        else j--;  

        result->push_back(cost[i][j]);
    }

    reverse(result->begin(), result->end());

    return *result;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> cost {n, vector<int>{n}};
    vector<int> result;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> cost[i][j];

    cout << endl;
    result = LowestCostPath(cost);
    
    cout << "Lowest cost path to bottom right corner: ";
    for(int x : result)
        cout << x << " ";

    return 0;
}
/*
Sample input:
5
1 3 6 7 3
2 5 9 2 4
4 8 6 1 2
7 3 5 9 9
1 2 4 8 6

Answer to the problem:

Naive thought is that you
only need to go through the
field that has lower cost value,
all the way down to a bottom right corner.

But that would yield wrong result.

We know exact cost of going only right
or down. And that would be the sum of all
past costs plus the current one.

So we use that to solve smaller problems
i.e what would be the lowest cost of
    going to the closer field

Cost on the bottom right field represents
the lowest cost that we would necessary pay 
if we are to go to that field.

=> we know that because beforehand we solved all the smaller
   problems.

Now, the bottom up part. Climb the matrix with: 
result[i] = min(left value, upper value) 
... until top left corner.
*/