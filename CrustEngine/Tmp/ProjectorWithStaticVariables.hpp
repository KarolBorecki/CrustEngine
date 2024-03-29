#ifndef _PROJECTOR_HPP_
#define _PROJECTOR_HPP_

#include <Math/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Triangle.hpp>
#include <Rendering/Objects/RenderObject.hpp>

/**
 * @brief Class used to handle mathematical 3D projection of polygons.
 */
class Projector
{
public:
    /**
     * @brief Temporary data scructure used to store projected polygon data along with it's illumination.
     * @details It is usfilleded in #ProjectPolygon method and passed to Renderer to draw projected polygon.
     */
    typedef struct ProjectionData // FIXME use Vectors instead of doubles
    {
        bool renderable = false;
        float x1 = 0, y1 = 0, z1 = 0;
        float x2 = 0, y2 = 0, z2 = 0;
        float x3 = 0, y3 = 0, z3 = 0;
        Vector3<> p1(), p2(), p3();
        uint8_t light = 0;
    } ProjectionData;

public:
    Projector(uint32_t _windowWidth, uint32_t _windowHeigth);

    ~Projector();

    /**
     * @brief Projects given polygon using #projMatrix.
     *
     * @details Class used in #DrawMesh method. It takes 3D space parameters and projects given #poli accordingly to it's position (in future also rotation) and scene's lightining.
     *
     * @param poli Projected polygon.
     * @param transform Transform of the polygon's object - more precisely transform from which perspective the polygon will be projected.
     * @param cam Camera, from which perspective the polygon will be projected.
     * @param lightDir direction of a light on a scene. This pararmeter is obscure as in the future it will be replaced by a several light sources.
     *
     * @return Projected polygon.
     */
    ProjectionData &ProjectPolygon(Polygon &poli, Transform &transform, Camera &cam, Vector3<> &lightDir);

    /**
     * @brief Getter for #projMatrix field.
     *
     * @return Reference to #projMatrix field.
     */
    const Matrix<double> &GetProjectionMatrix() const; // TODO implement

    /**
     * @brief Recalculates the projection matrix for given camera.
     *
     * @details The projection matrix is calculated as here is explained: <a href="https://en.wikipedia.org/wiki/3D_projection#Perspective_projection">Projection matrix on wikipedia</a> <br>
     *
     * @note The engine calculation is made based on <a link="https://www.youtube.com/watch?v=ih20l3pJoeU">this formulas</a>.
     *
     * @param cam Camera from which perspective objects will rendered.
     *
     * @sa Camera.hpp RenderObject.hpp
     */
    void RecalculateProjectionMatrix(Camera &cam);
    /* This value should not be changed without full understanding of this change! */

    static constexpr int PROJ_MATRIX_SIZE{4}; //!< Projection matrix size. Most of the time it will not changed as calculation for projection will most likely not changed.

private:
    uint32_t width{0};      //!< Assigned window width. Calulated on Renderer creation.
    uint32_t height{0};     //!< Assigned window height. Calulated on Renderer creation.
    float aspectRatio{0.0}; //!< Assigned window aspect ration. Calulated on Renderer creation.

    Matrix<float> &projMat; //!< Projection matrix. See Renderer::RecalculateProjectionMatrix.
    ProjectionData &result; //!< Result of projection. Temporary value returned when we finish projecting polygin. See Renderer::ProjectPolygon.
};

Projector::Projector(uint32_t _width, uint32_t _height) : width(_width), height(_height), result(*(new ProjectionData())), projMat(*(new Matrix<float>(PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0)))
{
    aspectRatio = ((float)_height / (float)_width);
}

Projector::~Projector()
{
    delete &projMat;
    delete &result;
}

