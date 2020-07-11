#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include <array>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <iostream>

template <size_t S>
class BitArray
{
    std::array<bool, S> data;
    
    public:
        BitArray ();
        BitArray (const bool& default_init);
        BitArray (const std::initializer_list<unsigned> init);
        BitArray (const BitArray<S>& BA);
        BitArray (BitArray<S>&& rv_BA);

        void set_bit (const unsigned i);
        void set_bit (const unsigned i, const bool b);

        constexpr bool test_bit (const unsigned i) const;

        constexpr int size () const;

        void not_op ();
        void and_op (const BitArray<S>& BA);
        void or_op (const BitArray<S>& BA);
        // toggle k-th bit
        void xor_op (const BitArray<S>& BA);
    
        constexpr auto begin () noexcept;
        constexpr auto end () noexcept;

        bool& operator[] (const size_t idx);
        const bool& operator[] (const size_t idx) const;

        BitArray<S> operator& (const BitArray<S>& val) const;
        BitArray<S> operator| (const BitArray<S> val) const;
        BitArray<S> operator! ();

        friend std::ostream& operator<< (std::ostream& os, const BitArray<S>& BA)
        {
            for (const bool bit : BA.data)
                os << bit << " ";
            os << "\n";

            return os;
        }
};

#include "BitArray.cpp"

#endif