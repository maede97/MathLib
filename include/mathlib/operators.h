#pragma once

#include <mathlib/vector.h>

// More operators
template <unsigned N, typename T>
Vector<N, T> operator+(Vector<N, T> copy, const Vector<N, T> &b)
{
    copy += b;
    return copy;
}

template <unsigned N, typename T>
Vector<N, T> operator-(Vector<N, T> copy, const Vector<N, T> &b)
{
    copy -= b;
    return copy;
}

template <unsigned N, typename T>
Vector<N, T> operator*(Vector<N, T> copy, const Vector<N, T> &b)
{
    copy *= b;
    return copy;
}

template <unsigned N, typename T>
Vector<N, T> operator/(Vector<N, T> copy, const Vector<N, T> &b)
{
    static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
    copy /= b;
    return copy;
}