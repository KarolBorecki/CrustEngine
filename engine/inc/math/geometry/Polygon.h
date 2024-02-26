#ifndef CRUSTENGINE_POLYGON_H
#define CRUSTENGINE_POLYGON_H

#include <cstdint>

#include "math/Vector3.h"

namespace Crust {
    /**
     * @brief A polygon with a variable number of vertices.
     *
     * @tparam V The number of vertices in the polygon.
     */
    template<uint8_t V>
    class Polygon {
    public:
        /**
         * @brief Construct a new Polygon object.
         */
        Polygon();

        /**
         * @brief Destroy the Polygon object. Deallocate the vertices.
         */
        ~Polygon();

        /**
         * @brief Get the vertex at the specified index.
         *
         * @param p_index The index of the vertex to get.
         * @return The vertex at the specified index.
         */
        Vector3<>& getVertex(uint8_t p_index);

    private:
        Vector3<>* m_vertices[V]; /**< The vertices of the polygon. */
    };
}

#endif /* CRUSTENGINE_POLYGON_H */
