#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>
#include "GeomShape.hpp"

using namespace std;

class Rectangle : virtual public GeomShape
{
    double a, b;

    public:
        Rectangle () = delete;
        Rectangle (double A, double B): a(A), b(B)
        {
            assert(a > 0);
            assert(b > 0);
        }

        double area () override
        {
            return a * b;
        }

        void print () override 
        { 
            cout << "Rectangle: " << endl;
            cout << "a = " << a << ", b = " << b << endl;
            cout << "Area of your rectangle: " << area() << endl << endl;
        }

        bool operator<(GeomShape &g) override
        {
            return area() < g.area();
        }
};


#endif