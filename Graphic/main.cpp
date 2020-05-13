#include <iostream>

#include "Scene.hpp"

using namespace std;

int main ()
{
    Material ivory(Vec_3_f(0.4, 0.4, 0.3));
    Material red_rubber(Vec_3_f(0.3, 0.1, 0.1));
    Material green(Vec_3_f(0.1, 0.7, 0.5));
    Material red(Vec_3_f(0.8, 0.1, 0.2));

    Material red_reflection(Vec_3_f(0.8, 0.1, 0.2), true);
    Material red_reflection_refraction(Vec_3_f(0.8, 0.1, 0.2), true, true);
    
    Sphere s1(Vec_3_f(-3,    0,   -16), 2, ivory);
    Sphere s2(Vec_3_f(-1.0, -1.5, -12), 2, red);
    Sphere s3(Vec_3_f( 1.5, -0.5, -18), 3, red_rubber);
    Sphere s4(Vec_3_f( 7,    5,   -18), 4, green);

    Sphere s5(Vec_3_f(-5,    -5,   -10), 3, red_reflection_refraction);

    Objects objs = {&s1, &s2, &s3, &s4, &s5};

    Lights lights = {Light(Vec_3_f(-20, 0, 20), 1.5)};

    render(objs,lights);

    return 0;
}