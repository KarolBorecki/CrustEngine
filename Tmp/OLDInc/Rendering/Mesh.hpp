#ifndef _MESH_HPP_
#define _MESH_HPP_

#include <vector>

#include <Math/Vector3.hpp>
#include <Rendering/Polygon.hpp>

#define DEFAULT_MESH_NAME "NO NAME" //!< Default polygon name that is given when no name was provided.

namespace crust {
    template<class, typename>
    class Vector3;


// TODO maybe try to use struct instead of a class
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
         * @param poli Handler to added triangle.
         */
        void AddPolygon(Polygon &poli);

        /**
         * @brief Getter for polygon.
         *
         * @param index The index in #polygons for got polygon.
         */
        Polygon &GetPolygon(const uint32_t index) const;

        /**
         * @brief Getter for point of polygon of specified index.
         *
         * @param poliIndex Triangle index.
         * @param pointIndex Triangle's point index.
         */
        const crust::Vector3<> &GetPoint(const uint32_t poliIndex, const uint32_t pointIndex) const;

        /**
         * @brief Getter for polygons count.
         *
         * @return polygons count.
         */
        uint32_t GetPolygonsCount() const;

        /**
         * @brief Setter for #name field.
         *
         * @param newName new mesh's name.
         */
        void SetName(std::string newName);

        /**
         * @brief Getter for #name field.
         *
         * @return The mesh's file name.
         */
        std::string GetName() const;

    private:
        std::string _name; //!< Mesh name. For *.obj file it is 'o' value. For others file: mesh's file path. It is just representative and has no influence on mesh rendering.

        std::vector<Polygon *> _polygons; //!< Polygons, of which the mesh consists. Each of it will be then projected onto the scene.
    };

    inline Mesh::Mesh() : _name(DEFAULT_MESH_NAME) {}

    inline Mesh::Mesh(std::string meshName) : _name(meshName) {}

    Mesh::~Mesh() {
        for (auto poli: _polygons)
            delete poli;
    }

    inline void Mesh::AddPolygon(Polygon &poli) { _polygons.push_back(&poli); }

    inline Polygon &Mesh::GetPolygon(const uint32_t index) const { return *(_polygons[index]); }

    inline const crust::Vector3<> &Mesh::GetPoint(const uint32_t poliIndex, const uint32_t pointIndex) const {
        return _polygons[poliIndex]->GetPoint(pointIndex);
    }

    inline uint32_t Mesh::GetPolygonsCount() const { return _polygons.size(); }

    inline void Mesh::SetName(std::string newName) { _name = newName; }

    inline std::string Mesh::GetName() const { return _name; }

}
#endif /* _MESH_HPP_ */