#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> combs; // vektor za sve n-arne kombinacije od slova CHR
vector<string> a; // prve mogucnosti zamjene od dva slova
vector<string> b; // druge zamjene na i-tim pozicijama
vector<string> CHR = {"a", "b", "c", "d", "e", "f"};

int counter = 0; // broji caseove koji valjaju (vrate 'a' i len = 1)

// dobije string i provrti kroz vektor a, ako postoji podudarnost onda se resetira 
// while i krene od pocetka, sve dok ili ne dode do kraja ili ne postane duljine 1
// ako je duljine 1 i na kraju je 'a', counter++
void test_input (string& s)
{
    int i = 0;
    while (i < a.size() && s.size() != 1)
    {  
        if (s.substr(0, 2) == a[i])
        {
            s = b[i] + s.substr(2);

            i = 0;
        }
        else i++;
    }

    counter = s[0] == 'a' && s.size() == 1 ? counter + 1 : counter;

    return;
}

// brute force nacin uzimanja svih kombinacija, 
// nakon pusha zovem test_input na zadnji dodani element
void generate_all_combinations (int n)
{
    switch (n)
    {
        case 2:
            for (auto& a : CHR)
                for (auto& b : CHR)
                    combs.push_back(a + b), test_input(combs.back());
            break;
        case 3:
            for (auto& a : CHR)
                for (auto& b : CHR)
                    for (auto& c : CHR)
                        combs.push_back(a + b + c), test_input(combs.back());
            break;
        case 4:
            for (auto& a : CHR)
                for (auto& b : CHR)
                    for (auto& c : CHR)
                        for (auto& d : CHR)
                            combs.push_back(a + b + c + d), test_input(combs.back());
            break;
        case 5:
            for (auto& a : CHR)
                for (auto& b : CHR)
                    for (auto& c : CHR)
                        for (auto& d : CHR)
                            for (auto& e : CHR)
                                combs.push_back(a + b + c + d + e), test_input(combs.back());
            break;
        case 6:
            for (auto& a : CHR)
                for (auto& b : CHR)
                    for (auto& c : CHR)
                        for (auto& d : CHR)
                            for (auto& e : CHR)
                                for (auto& f : CHR)
                                    combs.push_back(a + b + c + d + e + f), test_input(combs.back());
            break;
    
    default:
        break;
    }
    return;
}

int main ()
{
    vector<string> x;

    int n, q;

    cin >> n >> q;
    cin.ignore();

    x.resize(q);

    while (q--)
        getline(cin, x[q]);

    // x je vektor koji uzme cijeli input, pa ga dva fora dolje
    // razdvoje na vektor a (dvoclani elementi) i vektor b (jednoclani elementi)
    for (auto& k : x)
    {   
        string s;
        for (int i = 0; i < k.length(); i++)
        {
            if (k[i] != ' ')
                s += k[i];
            else
            {
                a.push_back(s);
                s.clear();
                s += k[i + 1];
                b.push_back(s);
                s.clear();
            }
        }
    }

    generate_all_combinations(n);

    cout << counter << endl;
    
    return 0;
}