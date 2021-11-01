#ifndef __MATHLIB_OPERATORS_H__
#define __MATHLIB_OPERATORS_H__

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

#endif /* __MATHLIB_OPERATORS_H__ */