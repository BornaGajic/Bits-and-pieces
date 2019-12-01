#include <bits/stdc++.h>

using namespace std;

int lcs (vector<char> X, vector<char> Y, vector<vector<int>>& matrix, int i, int j)
{
    if(i == -1 || j == -1) return 0;
    else if(matrix[i][j] != 0) 
    {
        return matrix[i][j];
    }
    else if(X[i] == Y[j])
    {
        int result = 1 + lcs(X, Y, matrix, i - 1, j - 1);

        matrix[i][j] = result;

        return result;
    }
    else
    {
        int res1 = lcs(X, Y, matrix, i - 1, j);
        int res2 = lcs(X, Y, matrix, i, j - 1);

        if(i - 1 > 0)
            matrix[i - 1][j] = res1;

        if(j - 1 > 0)
            matrix[i][j - 1] = res2;

        return max(res1, res2);
    }
}

int main()
{
    int n, m;

    vector<vector<int>> matrix;
    vector<char> X = {'A', 'C', 'T', 'T', 'C', 'A', 'G'};
    vector<char> Y = {'G', 'A', 'C', 'T', 'C', 'A', 'G', 'T'};

    n = X.size();
    m = Y.size();

    matrix.resize(n);
    for(int i = 0; i < n; i++) matrix[i].resize(m);

    int res = lcs(X, Y, matrix, X.size()-1, Y.size()-1);

    cout << res << endl;

    return 0;
}


// O(n * m) = O (n^2)