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

    Material (const Vec_3_f& color): diffuse_color(color) {}
    Material (): diffuse_color() {}
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