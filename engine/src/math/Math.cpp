#include "math/Math.h"

namespace Crust {
    bool Math::equal(float p_a, float p_b, float p_epsilon) {
        return Math::abs(p_a - p_b) < p_epsilon;
    }

    bool Math::equal(double p_a, double p_b, float p_epsilon) {
        return Math::(p_a - p_b) < p_epsilon;
    }

    float Math::abs(float p_a) {
        return p_a < 0 ? -p_a : p_a;
    }

    double Math::abs(double p_a) {
        return p_a < 0 ? -p_a : p_a;
    }

    double Math::degreesToRadians(int p_degrees) {
        return p_degrees * (Math::PI / 180.0);
    }

    double Math::radiansToDegrees(double p_radians) {
        return p_radians * (180.0 / Math::PI);
    }

    double Math::tan(double p_t) {
        return std::tan(p_t);
    }

    double Math::sin(double p_t) {
        return std::sin(p_t);
    }

    double Math::cos(double p_t) {
        return std::cos(p_t);
    }
}