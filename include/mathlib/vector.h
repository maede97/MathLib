#ifndef __MATHLIB_VECTOR_H__
#define __MATHLIB_VECTOR_H__

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief %Vector class.
 * @tparam N The size of the vectors.
 * @tparam T The underlying data type of the vectors.
 */
template <unsigned N, typename T>
class Vector {
public:
    using type = T;  ///< The underlying data type.

    /**
     * @brief The underlying size of the vector.
     * @return The size.
     */
    constexpr static unsigned size() {
        return N;
    }

    /**
     * @brief Construct a zero vector.
     */
    Vector() {
        std::fill(m_data, m_data + N, T(0.));
    }

    /**
     * @brief Construct a vector from a single value.
     * @param t The single value
     */
    Vector(T t) {
        std::fill(m_data, m_data + N, t);
    }

    /**
     * @brief Construct a vector from given data.
     * @param data The data to use.
     */
    Vector(std::vector<T> data) {
        assert(data.size() == N);
        std::copy(data.begin(), data.end(), m_data);
    }

    /**
     * @brief Construct a vector from another vector.
     * @param other The other vector.
     */
    Vector(const Vector &other) {
        std::copy(other.m_data, other.m_data + N, m_data);
    }

    /**
     * @brief Construct a vector from given data.
     * @param data The data to use.
     */
    Vector(T data[N]) {
        std::copy(data, data + N, m_data);
    }

    /**
     * @brief Copy a vector into this.
     * @param other The other vector
     * @return A reference to this.
     */
    Vector &operator=(Vector &other) {
        std::copy(other.m_data, other.m_data + N, m_data);
        return *this;
    }

    /**
     * @brief Default deconstructor.
     */
    ~Vector() = default;

    /**
     * @brief The euclidian norm.
     * @return The norm \f$ || v ||_2 \f$
     * @attention Only for floating point types.
     */
    T norm() const {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        T sum(0.0);
        for (unsigned i = 0; i < N; ++i)
            sum += m_data[i] * m_data[i];
        return std::sqrt(sum);
    }

    /**
     * @brief The squared euclidian norm.
     * @return The norm \f$ || v ||_2^2 \f$
     */
    T squaredNorm() const {
        T sum(0.0);
        for (unsigned i = 0; i < N; ++i)
            sum += m_data[i] * m_data[i];
        return sum;
    }

    /**
     * @brief Normalize this.
     * @attention Only for floating point types.
     */
    void normalize() {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        T inv_norm = T(1.0) / norm();
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = inv_norm * m_data[i];
    }

    /**
     * @brief Return a normalized copy of this.
     * @return The normalized copy.
     * @attention Only for floating point types.
     */
    Vector normalized() const {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        Vector ret;
        T inv_norm = T(1.0) / norm();
        for (unsigned i = 0; i < N; ++i)
            ret[i] = m_data[i] * inv_norm;
        return ret;
    }

    /**
     * @brief Read access to idx.
     * @param idx The index to read (0-indexed).
     * @return The value at idx.
     * @attention Does not perform index boundary checks. Use Vector::at instead.
     */
    const T operator[](unsigned idx) const {
        return m_data[idx];
    }

    /**
     * @brief Write access to idx.
     * @param idx The index to write (0-indexed).
     * @return The value at idx.
     * @attention Does not perform index boundary checks. Use Vector::at instead.
     */
    T &operator[](unsigned idx) {
        return m_data[idx];
    }

    /**
     * @brief Read access to idx.
     * @param idx The index to read (0-indexed).
     * @return The value at idx.
     * @attention Does not perform index boundary checks. Use Vector::at instead.
     */
    const T operator()(unsigned idx) const {
        return m_data[idx];
    }

    /**
     * @brief Write access to idx.
     * @param idx The index to write (0-indexed).
     * @return The value at idx.
     * @attention Does not perform index boundary checks. Use Vector::at instead.
     */
    T &operator()(unsigned idx) {
        return m_data[idx];
    }

    /**
     * @brief Read access to idx.
     * @param idx The index to read (0-indexed).
     * @return The value at idx.
     * @attention Does perform index boundary checks.
     */
    const T at(unsigned idx) const {
        assert_idx(idx);
        return m_data[idx];
    }

    /**
     * @brief Write access to idx.
     * @param idx The index to write (0-indexed).
     * @return The value at idx.
     * @attention Does perform index boundary checks.
     */
    T &at(unsigned idx) {
        assert_idx(idx);
        return m_data[idx];
    }

    /**
     * @brief Helper to read the first element.
     * @return The first element.
     * @attention Only for size >= 1.
     */
    const T x() const {
        static_assert(N >= 1 && "x() not supported for vectors with size 0");
        return m_data[0];
    }

