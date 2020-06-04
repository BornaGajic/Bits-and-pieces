#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main () 
{
    stack<char> st;
    string s, k;
    getline(cin, s);

    for (auto& x : s)
        st.push(x);
    
    while (st.size() != 0)
        k.push_back(st.top()), st.pop();
    
    if (s == k) cout << "DA";
    else cout << "NE";

    return 0;
}
