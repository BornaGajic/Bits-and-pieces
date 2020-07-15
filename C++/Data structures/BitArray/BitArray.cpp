#ifndef BITARRAY_CPP
#define BITARRAY_CPP

#include "BitArray.hpp"

template <size_t S>
BitArray<S>::BitArray ()
{
    data.fill(0);
}

template <size_t S>
BitArray<S>::BitArray (const bool& default_init)
{
    data.fill(default_init ? 1 : 0);
}

template <size_t S>
BitArray<S>::BitArray (const std::initializer_list<unsigned> init)
{
    data.fill(0);

    for (const auto pos : init)
        set_bit(pos);
}

template <size_t S>
BitArray<S>::BitArray (const BitArray<S>& BA)
{
    for (size_t i = 0; i < S; i++)
        data[i] = BA.data[i];
}

template <size_t S>
BitArray<S>::BitArray (BitArray<S>&& rv_BA)
{
    data.swap(rv_BA.data);
}

template <size_t S>
void BitArray<S>::set_bit (const unsigned i) 
{ 
    data[i] = 1;
}

template <size_t S>
void BitArray<S>::set_bit (const unsigned i, const bool b) 
{ 
    data[i] = static_cast<bool>(b); 
}

template <size_t S>
constexpr bool BitArray<S>::test_bit (const unsigned i) const 
{ 
    return data[i]; 
}

template <size_t S>
constexpr int BitArray<S>::size () const 
{ 
    return data.max_size();
}

template <size_t S>
void BitArray<S>::not_op ()
{
    std::for_each(data.begin(), data.end(), [&](bool i) { return !i;});
}
template <size_t S>
void BitArray<S>::and_op (const BitArray<S>& BA)
{
    for (int i = 0; i < S; i++)
        data[i] = data[i] & BA[i];
}
template <size_t S>
void BitArray<S>::or_op (const BitArray<S>& BA)
{
    for (int i = 0; i < S; i++)
        data[i] = data[i] | BA[i];
}

// toggle k-th bit
template <size_t S>
void BitArray<S>::xor_op (const BitArray<S>& BA)
{
    for (int i = 0; i < S; i++)
        data[i] = data[i] ^ BA[i];
}

template <size_t S>
constexpr auto BitArray<S>::begin () noexcept
{
    return data.begin();
}

template <size_t S>
constexpr auto BitArray<S>::end () noexcept
{
    return data.end(); 
}

template <size_t S>
bool& BitArray<S>::operator[] (const size_t idx) 
{ 
    return data[idx];
}

template <size_t S>
const bool& BitArray<S>::operator[] (const size_t idx) const 
{ 
    return data[idx];
}

template <size_t S>
BitArray<S> BitArray<S>::operator& (const BitArray<S>& val) const
{
    BitArray<S> result {};

    for (size_t i = 0; i < S; i++)
    {
        result[i] = (*this)[i] & val[i];
    }            

    return result;
}

template <size_t S>
BitArray<S> BitArray<S>::operator| (const BitArray<S> val) const
{
    BitArray<S> result {};

    for (size_t i = 0; i < S; i++)
    {
        result[i] = (*this)[i] | val[i];
    }            

    return result;
}

template <size_t S>
BitArray<S> BitArray<S>::operator! ()
{
    for (auto& bit : data)
        bit = !bit;
    
    return *this;
}

#endif