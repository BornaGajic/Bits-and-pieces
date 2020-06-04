#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Person {
    protected:
        string firstName, lastName;
        unsigned int age;
    public:
        Person(){}
        Person(const Person& p)
        {
            firstName = p.firstName;
            lastName = p.lastName;
            age = p.age;
        }
        Person(const string& firstName, const string& lastName, unsigned int age)
        {
            this->firstName = firstName;
            this->lastName = lastName;
            this->age = age;
        }
        
        void setAge(unsigned int age){ this->age = age; }
        Person& operator=(const Person& p)
        {
            firstName = p.firstName;
            lastName = p.lastName;
            age = p.age;

            return *this;
        }
        virtual ostream& printPerson(ostream& os) const
        {
            os << firstName << " " << lastName << " " << age << endl;
            
            return os;
        }
};




#endif