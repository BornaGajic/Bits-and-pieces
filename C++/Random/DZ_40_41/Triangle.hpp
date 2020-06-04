#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "GeomShape.hpp"

using namespace std;

class Triangle : virtual public GeomShape
{
    double a, b, c;

    public:
        Triangle () = delete;
        Triangle (double A, double B, double C): a(A), b(B), c(C) 
        {
            assert(a > 0);
            assert(b > 0);
            assert(c > 0);
        }

        double area () override
        {
            double s = (a + b + c)/2;
            return sqrt(s*(s - a)*(s - b)*(s - c));
        }

        void print () override 
        { 
            cout << "Triangle: " << endl;
            cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
            cout << "Area of your triangle: " << area() << endl << endl;
        }

        bool operator<(GeomShape &g) override
        {
            return area() < g.area();
        }
};


#endif