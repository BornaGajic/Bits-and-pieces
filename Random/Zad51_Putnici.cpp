#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

int main()
{
    priority_queue<int> que;
    vector<int> priorityVector;
    vector<int> bridge;
    int n; 
    cin >> n;

    while(n--)
    {
        int x, i = 5;
        while(cin >> x, x != -1)
            que.push(x);

        while(i-- && que.size() != 0)
            bridge.push_back(que.top()), que.pop();

        for (int x : bridge) priorityVector.push_back(x);
        bridge.clear();
    }

    for(auto &x : priorityVector)
      cout << x << " ";

    return 0;
}