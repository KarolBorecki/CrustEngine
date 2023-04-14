#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <math.h> /* cos, sin, sqrt */

class Math
{
public:
    static double Abs(double value);

    static double SquareRoot(double radicand);
    static double InverseSquareRoot(double radicand);

    static double Cos(double t);
    static double Sin(double t);
    static double Tan(double t);

    /**
     * @brief Converts #radians to degrees.
     */

    static uint16_t RadiansToDegrees(double radians);

    /**
     * @brief Converts #angleInDegrees to radians.
     */

    static double DegreesToRadians(uint16_t degrees);

    static bool DoubleEquals(double val1, double val2, double delta = DOUBLE_DEFAULT_DELTA);

private:
    static constexpr double PI{M_PI};

    static constexpr double DOUBLE_DEFAULT_DELTA{0.0000001};
};

inline double Math::Abs(double value)
{
    return (value >= 0 ? value : -value);
}

inline double Math::SquareRoot(double radicand)
{
    return sqrt(radicand);
}

inline double Math::InverseSquareRoot(double radicand)
{
    return (1.0 / sqrt(radicand));
}

inline double Math::Cos(double t)
{
    return cos(t);
}

inline double Math::Sin(double t)
{
    return sin(t);
}

inline double Math::Tan(double t)
{
    return tan(t);
}

inline uint16_t Math::RadiansToDegrees(double radians)
{
    return (radians)*180.0 / PI;
}

inline double Math::DegreesToRadians(uint16_t degrees)
{
    return (degrees)*PI / 180.0;
}

inline bool Math::DoubleEquals(double val1, double val2, double delta)
{
    return (Math::Abs(val1 - val2) <= delta);
}

#endif /* _MATH_HPP_ */