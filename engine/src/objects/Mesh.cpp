#include "objects/Mesh.h"

namespace Crust {
    Crust::Mesh::Mesh() : m_name(DEFAULT_MESH_NAME) {}

    Mesh::Mesh(const char* name) : m_name(name){}

    Mesh::~Mesh() {
        for (auto p : m_polygons) {
            delete p;
        }
    }

    void Mesh::addPolygon(Triangle &p_poli) {
        m_polygons.push_back(&p_poli);
    }

    Triangle &Mesh::getPolygon(const uint32_t p_index) const {
        return *m_polygons[p_index]; // TODO review this
    }

    uint32_t Mesh::getPolygonsCount() const {
        return m_polygons.size();
    }

    void Mesh::setName(const char* p_newName) {
        m_name = p_newName; // TODO why std::move
    }

    const char* Mesh::getName() const {
        return m_name;
    }
}