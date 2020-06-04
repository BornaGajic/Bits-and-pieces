#include <iostream>
#include "HashTable.h"

using namespace std;

struct ID
{
    const string email;
    unsigned int age;

    friend ostream& operator<< (ostream& os, const ID& id)
    {
        os << "email: " << id.email << endl;
        os << "age: " << id.age << endl;
    }
};

int main()
{
    ID b{"borna.gajic@gmail.com", 19}, k{"karlo.gajic@gmail.com", 18}, i{"ivona.vidovic.14@gmail.com", 19};

    HashTable<ID, 3> table;

    table.insert(b.email, b);


    cout << table.search("borna.gajic@gmail.com") << endl;

    return 0;
}