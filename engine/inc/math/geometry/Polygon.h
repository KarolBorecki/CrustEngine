#ifndef CRUSTENGINE_POLYGON_H
#define CRUSTENGINE_POLYGON_H

#include <cstdint>

#include "logging/ExceptionsHandler.h"
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
        Polygon() = default;

        /**
         * @brief Destroy the Polygon object. Deallocate the vertices.
         */
        virtual ~Polygon() = default;

        /**
         * @brief Get the vertex at the specified index.
         *
         * @param p_index The index of the vertex to get.
         * @return The vertex at the specified index.
         */
        inline Vector3<>& getVertex(uint8_t p_index) {
            return m_vertices[p_index];
        }

        /**
         * @brief Set the vertex at the specified index.
         *
         * @param p_index The index of the vertex to set.
         * @param p_x The x coordinate of the vertex.
         * @param p_y The y coordinate of the vertex.
         * @param p_z The z coordinate of the vertex.
         */
        void setVertex(uint8_t p_index, float p_x, float p_y, float p_z) {
            if (p_index >= V) {
                ExceptionsHandler::throwError("Index out of range for polygon of size [%d]: %d", V, p_index);
            }

            m_vertices[p_index].x() = p_x;
            m_vertices[p_index].y() = p_y;
            m_vertices[p_index].z() = p_z;
        }


    private:
        Vector3<> m_vertices[V]; /**< The vertices of the polygon. */
    };
}

#endif /* CRUSTENGINE_POLYGON_H */
