#ifndef BITARRAY_HPP
#define BITARRAY_HPP

#include <array>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <iterator>

template <size_t S = 4>
class BitArray
{
    std::array<uint32_t, S> data;
    
    public:
        BitArray ()
        {
            data.fill(0);
        }
        BitArray (const bool default_init)
        {
            data.fill(default_init ? 1 : 0);
        }
        BitArray (std::initializer_list<unsigned> init)
        {
            if (init.size() > S)
                throw std::out_of_range("initializer_list is larger than specified BitArray length.");

            if (std::all_of(init.begin(), init.end(), [](int i) { return i == 0 || i == 1;}))
            {
                //std::fill_n(data.begin(), data.end(), init.begin(), init.end());
            }
        }
        BitArray (const BitArray<S>& BA)
        {
            data.fill_n(BA.begin(), BA.end());
        }
        BitArray (const BitArray<S>&& rv_BA)
        {
            data.swap(rv_BA);
        }

        void set_bit (const int i) const { data[i] = 1; }
        void set_bit (const int i, const bool b) const { data[i] = static_cast<unsigned>(b); }

        constexpr bool test_bit (const int i) const { return data[i]; }

        constexpr int size () const { return data.size(); }

        void not_o ()
        {
            std::for_each(data.begin(), data.end(), [&](bool i) { return !i;});
        }

        void and_o (const BitArray<S>& BA)
        {
            for (int i = 0; i < S; i++)
                data[i] = data[i] & BA[i];
        }

        void or_o (const BitArray<S>& BA)
        {
            for (int i = 0; i < S; i++)
                data[i] = data[i] | BA[i];
        }

        // toggle k-th bit
        void xor_o (const BitArray<S>& BA)
        {
            for (int i = 0; i < S; i++)
                data[i] = data[i] ^ BA[i];
        }
        
        BitArray operator& (const BitArray& lhs, const BitArray& rhs)
        {
            BitArray result {lhs.and_o(rhs)};
            
            return result;
        }


        unsigned& operator[] (size_t idx) { return data[idx]; }
        const unsigned& operator[] (size_t idx) const { return data[idx]; }
        


        constexpr auto begin () noexcept { return data.begin(); }
        constexpr auto end () noexcept { return data.end(); }

};


#endif