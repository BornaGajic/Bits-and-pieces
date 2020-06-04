#include <iostream>
#include <vector>

using namespace std;

int KnapsackProblem (vector<int>& weight, vector<int>& value, int w, int i, int sum, vector<int>& dp)
{
    if(i >= 0)
    {
        if(w - weight[i] >= 0)
        {
            int res1, res2;
            
            if(dp[i] == 0)
            {
                res1 = value[i] + KnapsackProblem(weight, value, w - weight[i], i - 1, sum + value[i], dp);
                dp[i] = res1;
            }
            else
                res1 = dp[i];
                
            res2 = KnapsackProblem(weight, value, w, i - 1, sum, dp);
                
            return max(res1, res2);
        }
        else
            return KnapsackProblem(weight, value, w, i - 1, sum, dp);
    }
    else 
        return 0;

}

int main()
{
    int n, w;

    cin >> n;

    vector<int> weight, value, dp;

    weight.resize(n);
    value.resize(n);
    dp.resize(n);

    for(int i = 0; i < n; i++) cin >> value[i];
    for(int i = 0; i < n; i++) cin >> weight[i];

    cin >> w;

    int result = KnapsackProblem(weight, value, w, n - 1, 0, dp);

    cout << result << endl;

    return 0;
}
/*
Input:
n = 6
value  = 30 140 20 100 120 31
weight = 10 20  30 40  50  60
Knapsack weight limit = 100

result = 290

=> maximum value with given knapsack weight limit
*/
