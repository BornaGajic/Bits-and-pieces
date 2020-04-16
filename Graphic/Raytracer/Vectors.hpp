#ifndef VECTORS_HPP
#define VECTORS_HPP

#include <iostream>
#include <cassert>
#include <array>
#include <math.h>

using namespace std;

template <size_t dim, typename T>
class Vector
{
    array<T, dim> data_;

    public:    
        Vector()
        {
            data_.fill(T());
        }
        
        T& operator[] (const size_t i)
        {
            assert(i < dim);
            return data_[i];
        }

        const T& operator[] (const size_t i ) const
        {
            assert(i < dim);
            return data_[i];
        }
};

typedef Vector<2, float> Vec_2_f;
typedef Vector<3, float> Vec_3_f;
typedef Vector<3, int> Vec_3_i;
typedef Vector<3, float> Vec_4_f;

template <typename T>
struct Vector<2, T>
{
    T x, y;

    Vector(): x(T()), y(T()) {}
    Vector(T X, T Y): x(X), y(Y) {}

    T& operator[] (const size_t i)
    {
        assert(i < 2);
        return i ? y : x;
    }

    const T& operator[] (const size_t i) const
    {
        assert(i < 2);
        return i ? y : x;
    }
};

template <typename T>
struct Vector<3, T>
{
    T x, y, z;

    Vector(): x(T()), y(T()), z(T()) {}
    Vector(T X, T Y, T Z): x(X), y(Y), z(Z) {}

    T& operator[] (const size_t i)
    { 
        assert(i<3);
        return i<=0 ? x : (1==i ? y : z);
    }
    const T& operator[](const size_t i) const
    { 
        assert(i<3);
        return i<=0 ? x : (1==i ? y : z);
    }

    float norm ()
    {
        return sqrt(x*x + y*y + z*z);
    }

    float norm () const
    {
        return sqrt(x*x + y*y + z*z);
    }

    Vector<3, T>& normalize (T l = 1)
    {
        *this = (*this) * (l / norm());
        return *this;
    }
};

template <typename T>
struct Vector<4, T>
{
    T x, z, y, w;

    Vector(T X, T Y, T Z, T W): x(X), y(Y), z(Z), w(W) {}

    T& operator[] (const size_t i)
    {
        assert(i < 4);
        switch (i)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        case 3:
            return w;
            break;
        default:
            break;
        }
    }

    const T& operator[] (const size_t i) const
    {
        assert(i < 4);
        switch (i)
        {
        case 0:
            return x;
            break;
        case 1:
            return y;
            break;
        case 2:
            return z;
            break;
        case 3:
            return w;
            break;
        default:
            break;
        }
    }
};

#pragma region operator_overloading

template <size_t dim, typename T>
T operator* (const Vector<dim, T>& lhs, const Vector<dim, T> rhs)
{
    T result = T();

    for (size_t i = dim; i--; result += lhs[i] * rhs[i]);

    return result;
}

template <size_t dim, typename T>
Vector<dim, T> operator+ (Vector<dim, T> lhs, const Vector<dim, T>& rhs)
{
    for (size_t i = dim; i--; lhs[i] += rhs[i]);

    return lhs;
}

template <size_t dim, typename T>
Vector<dim, T> operator- (Vector<dim, T> lhs, const Vector<dim, T>& rhs)
{
    for (size_t i = dim; i--; lhs[i] -= rhs[i]);

    return lhs;
}

template <size_t dim, typename T, typename K>
Vector<dim, T> operator* (const Vector<dim, T>& lhs, const K& rhs)
{
    Vector<dim, T> result;
    for (size_t i = dim; i--; result[i] = lhs[i] * rhs);

    return result;
}

template <size_t dim, typename T>
Vector<dim, T> operator- (const Vector<dim, T>& lhs)
{
    return lhs * T(-1);
}

template <size_t dim, typename T>
ostream& operator<< (ostream& out, const Vector<dim, T>& vec)
{
    for (unsigned int i = 0; i < dim; i++)
        out << vec[i] << " ";
    
    return out;
}

#pragma endregion operator_overloading

// cross product
template <typename T>
Vec_3_f cross (Vector<3, T> v1, Vector<3, T> v2)
{
    return Vec_3_f(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}

template <typename T>
float determinant(const Vector<3, T>& v1, const Vector<3, T>& v2, const Vector<3, T>& v3)
{
    return (v1.x * (v2.y*v3.z-v2.z*v3.y ) - v2.x * (v1.y*v3.z-v1.z*v3.y ) + v3.x * (v1.y*v2.z-v1.z*v2.y ));
}

#endif