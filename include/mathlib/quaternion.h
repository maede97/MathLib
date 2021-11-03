#ifndef __MATHLIB_QUATERNION_H__
#define __MATHLIB_QUATERNION_H__

#include <mathlib/operators.h>

#include <cmath>

/**
 * @brief %Quaternion class
 * @tparam T The underlying data type.
 * @attention Data type must be floating point.
 * @attention Also supports all other functions of a Vector<4, T>, but use with caution!
 */
template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
class Quaternion : public Vector<4, T> {
public:
    using Vector3_t = Vector<3, T>;  ///< Helper for the vector part

    /**
     * @brief Create a quaternion from given values.
     * @param x The x compontent.
     * @param y The y compontent.
     * @param z The z compontent.
     * @param w The w compontent.
     */
    Quaternion(T x, T y, T z, T w) : Vector<4, T>({x, y, z, w}) {}

    /**
     * @brief Create a quaternion from a given axis and angle.
     * @param axis The axis, will be normalized.
     * @param angle The angle (in radians) of the rotation.
     */
    Quaternion(const Vector3_t& axis, T angle) {
        w() = std::cos(angle / T(2.));
        setVec(std::sin(angle / T(2.)) * axis.normalized());
    }

    /**
     * @brief Create a zero quaternion.
     */
    Quaternion() = default;

    /**
     * @brief Create a quaternion from another quaternion
     * @param other The other quaternion.
     */
    Quaternion(const Quaternion& other) : Vector<4, T>({other.x(), other.y(), other.z(), other.w()}) {}

    /**
     * @brief Default deconstructor
     */
    ~Quaternion() = default;

    /**
     * @brief Create an identity quaternion.
     * @return The identity quaternion.
     */
    static Quaternion Identity() {
        return Quaternion(T(0.), T(0.), T(0.), T(1.));
    }

    /**
     * @brief Initialize a quaternion from another.
     * @param other The other quaternion.
     * @return A reference to this.
     */
    Quaternion& operator=(const Quaternion& other) {
        w() = other.w();
        setVec(other.vec());
        return *this;
    }

    /**
     * @brief Compute multiplication of two quaternions.
     * 
     * This is the same as performing the two rotations.
     * @param other The other quaternion
     * @return The new rotation (quaternion).
     */
    Quaternion operator*(const Quaternion& other) const {
        Quaternion ret;

        if (vec().squaredNorm() < std::numeric_limits<T>::epsilon()) {
            return other;
        }
        if (other.vec().squaredNorm() < std::numeric_limits<T>::epsilon())
            return Quaternion(this->x(), this->y(), this->z(), this->w());

        ret.setVec(vec().cross(other.vec()) + w() * other.vec() + other.w() * vec());
        ret.w() = w() * other.w() - (vec().dot(other.vec()));

        return ret;
    }

    /**
     * @brief Rotate a vector with this.
     * @param other The vector to rotate
     * @return The rotated vector.
     */
    Vector3_t operator*(const Vector3_t& other) const {
        return other + T(2.) * vec().cross(w() * other + vec().cross(other)) / ((*this).squaredNorm() + std::numeric_limits<T>::epsilon());
    }

    /**
     * @brief Compute the inverse of this quaternion.
     * @return The inverse of this quaternion.
     */
    Quaternion inverse() const {
        Quaternion ret;

        T inv_norm_s = T(1.) / ((*this).squaredNorm() + std::numeric_limits<T>::epsilon());

        ret.w() = w() * inv_norm_s;

        ret.setVec(-vec() * inv_norm_s);

        return ret;
    }

    /**
     * @brief Read access to the w component.
     * @return The w component.
     */
    T w() const {
        return (*this)[3];
    }

    /**
     * @brief Write access to the w component.
     * @return The w component.
     */
    T& w() {
        return (*this)[3];
    }

    /**
     * @brief Read access to the vector component.
     * @return The vector component.
     */
    Vector3_t vec() const {
        return Vector3_t((*this).x(), (*this).y(), (*this).z());
    }

    /**
     * @brief Write access to the vector component.
     * @param vec The new vector component.
     */
    void setVec(const Vector3_t& vec) {
        (*this).x() = vec.x();
        (*this).y() = vec.y();
        (*this).z() = vec.z();
    }

    /**
     * @brief The current angle of the quaternion.
     * @return The angle of the rotation around axis().
     */
    T angle() const {
        return T(2.) * std::atan2(vec().norm(), w());
    }

    /**
     * @brief The current axis of the quaternion
     * @return The axis of the quaternion rotation.
     * @todo Check if the 0-vector fix is valid.
     */
    Vector3_t axis() const {
        if (vec().squaredNorm() < std::numeric_limits<T>::epsilon())
            return Vector3_t(1., 0., 0.);
        return vec().normalized();
    }
};

/**
 * @name Defines
 * @brief Underlying data type definitions.
 */
/** @{ */
using Quaterniond = Quaternion<double>;
using Quaternionf = Quaternion<float>;
/** @} */

#endif /* __MATHLIB_QUATERNION_H__ */