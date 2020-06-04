#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <math.h>

using namespace std;

class Expression {
    protected:
    virtual double evaluate() = 0;
};

class SineIntegral: public Expression {
private:
    double dx;
    double x1, x2;
public:
    SineIntegral(double dx, double x1, double x2): dx{dx}, x1{x1}, x2{x2} {}
    
    double evaluate() override {
        double x = x1;
        double acc{0.0};
        while (x <= x2) {
            acc += sin(x) * dx;
            x += dx;
        }
        return acc;
    }
};

class CosineIntegral : public Expression
{
    double x1, x2, dx;

    public:
        CosineIntegral(double x, double y, double dy)
        {
            x1 = x;
            x2 = y;
            dx = dy;
        }

        double evaluate() override
        {

        }
};

template <typename T, size_t S>
class Sum : public Expression
{
    T numbers [S];
    public:

        Sum(T (&arr)[S])
        {
            for(int i = 0; i < S; i++)
            {
                numbers[i] = arr[i];
            }
        }

        double evaluate() override 
        {
            double acc = 0;

            for(auto x : numbers)
            {
                acc += x;
            }

            return acc;
        }
};

#endif