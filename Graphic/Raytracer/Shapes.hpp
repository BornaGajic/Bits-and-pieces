#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <iostream>

#include "Vectors.hpp"
#include "Collection.hpp"

using namespace std;

struct Sphere : Object // public inheritance
{
    Vec_3_f c;
    float r;
    
    Sphere (const Vec_3_f& c, const float& r, const Material& m)
    {
        this->c = c;
        this->r = r;
        Object::material = m;
    }

    bool ray_intersect (const Vec_3_f& p, const Vec_3_f& d, float& t) const
    {
        Vec_3_f v = c - p;
        Vec_3_f pc;

        if (d * v < 0) return false;
        else
        {
            pc = p + d * ((d * v) / d.norm());

            if ((c - pc) * (c - pc) > r * r) return false;
            else
            {
                float dist = sqrt(r * r - (c - pc) * (c - pc));

                if (v * v > r * r)
                    t = (pc - p).norm() - dist;
                else
                    t = (pc - p).norm() + dist;

                return true;
            }
        }
    }

    Vec_3_f normal (const Vec_3_f& p) const 
    {
        return (p - c).normalize();
    }
};

struct Triangle : Object
{
    Vec_3_f a, b, c;

    Triangle (const Vec_3_f& a, const Vec_3_f& b, const Vec_3_f& c, const Material& m)
    {
        this->a = a;
        this->b = b;
        this->c = c;

        Object::material = m;
    }

   bool ray_intersect (const Vec_3_f& p, const Vec_3_f& d, float& t) const
   {
       float detA = determinant(a - b, a - c, d);
       float beta = determinant(a - p, a - c, d) / detA;
       float gamma = determinant(a - b, a - p, d) / detA;
       float alpha = 1 - beta - gamma;
       float t0 = determinant (a - b, a - c, a - p) / detA;

        if (t0 < 0) return false;

        if (min(alpha, min(beta, gamma)) >= 0 &&
            max(alpha, max(beta, gamma)) <= 1   )
        {
            t = t0;
            return true;
        }
        else return false;
   }

   Vec_3_f normal () const override
   {
       return cross(b - a, c - a).normalize();
   }
};

#endif