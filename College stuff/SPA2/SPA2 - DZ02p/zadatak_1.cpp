#include <iostream>
#include <vector>
#include <string>
using namespace std;

// euklidov algoritam za odredivanje rel. prost. brojeva
int gcd (int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

string solve ()
{
    vector<int> happyM, happyF;
    int n, m, b, g;
    bool rel_prost;

    cin >> n >> m;
    rel_prost = gcd(n, m) == 1 ? true : false; // Ako su relativno prosti i postoji jedan/jedna sretna onda ce svi biti sretni
    cin >> b;
    
    if(b && rel_prost) return "YES";

    happyM.resize(b);

    while (b--)
        cin >> happyM[b];

    cin >> g;
    if (g && rel_prost) return "YES";
    happyF.resize(g);

    while (g--)
        cin >> happyF[g];

    // U suprotnom, nakon punog kruga (kada se izvrte sve kombinacije) ce se znati jesu svi sretni ili ne
    int i = 0;
    do
    {
        bool flag_m = false, flag_f = false;

        for (int& x : happyM) // U happyM su svi sretni decki
        {
            if (x == i % n)
            {
                flag_m = true;
                break;
            }
        }

        for (int& y : happyF) // U happyF sve sretne cure
        {
            if (y == i % m) // ako u trenutnoj kombinaciji postoji sretna cura onda je flag_f true => ako m nije sretan sad je
            {
                flag_f = true;
                break;
            }
        }
        
        // m sretan, f ne => sad je i f sretna, i obratno za else
        if (flag_m && !flag_f) happyF.push_back(i % m);
        else if (!flag_m && flag_f) happyM.push_back(i % n);

    } while (++i, i % n != 0 || i % m != 0);

    if (happyF.size() + happyM.size() == n + m) return "YES"; // ako su svi sretni vrati yes ako ne vrati no
    else return "NO";
}

int main ()
{
    cout << solve() << endl;   

    return 0;
}