#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "GeomShape.hpp"

using namespace std;

class Circle : virtual public GeomShape
{
    double r;

    public:
        Circle () = delete;
        Circle (double R): r(R) { assert(r > 0); }

        double area () override
        {
            return r * r * 3.14159265358979323846;
        }

        void print () override 
        { 
            cout << "Circle: " << endl;
            cout << "r = " << r << endl;
            cout << "Area of your circle: " << area() << endl << endl;
        }

        bool operator<(GeomShape &g) override
        {
            return area() < g.area();
        }
};


#endif