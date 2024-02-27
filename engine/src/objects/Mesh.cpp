#include "objects/Mesh.h"

#include <utility>

namespace Crust {
    Crust::Mesh::Mesh() {

    }

    Mesh::Mesh(std::string name) {

    }

    Mesh::~Mesh() {

    }

    void Mesh::addPolygon(Triangle &p_poli) {

    }

    Triangle &Mesh::getPolygon(const uint32_t p_index) const {
        return *m_polygons[p_index]; // TODO review this
    }

    uint32_t Mesh::getPolygonsCount() const {
        return 0;
    }

    void Mesh::setName(std::string p_newName) {
        m_name = std::move(p_newName); // TODO why std::move
    }

    std::string Mesh::getName() const {
        return m_name;
    }
}