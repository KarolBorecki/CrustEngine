#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include <Math/Vector3.hpp>
#include <Math/Triangle.hpp>

/**
 * @brief This class represents renderable piece of an mesh.
 * @details It is a wrapper for a mathematical shape that represents renderable plane. Obj type uses a triangle so mostly it will be it. But it if we need anything else we can just modify this class.
 */
class Polygon : public Triangle //TODO triangle should derive from Polygon!!!!! Polygon should be base class!
{
public:
    using Triangle::Triangle;
    ~Polygon();

private:
};

Polygon::~Polygon()
{
}

#endif