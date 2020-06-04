#include <iostream>
#include <utility>
#include <math.h>
using namespace std;

struct Point;
double dot_product(Point A, Point B);
Point cross_product(Point A, Point B);
double norm(Point A);

struct Point
{
    double a, b, c;

    Point (double a1, double b2, double c3): a(a1), b(b2), c(c3) {}

    Point operator- (const Point& x)
    {
        double A = a - x.a, B = b - x.b, C = c - x.c;
        
        Point Point{A, B, C};

        return Point;
    }

    Point operator+ (const Point& x)
    {
        double A = a + x.a, B = b + x.b, C = c + x.c;
        
        Point Point{A, B, C};

        return Point;
    }

    Point operator* (double x)
    {
        return Point{a * x, b * x, c * x};
    }
};

struct Ray
{
    Point e, d;
    
    Ray (Point b, Point c): e(b), d(c) {}
    
    // C = (x, y, z), center, r radius, -1 => no solution
    pair<Point, Point> ray_sphere_intersection (Point C, double r) 
    {
        double D = sqrt(pow(dot_product(d, e - C), 2) - (pow(norm(e - C), 2) - r*r));

        if (D > 0) // 2 solutions
        {
            double D1, D2;
            D1 = - dot_product(d, e - C) + D;
            D2 = - dot_product(d, e - C) - D;

            return make_pair(e + d * D1, e + d * D2);
        }
        else if (D == 0) // 1 solution
        {
            double D1;
            D1 = - dot_product(d, e - C);

            if (D1 + D == 0)
            {
                D1 += D;
                return make_pair(e + d * D1, Point{-1,-1,-1});
            }
            else
            {
                D1 -= D;
                return make_pair(e + d * D1, Point{-1,-1,-1});
            }
        }
        else
        {
            cout << "No solutions" << endl;

            return pair<Point, Point>{Point{-1,-1,-1}, Point{-1,-1,-1}};
        }
    }

    Point ray_triangle_intersection (Point A, Point B, Point C)
    {
        // normal at point A
        //double denom_n = pow(norm(cross_product(B - A, C - A)), -1);
        Point n = cross_product(B - A, C - A);
        
        double D = dot_product(n, A), t; // Ax + By + Cz = D, plane equation

        if (dot_product(n, d))
            t = (D - dot_product(n, e)) * pow(dot_product(n, d), -1);
        else
        {
            cout << "Ray is parallel to the triangle!";
            return Point{-1, -1, -1};
        }

        Point P = e + d * t; // possible intersection

        // determines if P is inside the triangle 
        if (dot_product(cross_product(B-A, P-A), n) >= 0)
            if (dot_product(cross_product(C-B, P-B), n) >= 0)
                if (dot_product(cross_product(A-C, P-C), n) >= 0)
                    return P;
        
        return Point{-1, -1, -1};
    }

    Point ray_square_intersection (Point A, Point B, Point C, Point D)
    {
        Point x = ray_triangle_intersection(A, D, C);
        Point y = ray_triangle_intersection(A, B, C);

        if (x.a == -1)
        {
            if (y.a == -1)
            {
                cout << "No intersection" << endl;
                return Point{-1, -1, -1};
            }
            else
                return y;
        } 
        else
            return x;
    }
};

Point cross_product (Point A, Point B)
{
    double x = A.b*B.c - A.c*B.b;
    double y = - A.a*B.c + A.c*B.a;
    double z = A.a*B.b - A.b*B.a;

    return Point{x, y, z};
}

double dot_product (Point A, Point B)
{
    return A.a * B.a + A.b * B.b + A.c * B.c;
}

double norm (Point A)
{
    return sqrt(A.a*A.a + A.b*A.b + A.c*A.c);
}

int main ()
{
    Point e1 (-4.04, -3.7, 3.02);
    Point d1 (0.66, 0.57, -0.5);
    Point center (0, 0, 0);

    Ray r1 (e1, d1);

    pair<Point, Point> par = r1.ray_sphere_intersection(center, 4.16);

    cout << par.first.a << " " << par.first.b << " " << par.first.c << endl;
    cout << par.second.a << " " << par.second.b << " " << par.second.c << endl;

    Point e2 (1.83, 5.33, 2.47);
    Point d2 (0.68, -0.4, -0.62);
    
    Ray r2 (e2, d2);

    Point A{4.25, 3.33, 2.5}, B{3.79, 6.07, 0}, C{2.84, 3.03, 0};
    Point Tintersection = r2.ray_triangle_intersection(A, B, C);

    cout << Tintersection.a << " " << Tintersection.b << " " << Tintersection.c << endl;

    Point e3 (3.7, 4.76, 2);
    Point d3 (-0.49, -0.87, -0.07);
    
    Ray r3 (e3, d3);

    Point a{3, 0, 0}, b{0, 0, 3}, c{0, 0, 0}, d{3, 0, 3};
    Point Sintersection = r3.ray_square_intersection(a, c, b, d);

    cout << Sintersection.a << " " << Sintersection.b << " " << Sintersection.c << endl;


    return 0;
}