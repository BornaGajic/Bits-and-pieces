#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "Person.h"

using namespace std;

class Employee: public Person {
    protected:
        string company;
    public:
        
        Employee(){}
        Employee(const Employee& employee)
        {
            firstName = employee.firstName;
            lastName = employee.lastName;
            age = employee.age;
            company = employee.company;
        }
        Employee(const string& firstName, const string& lastName, unsigned int age, const string& company)
        : Person(firstName, lastName, age)
        {
            this->company = company;
        }

        ostream& printPerson(ostream& os) const override
        {
            os << firstName << " " << lastName << " " << age << " " << company << endl;
            
            return os;
        }
 };


#endif