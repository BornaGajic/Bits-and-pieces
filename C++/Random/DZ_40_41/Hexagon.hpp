#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include <iostream>
#include "GeomShape.hpp"

using namespace std;

class Hexagon : virtual public GeomShape
{
    double a;

    public:
        Hexagon () = delete;
        Hexagon (double A): a(A) { assert(a > 0); }

        double area () override
        {
            return (3*sqrt(3) * a * a)/2;
        }

        void print () override 
        { 
            cout << "Hexagon: " << endl;
            cout << "a = " << a << endl;
            cout << "Area of your hexagon: " << area() << endl << endl;
        }

        bool operator<(GeomShape &g) override
        {
            return area() < g.area();
        }
};


#endif