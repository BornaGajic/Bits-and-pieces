#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;

int main ()
{
    queue<int> q;
    stack<int> s;
    priority_queue<int> pq;
    vector<int> out, v1, v2, v3, helper;

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)    
    {
        int command, x;
        cin >> command >> x;

        if (command == 1)
        {
            q.push(x);
            s.push(x);
            pq.push(x);
            helper.push_back(x);
        }
        else
        {
            out.push_back(x);
            v1.push_back(q.front()), q.pop();
            v2.push_back(s.top()), s.pop();
            v3.push_back(pq.top()), pq.pop();
        }
    }

    if (v1 == out)
        cout << "queue" << endl;
    else if (v2 == out)
        cout << "stack" << endl;
    else if (v3 == out)
        cout << "priority queue" << endl;
    else
    {
        bool flag = false;
        for (int x : out)
        {
            for(int y : helper)
            {
                if (x == y)
                {
                    cout << "undefined" << endl;
                    flag = true;
                    break;
                }
            }
            if (flag) break;
        }

        if (!flag) cout << "That is neither queue, priority queue nor stack!" << endl;
    }

    return 0;
}