    /**
     * @brief Helper to write the first element.
     * @return The first element.
     * @attention Only for size >= 1.
     */
    T &x() {
        static_assert(N >= 1 && "x() not supported for vectors with size 0");
        return m_data[0];
    }

    /**
     * @brief Helper to read the second element.
     * @return The second element.
     * @attention Only for size >= 2.
     */
    const T y() const {
        static_assert(N >= 2 && "y() not supported for vectors with size 1 or less");
        return m_data[1];
    }

    /**
     * @brief Helper to write the second element.
     * @return The second element.
     * @attention Only for size >= 2.
     */
    T &y() {
        static_assert(N >= 2 && "y() not supported for vectors with size 1 or less");
        return m_data[1];
    }

    /**
     * @brief Helper to read the third element.
     * @return The third element.
     * @attention Only for size >= 3.
     */
    const T z() const {
        static_assert(N >= 3 && "z() not supported for vectors with size 2 or less");
        return m_data[2];
    }

    /**
     * @brief Helper to write the third element.
     * @return The third element.
     * @attention Only for size >= 3.
     */
    T &z() {
        static_assert(N >= 3 && "z() not supported for vectors with size 2 or less");
        return m_data[2];
    }

    /**
     * @brief Get the sum of this.
     * @return The sum of all values.
     */
    T sum() const {
        return std::accumulate(m_data, m_data + N, T(0.));
    }

    /**
     * @brief Compute the dot-product with other.
     * @param other The other vector.
     * @return The dot-product with other.
     */
    T dot(const Vector &other) const {
        T ret(0.);
        for (unsigned i = 0; i < N; ++i)
            ret += m_data[i] * other.m_data[i];
        return ret;
    }

    /**
     * @brief Compute the cross product.
     * @param other The other vector.
     * @return The cross product of this and other.
     * @attention Only for size 3!
     */
    Vector cross(const Vector &other) {
        static_assert(N == 3 && "cross is only defined for Vectors with size 3.");
        Vector ret;
        ret.x() = m_data[1] * other.z() - m_data[2] * other.y();
        ret.y() = m_data[2] * other.x() - m_data[0] * other.z();
        ret.z() = m_data[0] * other.y() - m_data[1] * other.x();
        return ret;
    }

    /**
     * @brief Compute the minimum value of this.
     * @return The minimum value of this.
     */
    const T min() const {
        return *std::min_element(m_data, m_data + N);
    }

    /**
     * @brief Compute the maximum value of this.
     * @return The maximum value of this.
     */
    const T max() const {
        return *std::max_element(m_data, m_data + N);
    }

    /**
     * @brief Get a reference to the minimum value of this.
     * @return The reference to the minimum value of this.
     */
    T &minCoeff() {
        return *std::min_element(m_data, m_data + N);
    }

    /**
     * @brief Get a reference to the maximum value of this.
     * @return The reference to the maximum value of this.
     */
    T &maxCoeff() {
        return *std::max_element(m_data, m_data + N);
    }

