#include <iostream>
#include <list>
#include <utility>
#include <string>

using namespace std;

void SnakeCheck (list<pair<int, int>> &snake, string str) 
{
    string str_no_whitespace;
    
    for(char& c : str)
        if (c != ' ')
            str_no_whitespace.push_back(c);
    
    for (int i = 0; i < str_no_whitespace.size(); i++)
    {
        // prije nove operacije, a_i = a_i+1, a_0 = a_1
        list<pair<int, int>> temp;
        temp.push_back(snake.front());
        temp.push_back(snake.front());
        int flag = 1;
        for (auto& x : snake)
        {
            if(x == snake.back()) break;
            if (flag != 0)
            {
                flag--;
                continue;
            }
            temp.push_back(x);
        }
        snake = temp;
        
        if (str_no_whitespace[i] == 'L')
            snake.front().first--;
        else if (str_no_whitespace[i] == 'R')
            snake.front().first++;
        else if (str_no_whitespace[i] == 'U')
            snake.front().second++;
        else if (str_no_whitespace[i] == 'D')
            snake.front().second--;

        int counter = 0;
        for (auto& x : snake)
        {
            if (x == snake.front())
            {
                counter++;
                if (counter > 1)
                {
                    std::cout << "X" << endl;
                    return;
                }
            }
        }
    }

    std::cout << "OK" << endl;
}

int main ()
{
    list<pair<int, int>> snake;
    string commands;
    int n;
    cin >> n;

    for (int i = 0; i <= n; i++)
        snake.push_back(make_pair(i, 0));
    
    cin.ignore();
    getline(cin, commands);

    SnakeCheck(snake, commands);
    
    return 0;
}