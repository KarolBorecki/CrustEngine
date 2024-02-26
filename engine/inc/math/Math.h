#ifndef CRUSTENGINE_MATH_H
#define CRUSTENGINE_MATH_H

#include <cmath>

namespace Crust {
    class Math {
    public:
        static bool equal(float p_a, float p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);
        static bool equal(double p_a, double p_b, float p_epsilon = DOUBLE_DEFAULT_DELTA);

        static float abs(float p_a);
        static double abs(double p_a);

        static double degreesToRadians(int p_degrees);
        static double radiansToDegrees(double p_radians);

        static double tan(double p_t);
        static double sin(double p_t);
        static double cos(double p_t);

    public:
        static constexpr double PI { M_PI }; //!< The value of PI
        static constexpr double INF { 1.7976931348623157E+308 }; //!< Maximum value that double can hold.

    private:
        static constexpr double DOUBLE_DEFAULT_DELTA { 0.00000000000000001 }; //!< Default accepted margin for double values.

    };
}

#endif /* CRUSTENGINE_MATH_H */
