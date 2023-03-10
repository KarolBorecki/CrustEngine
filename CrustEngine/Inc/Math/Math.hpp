#ifndef _MATH_HPP_
#define _MATH_HPP_

class Math
{
public:
    static double Abs(double value);

    static bool DoubleEquals(double val1, double val2, double delta = DOUBLE_DEFAULT_DELTA);

private:
    static constexpr double DOUBLE_DEFAULT_DELTA { 0.0000001 };
};

inline double Math::Abs(double value)
{
    return (value >= 0 ? value : -value);
}

inline bool Math::DoubleEquals(double val1, double val2, double delta)
{
    return (Math::Abs(val1 - val2) <= delta);
}

#endif /* _MATH_HPP_ */