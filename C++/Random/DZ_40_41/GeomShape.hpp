#ifndef GEOMSHAPE_HPP
#define GEOMSHAPE_HPP

using namespace std;

#include <math.h>
#include <assert.h>

struct GeomShape
{
    virtual double area () { assert(false); }
    virtual void print () { assert(false); }
    virtual bool operator<(GeomShape&) { assert(false); }      
};

#endif