Projector::ProjectionData &Projector::ProjectPolygon(Polygon &poli, Transform &transform, Camera &cam, Vector3<> &lightDir)
{
    /* Moving object's triangle */
    Vector3<> movedP1(poli.GetPoint(0));
    Vector3<> movedP2(poli.GetPoint(1));
    Vector3<> movedP3(poli.GetPoint(2));

    movedP1 += transform.GetPosition();
    movedP2 += transform.GetPosition();
    movedP3 += transform.GetPosition();

    movedP1 -= cam.GetTransform().GetPosition(); // TODO move to local variable
    movedP2 -= cam.GetTransform().GetPosition();
    movedP3 -= cam.GetTransform().GetPosition();

    /* Calculating plolygons plane normal vector to see which direction it is facing */
    Vector3<> &normal = poli.Normal();

    /* Calculate dot product of this normal vector to see if it is visible by the camera*/
    float dotProduct = normal.X() * (movedP1.X() - cam.GetTransform().GetPosition().X()) +
                       normal.Y() * (movedP1.Y() - cam.GetTransform().GetPosition().Y()) +
                       normal.Z() * (movedP1.Z() - cam.GetTransform().GetPosition().Z());

    result.renderable = dotProduct < 0.0;

    if (dotProduct < 0.0f)
    {
        /* Illumination - see how many light is being placed onto this plane */
        Vector3<> lightDirNormal(lightDir);
        float lightDirNormalLen = Math::SquareRoot(lightDir.X() * lightDir.X() + lightDir.Y() * lightDir.Y() + lightDir.Z() * lightDir.Z());
        lightDirNormal /= lightDirNormalLen;

        float lightDotProduct = normal.X() * lightDirNormal.X() + normal.Y() * lightDirNormal.Y() + normal.Z() * lightDirNormal.Z();
        if (lightDotProduct < 0.0f)
            lightDotProduct = 0.0f;
        result.light = lightDotProduct * 255;

        /* Projecting object's triangle */
        Vector4<> extendedP1(movedP1.X(), movedP1.Y(), movedP1.Z(), 1.0);
        Vector4<> extendedP2(movedP2.X(), movedP2.Y(), movedP2.Z(), 1.0);
        Vector4<> extendedP3(movedP3.X(), movedP3.Y(), movedP3.Z(), 1.0);

        extendedP1 *= projMat;
        extendedP2 *= projMat;
        extendedP3 *= projMat;

        Vector3<> projectedP1;
        Vector3<> projectedP2;
        Vector3<> projectedP3;

        projectedP1 = {extendedP1.X(), extendedP1.Y(), extendedP1.Z()}; // Problem wyddaje się być w tym na czym wykonujemy tę wfunkcję (jak dajemy *this to normalnie wykonuje się = z init list)
        projectedP2 = {extendedP2.X(), extendedP2.Y(), extendedP2.Z()}; // FIXME moze brak copy constructora dla Vector3 iu Vector4 powoduje te wycieki???????
        projectedP3 = {extendedP3.X(), extendedP3.Y(), extendedP3.Z()};

        /* Scaling object's triangle to world space */
        projectedP1 /= extendedP1.W();
        projectedP2 /= extendedP2.W();
        projectedP3 /= extendedP3.W();

        projectedP1 += 1;
        projectedP2 += 1;
        projectedP3 += 1;

        projectedP1 *= 0.5;
        projectedP2 *= 0.5;
        projectedP3 *= 0.5;

        projectedP1.SetX(projectedP1.X() * width);
        projectedP1.SetY(projectedP1.Y() * height);
        projectedP2.SetX(projectedP2.X() * width);
        projectedP2.SetY(projectedP2.Y() * height);
        projectedP3.SetX(projectedP3.X() * width);
        projectedP3.SetY(projectedP3.Y() * height);

        result.x1 = projectedP1.X();
        result.y1 = projectedP1.Y();
        result.z1 = projectedP1.Z();

        result.x2 = projectedP2.X();
        result.y2 = projectedP2.Y();
        result.z2 = projectedP2.Z();

        result.x3 = projectedP3.X();
        result.y3 = projectedP3.Y();
        result.z3 = projectedP3.Z();
    }
    return result;
}

void Projector::RecalculateProjectionMatrix(Camera &cam)
{
    static double q;
    q = cam.GetFFar() / (cam.GetFFar() - cam.GetFNear());
    projMat[0][0] = aspectRatio * cam.GetFFovRad();
    projMat[1][1] = cam.GetFFovRad();
    projMat[2][2] = q;
    projMat[3][2] = 1.0;
    projMat[2][3] = -cam.GetFNear() * q;
}

#endif /* _PROJECTOR_HPP_ */