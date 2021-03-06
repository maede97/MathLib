#ifndef __MATHLIB_OPERATORS_H__
#define __MATHLIB_OPERATORS_H__

#include <mathlib/vector.h>

/**
 * @brief Add two vectors.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return a + b
 */
template <unsigned N, typename T>
Vector<N, T> operator+(Vector<N, T> a, const Vector<N, T> &b) {
    a += b;
    return a;
}

/**
 * @brief Subtract two vectors.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return a - b
 */
template <unsigned N, typename T>
Vector<N, T> operator-(Vector<N, T> a, const Vector<N, T> &b) {
    a -= b;
    return a;
}

/**
 * @brief Multiply two vectors.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return a * b
 */
template <unsigned N, typename T>
Vector<N, T> operator*(Vector<N, T> a, const Vector<N, T> &b) {
    a *= b;
    return a;
}

/**
 * @brief Divide two vectors.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return a / b
 * @attention Only supported for floating point vector types!
 */
template <unsigned N, typename T>
Vector<N, T> operator/(Vector<N, T> a, const Vector<N, T> &b) {
    static_assert(std::is_floating_point<T>::value && "base type is not floating point.");
    a /= b;
    return a;
}

/**
 * @brief Add a scalar to the vector
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param value The scalar
 * @param v The vector
 * @return A new vector with v + value, elementwise
 */
template <unsigned N, typename T>
Vector<N, T> operator+(const T &value, Vector<N, T> v) {
    v += value;
    return v;
}

/**
 * @brief Multiply a scalar with the vector
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @param value The scalar
 * @param v The vector
 * @return A new vector with v * value, elementwise
 */
template <unsigned N, typename T>
Vector<N, T> operator*(const T &value, Vector<N, T> v) {
    v *= value;
    return v;
}

/**
 * @brief Negate a vector.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 * @return A new vector which is negative elementwise.
 */
template <unsigned N, typename T>
Vector<N, T> operator-(Vector<N, T> v) {
    v *= T(-1.);
    return v;
}

#endif /* __MATHLIB_OPERATORS_H__ */