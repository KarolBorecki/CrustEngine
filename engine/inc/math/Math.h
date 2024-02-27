#ifndef CRUSTENGINE_MATH_H
#define CRUSTENGINE_MATH_H

#include <cmath>

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
         * @brief Compares two double numbers with a given margin of error.
         *
         * @param p_a The first number to compare.
         * @param p_b The second number to compare.
         * @param p_epsilon The margin of error.
         */
        static bool equal(double p_a, double p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        /**
         * @brief Returns the absolute value of a number.
         *
         * @param p_a The number to get the absolute value of.
         */
        static float abs(float p_a);

        /**
         * @brief Returns the absolute value of a number.
         *
         * @param p_a The number to get the absolute value of.
         */
        static double abs(double p_a);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         */
        static double degreesToRadians(int p_degrees);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         */
        static double radiansToDegrees(double p_radians);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         */
        static double tan(double p_t);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         */
        static double sin(double p_t);

        /**
         * @brief Returns the square root of a number.
         *
         * @param p_a The number to get the square root of.
         */
        static double cos(double p_t);

    public:
        static constexpr double PI { M_PI }; //!< The value of PI
        static constexpr double INF { 1.7976931348623157E+308 }; //!< Maximum value that double can hold.

    private:
        static constexpr double DOUBLE_DEFAULT_DELTA { 0.00000000000000001 }; //!< Default accepted margin for double values.

    };
}

#endif /* CRUSTENGINE_MATH_H */