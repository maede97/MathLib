#ifndef __MATHLIB_QUATERNION_H__
#define __MATHLIB_QUATERNION_H__

#include <mathlib/operators.h>
#include <mathlib/vector.h>

#include <cmath>

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
class Quaternion : public Vector<4, T> {
public:
    using vec_t = Vector<3, T>;
    Quaternion(T x, T y, T z, T w) : Vector<4, T>({x, y, z, w}) {}

    Quaternion(const vec_t& axis, T angle) {
        w() = std::cos(angle / T(2.));
        setVec(std::sin(angle / T(2.)) * axis.normalized());
    }

    Quaternion() = default;

    ~Quaternion() = default;

    static Quaternion Identity() {
        return Quaternion(T(0.), T(0.), T(0.), T(1.));
    }

    Quaternion operator*(const Quaternion& rhs) const {
        Quaternion ret;

        ret.setVec(vec().cross(rhs.vec()) + w() * rhs.vec() + rhs.w() * vec());
        ret.w() = w() * rhs.w() - (vec().dot(rhs.vec()));

        return ret;
    }

    vec_t operator*(const vec_t& other) const {
        return other + T(2.) * vec().cross(w() * other + vec().cross(other)) / (*this).squaredNorm();
    }

    Quaternion inverse() const {
        Quaternion ret;

        T inv_norm_s = T(1.) / (*this).squaredNorm();

        ret.w() = w() * inv_norm_s;

        ret.setVec(-vec() * inv_norm_s);

        return ret;
    }

    T w() const {
        return (*this)[3];
    }

    T& w() {
        return (*this)[3];
    }

    vec_t vec() const {
        return vec_t((*this).x(), (*this).y(), (*this).z());
    }

    void setVec(const vec_t& vec) {
        (*this).x() = vec.x();
        (*this).y() = vec.y();
        (*this).z() = vec.z();
    }

    T angle() const {
        return T(2.) * std::atan2(vec().norm(), w());
    }

    vec_t axis() const {
        return vec().normalized();
    }
};
using Quaterniond = Quaternion<double>;
using Quaternionf = Quaternion<float>;

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
Vector<3, T> operator*(const Quaternion<T>& q, const Vector<3, T>& v) {}

template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
const Quaternion<T> operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs) {
    Quaternion<T> ret;

    ret.setVec(lhs.vec().cross(rhs.vec()) + lhs.w() * rhs.vec() + rhs.w() * lhs.vec());
    ret.w() = lhs.w() * rhs.w() - (lhs.vec().dot(rhs.vec()));

    return ret;
}

#endif /* __MATHLIB_QUATERNION_H__ */