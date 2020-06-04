#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main ()
{
    int n, result = 0;
    priority_queue<int> que;
    vector<int> v;

    cin >> n;
    v.resize(n);

    while (n--)
        cin >> v[n];

    sort(v.begin(), v.end());
    
    que.push(v[0] + v[1]);
    
    for (int i = 2; i < v.size(); i++)
        que.push(v[i] + que.top());

    while (que.size() != 0)
    {
        result += que.top();
        que.pop();
    }
    
    cout << result << endl;
    
    return 0;
}