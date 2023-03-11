#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include <Math/Vector3.hpp>
#include <Math/Triangle.hpp>

class Polygon : public Triangle
{
public:
    using Triangle::Triangle;

    Vector3& Normal();
private:
    Vector3* normal {nullptr};
};

Vector3& Polygon::Normal() 
{
    if(normal != nullptr)
        return *normal;

    normal = new Vector3();
    static Vector3 line1;
    static Vector3 line2;

    line1 = *GetPoint(1);
    line1 -= *GetPoint(0);

    line2 = *GetPoint(2);
    line2 -= *GetPoint(0);

    normal->SetX(line1.Y() * line2.Z() - line1.Z() * line2.Y());
    normal->SetY(line1.Z() * line2.X() - line1.X() * line2.Z());
    normal->SetZ(line1.X() * line2.Y() - line1.Y() * line2.X());

    static double normalLen;
    normalLen = Math::SquareRoot(normal->X() * normal->X() + normal->Y() * normal->Y() + normal->Z() * normal->Z());
    (*normal) /= normalLen;

    return *normal;
}

#endif