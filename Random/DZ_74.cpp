#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main ()
{
    vector<int> sweets, subSweets, result;
    int n, m;
    cin >> n >> m;
    
    sweets.resize(n);

    while (n--)
        cin >> sweets[n];

    sort(sweets.begin(), sweets.end());

    for(auto& x : sweets)
    {
        subSweets.push_back(x);

        sort(subSweets.begin(), subSweets.end(), greater<int>());

        int semires = 0, days = 1, temp = m;
        for (int& y : subSweets)
        {
            semires += y * days;

            if (--temp == 0)
                days++, temp = m;
        }

        result.push_back(semires);
    }

    for (auto& x : result)
        cout << x << " ";
    
    return 0;
}