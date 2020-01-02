#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

/*
Returns maximum path in the matrix
*/

int n, m;

int MaxPath (vector<vector<int>> &A, vector<vector<int>> &dp, int i, int j)
{ 
    if (dp[i][j] != 0)
        return dp[i][j];
        
    if (i < 0 || i >= n) return 0;
    else if (j < 0 || j >= m) return 0;

    int current = A[i][j];
    int a, b, c, d; a = b = c = d = 1;

    if (i - 1 >= 0)
        if (A[i - 1][j] - current == 1)
            a += MaxPath(A, dp, i - 1, j);

    if (i + 1 < n)
        if (A[i + 1][j] - current == 1)
            b += MaxPath(A, dp, i + 1, j);

    if (j - 1 >= 0)
        if (A[i][j - 1] - current == 1)
            c += MaxPath(A, dp, i, j - 1);

    if (j + 1 < m)
        if (A[i][j + 1] - current == 1)
            d += MaxPath(A, dp, i, j + 1);

    dp[i][j] = max(max(a, b), max(c, d));
    
    return dp[i][j];
}

int main()
{
    int max_path = 0;
    pair<int, int> index;

    cin >> n >> m;

    vector<vector<int>> matrix {n, vector<int>{m}}, dp {n, vector<int>{m}};
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> matrix[i][j], dp[i][j] = 0;
            
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int x;

            if(dp[i][j] == 0)
                x = MaxPath(matrix, dp, i, j);
            else continue;

            if (max_path <= x)
                max_path = x, index.first = i, index.second = j;   
        }
    }

    cout << "Max path is: ";
    for (int i = 0; i < max_path; i++)
        cout << matrix[index.first][index.second] + i << " ";
    

    return 0;
}
/*
Sample input:

3 3
2 1 9
3 3 8
4 5 7
Result: 1 2 3 4 5

3 4
2 1 2 3 
3 4 3 9
8 7 6 5
Result: 5 6 7 8
*/