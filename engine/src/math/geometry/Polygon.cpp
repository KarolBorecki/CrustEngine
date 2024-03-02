#include "math/geometry/Polygon.h"

namespace Crust {
    template<uint8_t V>
    Polygon<V>::Polygon() {
        for (uint8_t i = 0; i < V; i++) {
            m_vertices[i] = new Vector3<>();
        }
    }

    template<uint8_t V>
    Polygon<V>::~Polygon() {
        for (uint8_t i = 0; i < V; i++) {
            delete m_vertices[i];
        }
    }

    template<uint8_t V>
    Vector3<> &Polygon<V>::getVertex(uint8_t p_index) {
        return m_vertices[p_index];
    }
}