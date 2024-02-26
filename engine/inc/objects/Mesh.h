#ifndef CRUSTENGINE_MESH_H
#define CRUSTENGINE_MESH_H

#include <string>

#include "math/geometry/Triangle.h"

namespace Crust {
    /**
     * @brief Represents 3D model as mesh consisted of 3D polygons.
     */
    class Mesh {
    public:
        /**
         * @brief Construct a new Mesh object with name set to #Mesh::DEFAULT_MESH_NAME.
         */
        Mesh();

        /**
         * @brief Construct a new Mesh object with name set to #name.
         */
        Mesh(std::string name);

        /**
         * @brief Deletes all of the polygons of this mesh.
         */
        ~Mesh();

        /**
         * @brief Adds the polygon to mesh. It holds the originals so given polygon should be allocated on stack. It will be then deleted in Mesh's destructor.
         *
         * @param p_poli Handler to added triangle.
         */
        void addPolygon(Triangle &p_poli);

        /**
         * @brief Getter for polygon.
         *
         * @param p_index The index in #polygons for got polygon.
         */
        Triangle &getPolygon(const uint32_t p_index) const;

        /**
         * @brief Getter for vertex of the polygon of specified index.
         *
         * @param p_poliIndex Triangle index.
         * @param p_point_index Triangle's point index.
         */
        const Vector3<> &getVertex(const uint32_t p_poli_index, const uint32_t p_point_index) const;

        /**
         * @brief Getter for polygons count.
         *
         * @return polygons count.
         */
        uint32_t getPolygonsCount() const;

        /**
         * @brief Setter for #name field.
         *
         * @param p_newName new mesh's name.
         */
        void setName(std::string p_newName);

        /**
         * @brief Getter for #name field.
         *
         * @return The mesh's file name.
         */
        std::string getName() const;

    private:
        std::string m_name; //!< Name of the mesh.
        std::vector<Triangle*> m_polygons; //!< Array of polygons that this mesh consists of.
    };
}

#endif /* CRUSTENGINE_MESH_H */