    /**
     * @brief Add another vector to this.
     * @param other The other vector.
     * @return A reference to this vector, with this + other.
     */
    Vector &operator+=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] += other.m_data[i];
        return *this;
    }

    /**
     * @brief Subtract another vector from this.
     * @param other The other vector.
     * @return A reference to this vector, with this - other.
     */
    Vector &operator-=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] -= other.m_data[i];
        return *this;
    }

    /**
     * @brief Multiply another vector to this (element-wise).
     * @param other The other vector.
     * @return A reference to this vector, with this * other.
     */
    Vector &operator*=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] *= other.m_data[i];
        return *this;
    }

    /**
     * @brief Divide this by another vector (element-wise).
     * @param other The other vector.
     * @return A reference to this vector, with this / other.
     * @attention Only for floating point types.
     */
    Vector &operator/=(const Vector &other) {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        for (unsigned i = 0; i < N; ++i)
            m_data[i] /= other.m_data[i];
        return *this;
    }

    /**
     * @brief Multiply this vector by a scalar
     * @param value The scalar
     * @return A reference to this vector, with this * value.
     */
    Vector &operator*(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] *= value;
        return *this;
    }

    /**
     * @brief Add a scalar to this vector
     * @param value The scalar
     * @return A reference to this vector, with this + value.
     */
    Vector &operator+(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] += value;
        return *this;
    }

    /**
     * @brief Subtract a scalar from this vector
     * @param value The scalar
     * @return A reference to this vector, with this - value.
     */
    Vector &operator-(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] -= value;
        return *this;
    }

    /**
     * @brief Divide this vector by a scalar
     * @param value The scalar
     * @return A reference to this vector, with this / value.
     * @attention Only for floating point types.
     */
    Vector &operator/(const T &value) {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        for (unsigned i = 0; i < N; ++i)
            m_data[i] /= value;
        return *this;
    }

    /**
     * @brief Get a variable length head.
     * @tparam n The number of elements.
     * @return A copy of this with given length, taken from the head.
     */
    template <unsigned n>
    Vector<n, T> head() const {
        static_assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i];
        }
        return ret;
    }

    /**
     * @brief Get a variable length tail.
     * @tparam n The number of elements.
     * @return A copy of this with given length, taken from the end.
     */
    template <unsigned n>
    Vector<n, T> tail() const {
        static_assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i + N - n];
        }
        return ret;
    }

    /**
     * @brief Get a variable length segment.
     * @tparam s The start element idx.
     * @tparam n The number of elements.
     * @return A copy of this with given length, starting at s.
     */
    template <unsigned s, unsigned n>
    Vector<n, T> segment() const {
        static_assert(n <= N && n + s <= N && "n > N or + s > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i + s];
        }
        return ret;
    }

    /**
     * @brief Helper for comma initialization.
     *
     * https://stackoverflow.com/questions/29523119/how-could-comma-separated-initialization-such-as-in-eigen-be-possibly-implemente
     */
    struct CommaLoader {
        Vector &m_v;   ///< A reference to the vector to be created.
        unsigned m_i;  ///< The current index to write

        /**
         * @brief Create a comma initializer with a reference and an index.
         * @param v The reference to the vector.
         * @param i The index to write.
         */
        CommaLoader(Vector &v, unsigned i) : m_v(v), m_i(i) {}

        /**
         * @brief Step forward one
         * 
         * Writes a value and steps the comma initializer one forward.
         * @param value The value to write at the current index.
         * @return A new comma loader with this and a one higher index.
         */
        CommaLoader operator,(T value) {
            m_v.assert_idx(m_i);
            m_v.at(m_i) = value;
            return CommaLoader(m_v, m_i + 1);
        }
    };

    /**
     * @brief Start the comma initialization.
     * @param value The initial value
     * @return The comma loader object.
     */
    CommaLoader operator<<(T value) {
        assert_idx(0);
        m_data[0] = value;
        return CommaLoader(*this, 1);
    }

    /**
     * @brief Cast this datatype
     * @tparam S the new datatype
     * @return A casted version of this to type S.
     */
    template <typename S>
    Vector<N, S> cast() const {
        Vector<N, S> ret;
        for (unsigned i = 0; i < N; ++i)
            ret[i] = static_cast<S>(m_data[i]);
        return ret;
    }

    /**
     * @brief Check for equality.
     * @param lhs The first vector.
     * @param rhs The second vector.
     * @return True if the vectors are equal (floating-point comparison).
     */
    friend bool operator==(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
        for (unsigned i = 0; i < N; ++i)
            if (fabs(lhs[i] - rhs[i]) > std::numeric_limits<double>::epsilon())
                return false;
        return true;
    }

    /**
     * @brief Check for inequality.
     * @param lhs The first vector.
     * @param rhs The second vector.
     * @return True if the vectors are not equal (floating-point comparison).
     */
    friend bool operator!=(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
        return !(lhs == rhs);
    }

    /**
     * @brief Write a vector to a stream.
     * @param os The stream.
     * @param v The vector.
     * @return The stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
        for (unsigned i = 0; i < N; ++i) {
            os << v[i];
            if (i < N - 1)
                os << " ";
        }
        return os;
    }

    /**
     * @brief Read a vector from a stream.
     * @param os The stream.
     * @param v The vector.
     * @return The stream.
     */
    friend std::istream &operator>>(std::istream &os, Vector<N, T> &v) {
        for (unsigned i = 0; i < N; ++i)
            os >> v[i];
        return os;
    }

    /**
     * @brief Return a string reprensetation of this.
     * @return A string containing the values.
     */
    std::string to_string() const {
        std::string ret;
        for (unsigned i = 0; i < N; ++i) {
            ret += std::to_string(m_data[i]);
            if (i < N - 1)
                ret += " ";
        }
        return ret;
    }

private:
    /**
     * @brief Assert a given index is in range.
     * @param idx The index.
     * @throws std::runtime_error If index is out of range.
     */
    void assert_idx(unsigned idx) const {
        if (idx >= N)
            throw std::runtime_error("idx >= N");
    }

private:
    T m_data[N];  ///< The underlying data.
};

#endif /* __MATHLIB_VECTOR_H__ */