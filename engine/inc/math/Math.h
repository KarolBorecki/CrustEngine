#ifndef CRUSTENGINE_MATH_H
#define CRUSTENGINE_MATH_H

#include <cmath>
#include "Vector3.h"
#include "Vector4.h"
#include "math/geometry/Triangle.h"

namespace Crust {
    /**
     * @brief Math operations wrapper/implementation.
     */
    class Math {
    public:
        /**
         * @brief Compares two floating point numbers with a given margin of error.
         *
         * @param p_a The first number to compare.
         * @param p_b The second number to compare.
         * @param p_epsilon The margin of error.
         */
        static bool equal(float p_a, float p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        /**
         * @brief Gets the absolute value of a number.
         *
         * @param p_a The number to get the absolute value of.
         *
         * @return The absolute value of the number.
         */
        static float abs(float p_a);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         *
         * @return The square root of the number.
         */
        static float sqrt(float p_a);

        /**
         * @brief Returns the radians of a number.
         *
         * @param p_degrees The number to get the radians of.
         *
         * @return The radians of the number.
         */
        static float degreesToRadians(int p_degrees);

        /**
         * @brief Returns the degrees of a number.
         *
         * @param p_radians The number to get the degrees of.
         *
         * @return The degrees of the number.
         */
        static int radiansToDegrees(float p_radians);

        /**
         * @brief Returns the tangens of a number.
         *
         * @param p_t The number to get the tangens of.
         *
         * @return The tangens of the number.
         */
        static float tan(float p_t);

        /**
         * @brief Returns the sin of a number.
         *
         * @param p_t The number to get the sin of.
         *
         * @return The sin of the number.
         */
        static float sin(float p_t);

        /**
         * @brief Returns the cos of a number.
         *
         * @param p_t The number to get the cos of.
         *
         * @return The cos of the number.
         */
        static float cos(float p_t);

        /**
         * @brief Returns the square root of a plane defined by the verticies of the vectors.
         *
         * @param p_a First vertex of the plane.
         * @param p_b Second vertex of the plane.
         * @param p_c Third vertex of the plane.
         *
         * @return The normal of the plane.
         */
        static Vector3 normal(const Vector3 &p_a, const Vector3 &p_b, const Vector3 &p_c);

        static Vector3 v3IntersectPlane(const Vector3 &p_plane_p, const Vector3 &p_plane_n, const Vector3 &p_line_start,
                                        const Vector3 &p_line_end);

        static uint8_t triangleClipAgainstPlane(const Vector3 &p_plane_p, const Vector3 &p_plane_n, Triangle &p_in_tri,
                                                Triangle &p_out_tri1, Triangle &p_out_tri2);

    public:
        static constexpr double PI{M_PI}; //!< The value of PI
        static constexpr double INF{1.7976931348623157E+308}; //!< Maximum value that double can hold.

    private:
        static constexpr double DOUBLE_DEFAULT_DELTA{
                0.000000000000000000001}; //!< Default accepted margin for double values.

    };
}

#endif /* CRUSTENGINE_MATH_H */
