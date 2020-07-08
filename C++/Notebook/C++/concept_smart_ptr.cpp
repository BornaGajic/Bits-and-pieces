#include <type_traits>
#include <concepts>
#include <memory>
#include <math.h>

#include <iostream>

template <typename T>
concept well_defined_math_type = std::is_fundamental<T>::value;

enum class Spices {Salt, Pepper, Empty};
// Spices could've been std::variant<Salt, Pepper, std::monostate (aka Empty)>

template <well_defined_math_type T>
class SpiceContainer
{
    protected:
        std::unique_ptr<Spices> spice;
    public:
        SpiceContainer () {}
        constexpr SpiceContainer (Spices object): spice(std::make_unique<Spices>(object)) {}

        virtual constexpr double area () const = 0;
};

template <well_defined_math_type T>
class SpiceRack : public SpiceContainer<T>
{
    // dimensions
    T radius;
    T height;

    using SpiceContainer<T>::spice;

    public:
        constexpr SpiceRack (T r, T h): SpiceContainer<T>(Spices::Empty), radius(r), height(h)
        {
            std::cout << "Default constructor!\n";
        }
        SpiceRack (Spices spice, T r, T h): SpiceContainer<T>(spice), radius(r), height(h)
        {
            std::cout << "Default constructor!\n";
        }
        SpiceRack (const SpiceRack<T>& tr): SpiceContainer<T>(tr.get_spice()), radius(tr.radius), height(tr.height)
        {
            std::cout<< "Copy constructor!\n";
        }
        SpiceRack (SpiceRack<T>&& tr): SpiceContainer<T>(), radius(tr.radius), height(tr.height)
        {
            std::cout << "Move constructor!\n";
            spice = std::move(tr.spice);
        }

        const auto get_spice () const 
        {
            return *spice;
        }

        constexpr double area () const
        {
            return M_PI * radius * radius * height;
        }
};

SpiceRack<int> make_rvalue_spicerack (int a, int b, Spices spice = Spices::Empty)
{
    return std::move(SpiceRack<int>{spice, a, b});
}

int main ()
{
    SpiceRack<int> t1 {Spices::Salt, 11, 23};
    SpiceRack<int> t2 = make_rvalue_spicerack(1, 2, Spices::Pepper); // std::move turns its argument to rvalue, even if it isn't
    //SpiceRack<Spices> t3 {1,2}; requires well_defined_type -> concept
    
    if (t2.get_spice() == Spices::Salt)
    {
        std::cout << "Salt" << std::endl;
    }
    else
    {
        std::cout<< "Something else" << std::endl;
    }
    
    return 0;
}