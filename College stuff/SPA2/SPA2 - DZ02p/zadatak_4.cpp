#include <iostream>

using namespace std;

// n i m su ulazne varijable, 
// num_of_steps_result je varijabla koja odrzava najmanji broj koraka do rijesenja
// isResult prati ako sam nasao jedno rijesenje
int n, m, num_of_steps_result = INT_MAX; 
bool isResult = false;

// steps je parametar koji redom prati korake za svaki poziv fje solve
// odnosno u stablu koje se izgradi, prati za svaki element koliko je poziva fje
// solve bilo nakon odredenog elementa
// ako se pronade rijesenje, isResult postaje true i num_of_steps_result postaje broj koraka 
// koji je trebao da se pronade rijesenje i ono je sada gornja granica. (steps >= steps_result) return
// ako se pronade bolje rijesenje onda toliko stepova postaje steps_result.
void solve (int a, int b, int steps)
{
    if (a == b)
    {
        if (steps <= num_of_steps_result)
        {
            num_of_steps_result = steps;
            isResult = true;
        }

        return;
    }
    else if (a <= 0)
        return;
    else if (a > b)
    {
        if (num_of_steps_result >= steps + (a - b))
            num_of_steps_result = steps + (a - b);
        else
            return;

        isResult = true;
        return;
    }
    else
    {
        if (isResult)
        {
            if (steps >= num_of_steps_result)
                return;
        }
        else if (a * 2 == b || a - 1 == b)
        {
            num_of_steps_result = ++steps <= num_of_steps_result ? steps : num_of_steps_result;
            isResult = true;
            return;
        }

        solve(a * 2, b, steps + 1);
        solve (a - 1, b, steps + 1);
    }
}


int main ()
{   
    cin >> n >> m;

    if (n > m)
        cout << n - m << endl;
    else if (n == m) cout << 0 << endl;
    else
    {
        solve(n, m, 0);
        cout << num_of_steps_result << endl;
    }

    return 0;
}