#ifndef _MATH_HPP_
#define _MATH_HPP_

#include <math.h> /* cos, sin, sqrt */

/**
 * @brief Static class that wrapps all math's algorithm used in the engine.
 */
class Math
{
public:
    /**
     * @brief Method that calculates absolute of a given value.
     *
     * @param value Value that will be converted to absolute.
     * @return double Abosulute value.
     */
    static double Abs(double value);
    static float Abs(float value);

    /**
     * @brief Method that calculates square root of a given value.
     *
     * @param radicand Value that square root will be calculated.
     * @return double Square root of #radicand.
     */
    static double SquareRoot(double radicand);
    
    /**
     * @brief Method that calculates 1/sqrt(radicand). This is highly useful during projection.
     *
     * @param radicand Value that square root will be calculated.
     * @return double Inversed of a square root of a #radicand.
     */
    static double InverseSquareRoot(double radicand);

    /**
     * @brief Method that calculates cos for t value.
     *
     * @param t x variable for cos(x). In radians.
     * @return double Value of a cos for #t.
     */
    static double Cos(double t);
    /**
     * @brief Method that calculates sin for t value.
     *
     * @param t x variable for sin(x). In radians.
     * @return double Value of a sin for #t.
     */
    static double Sin(double t);
    /**
     * @brief Method that calculates tan for t value.
     *
     * @param t x variable for tan(x). In radians.
     * @return double Value of a tan for #t.
     */
    static double Tan(double t);

    /**
     * @brief Converts #radians to degrees.
     *
     * @param radians Value in radians that will be converted.
     * @return uint16_t Converted value in degrees.
     */
    static uint16_t RadiansToDegrees(double radians);

    /**
     * @brief Converts #angleInDegrees to radians.
     *
     * @param degrees Value in degrees that will be converted
     * @return double Converted value in radians.
     */
    static double DegreesToRadians(uint16_t degrees);

    /**
     * @brief Checks if given values are equal within accepted margin #delta.
     *
     * @param val1 First compared value.
     * @param val2 Second compared value.
     * @param delta Accepted margin that will be tolerated even if the value are not exact. Default is #DOUBLE_DEFAULT_DELTA.
     * @return true Values are equal within accepted margin.
     * @return false Values are not equal within accepted margin.
     */
    static bool DoubleEquals(double val1, double val2, double delta = DOUBLE_DEFAULT_DELTA);

private:
    static constexpr double PI{M_PI}; //!< The value of PI
    static constexpr double INF { 1.7976931348623157E+308 }; //!< Maximum value that double can hold. 

    static constexpr double DOUBLE_DEFAULT_DELTA{0.0000001}; //!< Default accepted margin for double values.

};

inline double Math::Abs(double value)
{
    return (value >= 0 ? value : -value);
}

inline float Math::Abs(float value)
{
    return (value >= 0 ? value : -value);
}

inline double Math::SquareRoot(double radicand)
{
    return sqrt(radicand);
}

inline double Math::InverseSquareRoot(double radicand)
{
    double sq = sqrt(radicand);
    if(DoubleEquals(sq, 0)) return Math::INF;
    return (1.0 / sq);
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