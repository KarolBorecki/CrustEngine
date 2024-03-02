#include "math/Math.h"

namespace Crust {
    bool Math::equal(float p_a, float p_b, float p_epsilon) {
        return Math::abs(p_a - p_b) < p_epsilon;
    }

    float Math::abs(float p_a) {
        return p_a < 0 ? -p_a : p_a;
    }

    float Math::degreesToRadians(int p_degrees) {
        return p_degrees * (Math::PI / 180.0);
    }

    int Math::radiansToDegrees(float p_radians) {
        return p_radians * (180.0 / Math::PI);
    }

    float Math::tan(float p_t) {
        return std::tan(p_t);
    }

    float Math::sin(float p_t) {
        return std::sin(p_t);
    }

    float Math::cos(float p_t) {
        return std::cos(p_t);
    }
}