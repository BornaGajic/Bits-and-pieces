#include <variant>
#include <iostream>
#include <string>

using namespace std;

class Bar
{
    int bar_int;
    string bar_string;

    public:

    //default values
    Bar (int i = 0, string s = "default"): bar_int(i), bar_string(s) {}

    friend ostream& operator<<(ostream& out, const Bar& b)
    {
        out << "bar_int: " << b.bar_int << ", bar_string " << b.bar_string;

        return out;
    }
};

// FUNCTOR (can create objects that look like functions)
struct my_variant_printer_visitor 
{
    void operator()(int x)
    {
        cout << "int: " << x << endl;
    }
    void operator()(const Bar& b)
    {
        cout << "Bar: " << b << endl;
    }
    void operator()(const string& s)
    {
        cout << "String: " << s << endl;
    }
    void operator()(monostate)
    {
        cout << "Monostate" << endl;
    }
};

// implicit conversion to variant
variant<int, Bar, string, std::monostate> show_me_CONVERSION (const string& convert_me)
{
    if (!convert_me.empty())
        return convert_me;
    else
        return monostate{};
}

int main ()
{   
    Bar b {100, "Hello world!"};
    Bar b_default {};

    variant<int, Bar, string, std::monostate> my_variant;

    //my_variant = 5;
    //my_variant = "Variants are cool";
    my_variant = b;
    //my_variant = monostate{};

    cout << my_variant.index() << endl; // checks which type is currently active (<type1:0, type2:1, ..., typen:n-1>)

    if (holds_alternative<string>(my_variant)) // checks if variant is holding a string
    {
        cout << "my variant is holding a string" << endl;

        cout << std::get<string>(my_variant) << endl;
    }
    else if (holds_alternative<Bar>(my_variant))
    {
        cout << "my variant is holding a Bar :O" << endl;
        cout << std::get<Bar>(my_variant) << endl;
    }
    else if (holds_alternative<monostate>(my_variant))
    {
        cout << "monostate" << endl;
    }

    cout << endl;

     //std::visit internally invokes functor (visitor) on a given variant

    // MONOSTATE THROWS ERROR -> no overloaded function for monostate
    //auto PrintVisitor = [](const auto& t) { std::cout << t << "\n"; };
    //visit(PrintVisitor, my_variant);

    cout << endl;

    visit(my_variant_printer_visitor{}, my_variant);
    visit(my_variant_printer_visitor{}, show_me_CONVERSION("This works!"));

    // reference: https://www.bfilipek.com/p/start-here.html

    return 0;
}