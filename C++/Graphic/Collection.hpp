#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <iostream>
#include "Vectors.hpp"

using namespace std;

struct Light
{
    Vec_3_f position;
    float intensity;

    Light (const Vec_3_f& p, const float& l): position(p), intensity(l) {}
};

struct Material
{
    Vec_3_f diffuse_color;
    
    bool is_reflective = false;
    bool is_refractive = false;

    float index_of_refraction;

    Material (const Vec_3_f& color): diffuse_color(color) {}
    Material (const Vec_3_f& color, bool reflective): diffuse_color(color), is_reflective(reflective) {}
    Material (const Vec_3_f& color, bool reflective, bool refractive): diffuse_color(color), is_reflective(reflective), is_refractive(reflective) {}
    Material (const Vec_3_f& color, bool reflective, bool refractive, float ior): 
             diffuse_color(color), is_reflective(reflective), is_refractive(refractive), index_of_refraction(ior) {}
    Material (): diffuse_color() {}

    float get_ior ()
    {
        return is_refractive ? index_of_refraction : 1;   
    }
};

struct Object
{
    Material material;
    virtual bool ray_intersect (const Vec_3_f&, const Vec_3_f&, float&) const = 0;
    virtual Vec_3_f normal (const Vec_3_f&) const = 0;

    virtual bool ray_intersect () const { return false; }
    virtual Vec_3_f normal () const { return Vec_3_f{}; }
};

#endif