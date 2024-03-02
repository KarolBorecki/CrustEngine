#ifndef CRUSTENGINE_MESH_H
#define CRUSTENGINE_MESH_H

#include <string>
#include <utility>

#include "math/geometry/Triangle.h"
#include "static/Config.h"

namespace {
    template<typename T = float>
    class Vector3;
}

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
        explicit Mesh(const char* name);

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
        Triangle &getPolygon(uint32_t p_index) const;

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
        void setName(const char* p_newName);

        /**
         * @brief Getter for #name field.
         *
         * @return The mesh's file name.
         */
        const char* getName() const;

    private:
        const char* m_name; //!< Name of the mesh.
        std::vector<Triangle*> m_polygons; //!< Array of polygons that this mesh consists of.
    };
}

#endif /* CRUSTENGINE_MESH_H */
