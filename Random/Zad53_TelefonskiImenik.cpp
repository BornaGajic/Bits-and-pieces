#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*  
    A, B, C maps to 2
    D, E, F maps to 3
    G, H, I maps to 4
    J, K, L maps to 5
    M, N, O maps to 6
    P, R, S maps to 7
    T, U, V maps to 8
    W, X, Y maps to 9.

    Standard record for 
    telephone number is xxx-xxxx.

    Two phone numbers are the same
    if their standard record is same

    Sample input:
        12

        4873279
        ITS-EASY
        888-4567
        3-10-10-10
        888-GLOP
        TUT-GLOP
        967-11-11
        310-GINO
        F101010
        888-1200
        -4-8-7-3-2-7-9-
        487-3279

    Sample output:

    310-1010 2 
    487-3279 4
    888-4567 3
*/

int main ()
{
    int n;
    unordered_map<char, int> map;
    unordered_map<string, int> dict;
    
    int flag_letters = 3, flag_values = 2;
    for (char chr = 'A'; chr <= 'Y'; chr++)
    {
        if (chr == 'Q') continue;

        else if (!flag_letters)
            flag_values++, flag_letters = 3;
        
        map[chr] = flag_values;

        flag_letters--;
    }

    std::cin >> n;
    std::cin.ignore();
    while (n--)
    {
        string s, l;
        getline(std::cin, s);

        int number = 0, flag = 1;
        for(int i = s.size() - 1; i >= 0; i--)
        {
            char c = s[i];

            if(isalpha(c))
            {
                for(auto& x : map)
                    if (x.first == c)
                    {
                        number += x.second * flag;
                        flag *= 10;
                        break;
                    }   
            }
            else if (ispunct(c))
                continue;
            else
                number += (c - '0') * flag, flag *= 10;
        }

        l = to_string(number);
        l.insert(l.begin() + 3, '-');
        dict[l]++;
    }

    cout << endl;
    bool isDifferent = true;
    for (auto& x : dict)
    {
        if (x.second > 1)
            cout << x.first << " " << x.second << endl, isDifferent = false;
    }
    
    if (isDifferent)
        cout << "All numbers are different!" << endl;

    return 0;
}