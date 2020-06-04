#include <iostream>
#include <string>

using namespace std;

string Ukrcaj (int economy, int business)
{
    string* result = new string{};
    
    int passengerB = 2;
    while (business != 0)
    {
        result->push_back('B');
        
        passengerB--;
        business--;

        if (!passengerB)
        {
            if (economy > 0)
                result->push_back('E'), economy--;

            passengerB = 2;
        }

        if (!business)
            for (int i = 0; i < economy; i++)
                result->push_back('E');
    }

    return *result;
}

int main () 
{
    int economy, business;
    cin >> business >> economy;

    cout << Ukrcaj(economy, business) << endl;

    return 0;
}