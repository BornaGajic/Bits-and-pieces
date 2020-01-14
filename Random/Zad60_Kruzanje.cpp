#include <iostream>
#include <vector>
#include <utility>

using namespace std;

pair<int, int> route;

void solve (int m,  vector<int> &path,  vector<vector<int>> &v)
{
    int sum = 0, maxSum = 0;
    int etape = 0, max_etape = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i; j < m; j++)
        {
            v[i][j] = path[j] + sum;
            sum += path[j];
            etape++;
            
            if (sum >= maxSum)
            {
                if (sum == maxSum)
                {
                    if (etape > max_etape)
                        route.second = i;
                }
                else
                    route.second = i;

                max_etape = etape;
                etape = 1;
                maxSum = sum;
            }
            else
                etape = 1;
        }
        sum = 0;
    }

    if (!maxSum)
    {
        std::cout << "Bad cruising" << endl;
        return;
    }

    int max_path = 0, path_length = 0;
    int j = 0;
    while(j < m)
    {
        if (v[route.second][j] == maxSum)
        {
            if (max_path <= path_length)
            {
                route.first = j + 2;
                max_path = ++path_length;
            }
        }
        else if (v[route.second][j] != 0)
            path_length++;
        else if (v[route.second][j] == 0)
            path_length = 0;

        j++;
    }

    std::cout << "The nicest part is between stops " << route.first - max_path << " and " << route.first << endl;     
}

int main ()
{
    int n, m;
    cin >> n;

    while (n--)
    {
        cin >> m;
        vector<int> path;
        vector<vector<int>> v;
        path.resize(m - 1);
        v.resize(m - 1);

        for (int i = 0; i < m - 1; i++)
        {
            cin >> path[i];
            v[i].resize(m - 1);
        }

        solve(m - 1, path, v);
    }

    return 0;
}