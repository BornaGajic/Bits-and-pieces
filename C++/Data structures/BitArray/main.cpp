#include "BitArray.hpp"
#include <iostream>

int main ()
{
    BitArray<5> arr{0, 4, 3};
    std::cout << arr.test_bit(4) << std::endl;
    std::cout << arr << std::endl;

    std::cout << (arr & arr) << std::endl;

    BitArray<5> arr2 = arr | BitArray<5>{1};
    
    std::cout << (!arr2) << std::endl;

    return 0;
}