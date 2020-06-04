#ifndef SHAPES_H
#define SHAPES_H

using namespace std;



class Shape {
    public:
        virtual double area() const = 0;
};

class Rectangle : public Shape
{
    protected:
        double a, b;
    public:
        Rectangle(double a, double b) 
        {
             this->a = a;
             this->b = b;
        }
        Rectangle(const Rectangle& r)
        { 
            a = r.a;
            b = r.b;
        }
        ~Rectangle(){}

        double area() const override { return a * b; }
};

class Square : public Rectangle
{
    public:
        Square(double a) : Rectangle(a, a) {}
        Square(const Square& s) : Rectangle(s.a, s.b) {}
        ~Square(){}
};

class Circle : public Shape
{
    protected:
        double r;
    public:
        Circle(double n): r(n) {}
        Circle(const Circle& o): r(o.r) {}
        ~Circle() {}

        double area() const override { return r * r * 3.1415926535; }
};


#endif