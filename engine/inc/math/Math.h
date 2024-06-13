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
         * @brief Returns the minimum of two numbers. Base for the variadic method.
         *
         * @tparam T - type of the numbers.
         * @param a - first number.
         * @return a - the first number.
         */
        template<typename T>
        static T min(T a) {
            return a;
        }

        /**
         * @brief Returns the minimum of two numbers.
         *
         * @tparam T - type of the numbers.
         * @param a - first number.
         * @param Args - the following numbers.
         * @return The minimum of the given numbers.
         */
        template<typename T, typename... Args>
        static T min(T first, Args... args) {
            T min_of_rest = min(args...);
            return (first < min_of_rest) ? first : min_of_rest;
        }

        /**
         * @brief Returns the maximum of two numbers. Base for the variadic method.
         *
         * @tparam T - type of the numbers.
         * @param a - first number.
         * @return a - the first number.
         */
        template<typename T>
        static T max(T a) {
            return a;
        }

        /**
         * @brief Returns the maximum of two numbers.
         *
         * @tparam T - type of the numbers.
         * @param a - first number.
         * @param Args - the following numbers.
         * @return The maximum of the given numbers.
         */
        template<typename T, typename... Args>
        static T max(T first, Args... args) {
            T min_of_rest = min(args...);
            return (first > min_of_rest) ? first : min_of_rest;
        }

        /**
         * @brief Compares two floating point numbers with a given margin of error.
         *
         * @param p_a The first number to compare.
         * @param p_b The second number to compare.
         * @param p_epsilon The margin of error.
         */
        static bool equal(float p_a, float p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        /**
         * @brief Compares two vectors to determin wheter they are equal.
         *
         * @param p_a The first vector to compare.
         * @param p_b The second vector to compare.
         * @param p_epsilon The margin of error.
         *
         * @return True if the vectors are equal, false otherwise.
         */
        static bool vectorEqual(const Vector3 &p_a, const Vector3 &p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        /**
         * @brief Determines whether a vector is a zero vector equal to {0.0, 0.0, 0.0}.
         *
         * @param p_a The first vector to compare.
         * @param p_epsilon The margin of error.
         *
         * @return True if the vector is a zero vector, false otherwise.
         */
        static bool isVectorZero(const Vector3 &p_a, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        /**
         * @brief Gets the absolute value of a number.
         *
         * @param p_a The number to get the absolute value of.
         *
         * @return The absolute value of the number.
         */
        static float abs(float p_a);

        /**
         * @brief Returns the power of a number.
         *
         * @param p_a The number to get the power of.
         * @param p_b The power to raise the number to.
         *
         * @return The power of the number.
         */
        static uint32_t power(uint32_t p_a, uint32_t p_b);

        /**
         * @brief Returns the power of a number.
         *
         * @param p_a The number to get the power of.
         * @param p_b The power to raise the number to.
         *
         * @return The power of the number.
         */
        static double power(double p_a, double p_b);

        /**
         * @brief Returns the power of 2 of a number.
         *
         * @param p_a The number to get the power of 2 of.
         *
         * @return The power of 2 of the number.
         */
        static double power2(double p_a);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         *
         * @return The square root of the number.
         */
        static double sqrt(double p_a);

        /**
         * @brief Returns the radians of a number.
         *
         * @param p_degrees The number to get the radians of.
         *
         * @return The radians of the number.
         */
        static double degreesToRadians(int p_degrees);

        /**
         * @brief Returns the degrees of a number.
         *
         * @param p_radians The number to get the degrees of.
         *
         * @return The degrees of the number.
         */
        static int radiansToDegrees(double p_radians);

        /**
         * @brief Returns the tangens of a number.
         *
         * @param p_t The number to get the tangens of.
         *
         * @return The tangens of the number.
         */
        static double tan(double p_t);

        /**
         * @brief Returns the sin of a number.
         *
         * @param p_t The number to get the sin of.
         *
         * @return The sin of the number.
         */
        static double sin(double p_t);

        /**
         * @brief Returns the cos of a number.
         *
         * @param p_t The number to get the cos of.
         *
         * @return The cos of the number.
         */
        static double cos(double p_t);

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

        static Vector3 v3IntersectPlane(const Vector3 &p_plane_p, const Vector3 &p_plane_n,
                                        const Vector3 &p_line_start, Vector3 &p_line_end);

        /**
         * @brief Returns the intersection of an edge and a line.
         *
         * @param p_edge_start The start of the edge. Against this edge the line will be clipped.
         * @param p_edge_end The end of the edge. Against this edge the line will be clipped.
         * @param p_line_start The start of the line. This line will be clipped.
         * @param p_line_end The end of the line. This line will be clipped.
         * @param p_default_value The default value to return if the intersection is not possible.
         *
         * @return The intersection of the edge and the line.
         */
        static Vector3 v3IntersectEdge(const Vector3 &p_edge_start, const Vector3 &p_edge_end,
                                       const Vector3 &p_line_start, const Vector3 &p_line_end,
                                       const Vector3 &p_default_value = Vector3Zero);

        static bool lineIntersect(const Vector3 &p_edge_start, const Vector3 &p_edge_end,
                                  const Vector3 &p_line_start, const Vector3 &p_line_end,
                                  Vector3 &intersection);

        static uint8_t triangle3DClipAgainstPlane(const Vector3 &p_plane_p, const Vector3 &p_plane_n,
                                                  Triangle &p_in_tri, Triangle &p_out_tri1, Triangle &p_out_tri2);

        static uint8_t triangle2DClipAgainstEdge(Vector3 &p_edge_p1, Vector3 &p_edge_p2,
                                                 Triangle &p_in_tri,
                                                 Triangle &p_out_tri1, Triangle &p_out_tri2, Triangle &p_out_tri3);

        static uint8_t triangle2DClipAgainstTriangle(Triangle &p_clip_tri, Triangle &p_in_tri,
                                                     Triangle &p_out_tri1, Triangle &p_out_tri2, Triangle &p_out_tri3,
                                                     Triangle &p_out_tri4, Triangle &p_out_tri5, Triangle &p_out_tri6,
                                                     Triangle &p_out_tri7, Triangle &p_out_tri8, Triangle &p_out_tri9);

    public:
        static constexpr double PI{M_PI}; //!< The value of PI
        static constexpr double INF{1.7976931348623157E+308}; //!< Maximum value that double can hold.

    private:
        static constexpr double DOUBLE_DEFAULT_DELTA{
                0.000000000000000000001}; //!< Default accepted margin for double values.

    };
}

#endif /* CRUSTENGINE_MATH_H */
