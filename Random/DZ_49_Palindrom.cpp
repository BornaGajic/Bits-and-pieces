#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main () 
{
    string str;
    stack<char> s1, s2, temp;
    
    getline(cin, str);
    
    for(char& c : str)
        s1.push(c);

    temp = s1;
    while(temp.size() != 0)
        s2.push(temp.top()), temp.pop();
    
    if (s1 == s2) cout << "DA" << endl;
    else cout << "NE" << endl;
    
    return 0;
}