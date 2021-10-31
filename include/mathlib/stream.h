#pragma once

#include <mathlib/vector.h>

#include <ostream>

template <unsigned N, typename T>
std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
    for (unsigned i = 0; i < N; ++i)
        os << v[i] << " ";
    return os;
}
template <unsigned N, typename T>
std::ostream &operator>>(std::ostream &os, Vector<N, T> &v) {
    for (unsigned i = 0; i < N; ++i)
        os >> v[i];
    return os;
}