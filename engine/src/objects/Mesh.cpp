#include "objects/Mesh.h"

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
        return initializer;
    }

    const Vector3<> &Mesh::getVertex(const uint32_t p_poli_index, const uint32_t p_point_index) const {
        return <#initializer#>;
    }

    uint32_t Mesh::getPolygonsCount() const {
        return 0;
    }

    void Mesh::setName(std::string p_newName) {
        m_name = p_newName;
    }

    std::string Mesh::getName() const {
        return m_name;
    }
}