#ifndef __MATHLIB_DEFINES_H__
#define __MATHLIB_DEFINES_H__

#include <mathlib/vector.h>

/**
 * @name Float
 * @brief Underlying data type is float.
 */
/** @{ */
using Vector1f = Vector<1, float>;
using Vector2f = Vector<2, float>;
using Vector3f = Vector<3, float>;
/* @} */

/**
 * @name Double
 * @brief Underlying data type is double.
 */
/** @{ */
using Vector1d = Vector<1, double>;
using Vector2d = Vector<2, double>;
using Vector3d = Vector<3, double>;
/* @} */

/**
 * @name Integer
 * @brief Underlying data type is integer.
 */
/** @{ */
using Vector1i = Vector<1, int>;
using Vector2i = Vector<2, int>;
using Vector3i = Vector<3, int>;
/* @} */

/**
 * @name Unsigned
 * @brief Underlying data type is unsigned int.
 */
/** @{ */
using Vector1u = Vector<1, unsigned>;
using Vector2u = Vector<2, unsigned>;
using Vector3u = Vector<3, unsigned>;
/* @} */

#endif /* __MATHLIB_DEFINES_H__ */