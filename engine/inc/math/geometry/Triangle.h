#ifndef CRUSTENGINE_TRIANGLE_H
#define CRUSTENGINE_TRIANGLE_H

#include "Polygon.h"

namespace Crust {
    /**
     * @brief A triangle.
     */
    class Triangle : public Polygon<3> {
    public:
        /**
         * @brief Construct a new Triangle object.
         */
        Triangle() : Polygon<3>() {}
        ~Triangle() = default;
    };
}

#endif /* CRUSTENGINE_TRIANGLE_H */
