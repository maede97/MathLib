#pragma once

#include <mathlib/vector.h>

// More operators
template <unsigned N, typename T>
Vector<N, T> operator+(Vector<N, T> a, const Vector<N, T> &b) {
    a += b;
    return a;
}

template <unsigned N, typename T>
Vector<N, T> operator-(Vector<N, T> a, const Vector<N, T> &b) {
    a -= b;
    return a;
}

template <unsigned N, typename T>
Vector<N, T> operator*(Vector<N, T> a, const Vector<N, T> &b) {
    a *= b;
    return a;
}

template <unsigned N, typename T>
Vector<N, T> operator/(Vector<N, T> a, const Vector<N, T> &b) {
    static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
    a /= b;
    return a;
}