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

    /**
     * @brief Calculates normal vector of plane that this polygon represents.
     *
     * @return Vector3& Normal vector of this plane.
     */
    Vector3<> &Normal();

private:
    Vector3<> *p_normal{nullptr};
};

Polygon::~Polygon()
{
    if (p_normal == nullptr)
        return;
    delete p_normal;
}

Vector3<> &Polygon::Normal()
{
    if (p_normal != nullptr) // FIXME After rotation this is ought to be recalculated - this will generate bugs, but for now it is good enough as it is faster
        return *p_normal;

    p_normal = new Vector3();
    static Vector3 line1;
    static Vector3 line2;

    line1 = GetPoint(1);
    line1 -= GetPoint(0);

    line2 = GetPoint(2);
    line2 -= GetPoint(0);

    p_normal->SetX(line1.Y() * line2.Z() - line1.Z() * line2.Y());
    p_normal->SetY(line1.Z() * line2.X() - line1.X() * line2.Z());
    p_normal->SetZ(line1.X() * line2.Y() - line1.Y() * line2.X());

    static double normalLen;
    normalLen = Math::SquareRoot(p_normal->X() * p_normal->X() + p_normal->Y() * p_normal->Y() + p_normal->Z() * p_normal->Z());
    (*p_normal) /= normalLen;

    return *p_normal;
}

#endif