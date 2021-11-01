#ifndef __MATHLIB_VECTOR_H__
#define __MATHLIB_VECTOR_H__

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <numeric>
#include <ostream>
#include <stdexcept>
#include <vector>

template <unsigned N, typename T>
class Vector {
public:
    using type = T;
    constexpr static unsigned size() {
        return N;
    }

    // Constructors
    Vector() {
        std::fill(m_data, m_data + N, T(0.));
    }

    Vector(T t) {
        std::fill(m_data, m_data + N, t);
    }

    Vector(std::vector<T> data) {
        assert(data.size() == N);
        std::copy(data.begin(), data.end(), m_data);
    }

    Vector(const Vector &other) {
        std::copy(other.m_data, other.m_data + N, m_data);
    }

    Vector(T data[N]) {
        std::copy(data, data + N, m_data);
    }

    Vector &operator=(Vector &other) {
        std::copy(other.m_data, other.m_data + N, m_data);
        return *this;
    }

    ~Vector() = default;

    // Norm
    T norm() const {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        T sum(0.0);
        for (unsigned i = 0; i < N; ++i)
            sum += m_data[i] * m_data[i];
        return std::sqrt(sum);
    }

    T squaredNorm() const {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        T sum(0.0);
        for (unsigned i = 0; i < N; ++i)
            sum += m_data[i] * m_data[i];
        return sum;
    }

    void normalize() {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        T inv_norm = T(1.0) / norm();
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = inv_norm * m_data[i];
    }

    Vector normalized() const {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        Vector ret;
        T inv_norm = T(1.0) / norm();
        for (unsigned i = 0; i < N; ++i)
            ret[i] = m_data[i] * inv_norm;
        return ret;
    }

    // Access
    const T operator[](unsigned idx) const {
        return m_data[idx];
    }

    T &operator[](unsigned idx) {
        return m_data[idx];
    }

    const T operator()(unsigned idx) const {
        return m_data[idx];
    }

    T &operator()(unsigned idx) {
        return m_data[idx];
    }

    const T at(unsigned idx) const {
        assert_idx(idx);
        return m_data[idx];
    }

    T &at(unsigned idx) {
        assert_idx(idx);
        return m_data[idx];
    }

    T x() const {
        static_assert(N >= 1 && "x() not supported for vectors with size 0");
        return m_data[0];
    }

    T &x() {
        static_assert(N >= 1 && "x() not supported for vectors with size 0");
        return m_data[0];
    }

    T y() const {
        static_assert(N >= 2 && "y() not supported for vectors with size 1 or less");
        return m_data[1];
    }

    T &y() {
        static_assert(N >= 2 && "y() not supported for vectors with size 1 or less");
        return m_data[1];
    }

    T z() const {
        static_assert(N >= 3 && "z() not supported for vectors with size 2 or less");
        return m_data[2];
    }

    T &z() {
        static_assert(N >= 3 && "z() not supported for vectors with size 2 or less");
        return m_data[2];
    }

    // Math ops
    T sum() const {
        return std::accumulate(m_data, m_data + N, T(0.));
    }

    T dot(const Vector &other) const {
        T ret(0.);
        for (unsigned i = 0; i < N; ++i)
            ret += m_data[i] * other.m_data[i];
        return ret;
    }

    T min() const {
        return *std::min_element(m_data, m_data + N);
    }

    T max() const {
        return *std::max_element(m_data, m_data + N);
    }

    T &minCoeff() {
        return *std::min_element(m_data, m_data + N);
    }

    T &maxCoeff() {
        return *std::max_element(m_data, m_data + N);
    }

    // Operators
    Vector &operator+=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] += other.m_data[i];
        return *this;
    }

    Vector &operator-=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] -= other.m_data[i];
        return *this;
    }

    Vector &operator*=(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] *= other.m_data[i];
        return *this;
    }

    Vector &operator/=(const Vector &other) {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        for (unsigned i = 0; i < N; ++i)
            m_data[i] /= other.m_data[i];
        return *this;
    }

    Vector &operator*(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] *= value;
        return *this;
    }

    Vector &operator+(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] += value;
        return *this;
    }

    Vector &operator-(const T &value) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] -= value;
        return *this;
    }

    Vector &operator/(const T &value) {
        static_assert(std::is_floating_point<T>::value, "base type is not floating point.");
        for (unsigned i = 0; i < N; ++i)
            m_data[i] /= value;
        return *this;
    }

    // Head / tail / segment
    template <unsigned n>
    Vector<n, T> head() const {
        static_assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i];
        }
        return ret;
    }
    template <unsigned n>
    Vector<n, T> tail() const {
        static_assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i + N - n];
        }
        return ret;
    }
    template <unsigned s, unsigned n>
    Vector<n, T> segment() const {
        static_assert(n <= N && n + s <= N && "n > N or + s > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i + s];
        }
        return ret;
    }

    // Comma Initializer list
    // https://stackoverflow.com/questions/29523119/how-could-comma-separated-initialization-such-as-in-eigen-be-possibly-implemente
    struct CommaLoader {
        Vector &m_v;
        unsigned m_i;
        CommaLoader(Vector &v, unsigned i) : m_v(v), m_i(i) {}
        CommaLoader operator,(T value) {
            m_v.assert_idx(m_i);
            m_v.at(m_i) = value;
            return CommaLoader(m_v, m_i + 1);
        }
    };
    CommaLoader operator<<(T value) {
        assert_idx(0);
        m_data[0] = value;
        return CommaLoader(*this, 1);
    }

    template <typename S>
    Vector<N, S> cast() const {
        Vector<N, S> ret;
        for (unsigned i = 0; i < N; ++i)
            ret[i] = static_cast<S>(m_data[i]);
        return ret;
    }

    // Comparison
    friend bool operator==(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
        for (unsigned i = 0; i < N; ++i)
            if (fabs(lhs[i] - rhs[i]) > std::numeric_limits<double>::epsilon())
                return false;
        return true;
    }

    friend bool operator!=(const Vector<N, T> &lhs, const Vector<N, T> &rhs) {
        return !(lhs == rhs);
    }

    // Write & Read
    friend std::ostream &operator<<(std::ostream &os, const Vector<N, T> &v) {
        for (unsigned i = 0; i < N; ++i) {
            os << v[i];
            if (i < N - 1)
                os << " ";
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &os, Vector<N, T> &v) {
        for (unsigned i = 0; i < N; ++i)
            os >> v[i];
        return os;
    }

    // Custom functions for specializations
    Vector cross(const Vector &other) {
        static_assert(N == 3 && "cross is only defined for Vectors with size 3.");
        return Vector();
    }

private:
    void assert_idx(unsigned idx) const {
        if (idx >= N)
            throw std::runtime_error("idx >= N");
    }

private:
    T m_data[N];
};

#endif /* __MATHLIB_VECTOR_H__ */