#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

template <unsigned N, typename T>
class Vector {
public:
    // Constructors
    Vector() {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = 0.;
    }

    Vector(T t) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = t;
    }

    Vector(std::vector<T> data) {
        assert(data.size() == N);

        for (unsigned i = 0; i < N; ++i)
            m_data[i] = data[i];
    }

    Vector(const Vector &other) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = other.m_data[i];
    }

    Vector(T data[N]) {
        for (unsigned i = 0; i < N; ++i)
            m_data[i] = data[i];
    }

    ~Vector() = default;

    // info about this
    unsigned size() const {
        return N;
    }

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
        T dat[N];
        T inv_norm = T(1.0) / norm();
        for (unsigned i = 0; i < N; ++i)
            dat[i] = m_data[i] * inv_norm;
        return Vector(dat);
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
        return std::min_element(m_data, m_data + N);
    }

    T &maxCoeff() {
        return std::max_element(m_data, m_data + N);
    }

    // Operators
    Vector &operator=(Vector &other) {
        std::copy(other.m_data, other.m_data + N, m_data);
        return *this;
    }

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

    bool operator==(const Vector &other) const {
        Vector diff = *this - other;
        return diff.squaredNorm() < 1e-10;
    }

    bool operator!=(const Vector &other) const {
        return !(*this == other);
    }

    // Head / tail / segment
    template <unsigned n>
    Vector<n, T> head() const {
        assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i];
        }
        return ret;
    }
    template <unsigned n>
    Vector<n, T> tail() const {
        assert(n <= N && "n > N");
        Vector<n, T> ret;
        for (unsigned i = 0; i < n; ++i) {
            ret[i] = m_data[i + N - n];
        }
        return ret;
    }
    template <unsigned s, unsigned n>
    Vector<n, T> segment() const {
        assert(n <= N && n + s <= N && "n > N or + s > N");
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
            m_v.at(m_i) = value;
            return CommaLoader(m_v, m_i + 1);
        }
    };
    CommaLoader operator<<(T value) {
        m_data[0] = value;
        return CommaLoader(*this, 1);
    }

private:
    void assert_idx(unsigned idx) const {
        // make use of the fact that a const char* literal evaluates to true
        if (idx < 0)
            throw std::runtime_error("idx < 0");
        if (idx >= N)
            throw std::runtime_error("idx >= N");
    }

private:
    T m_data[N];
};
