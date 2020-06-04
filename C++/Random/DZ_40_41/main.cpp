#include <vector>
#include <string>
#include "Rectangle.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
#include "Hexagon.hpp"

using namespace std;
/*
upOrdown = true => 1, 2, 3, ...
         = false => ..., 3, 2, 1
*/
void bubbleSort (GeomShape** shapes, int S, bool upOrdown)
{
    int i = S - 1, border = 0;
    for(int x = S - 1; x >= 0; x--)
    {
        do
        {
            if (upOrdown)
            {
                if(shapes[i]->area() <= shapes[i - 1]->area())
                    swap(shapes[i], shapes[(i - 1)]), i--;
            }
            else
            {
                if(shapes[i]->area() >= shapes[i - 1]->area())
                    swap(shapes[i], shapes[(i - 1)]), i--;
            }

            i--;
        }
        while(i > border);

        i = S - 1;
    }
}

GeomShape* generator (string s) 
{ 
    vector<double> args;
    
    if (s.find_first_of(" ") != string::npos)
    {
        int index_after_shape = s.find_first_of(" "), counterOfArgs = 0;
        string shape { s.substr(0, index_after_shape) };
        string arg;
        
        for (int i = index_after_shape + 1; i < s.size(); i++)
        {
            if (s[i] != ' ' && (isdigit(s[i]) || s[i] == '.'))
            {
                arg.push_back(s[i]);
                
                if (i == s.size() - 1)
                {
                    args.push_back(stod(arg));
                    counterOfArgs++;
                    arg = "";
                }
            }
            else
            {
                if (s[i] != ' ') return nullptr;
                else if (s[i] == ' ' && i == s.size() - 1) return nullptr;
                else if (arg == "") return nullptr;

                args.push_back(stod(arg));
                counterOfArgs++;
                arg = "";
            }
        }

        if (shape == "Rectangle" && counterOfArgs == 2)
            return new Rectangle(args[0], args[1]);
        else if (shape == "Circle" && counterOfArgs == 1)
            return new Circle(args[0]);
        else if (shape == "Hexagon" && counterOfArgs == 1)
            return new Hexagon(args[0]);
        else if (shape == "Triangle" && counterOfArgs == 3)
            return new Triangle(args[0], args[1], args[2]);
        else
            return nullptr;
    }
    
    return nullptr;
}

int main ()
{
    GeomShape* shapes [11] = 
    {
        new Triangle(3, 4, 5), new Rectangle(2, 4), 
        new Circle(10), new Triangle(2, 2, 3), new Circle(3),
        new Circle(5), new Rectangle(1, 10), new Triangle(2, 4, 5), 
        new Circle(1), new Rectangle(2, 2), new Hexagon(3)
    };

    for (int i = 0; i < 11; i++)
        shapes[i]->print();

    bubbleSort (shapes, 11, true);

    cout << "---------------" << endl;
    
    for (int i = 0; i < 11; i++)
        shapes[i]->print();

    GeomShape* gs = generator("Circle 11");
    
    if (gs)
        gs->print();
    else 
        cout << "wrong input";

    return 0;
}