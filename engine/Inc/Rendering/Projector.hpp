#ifndef _PROJECTOR_HPP_
#define _PROJECTOR_HPP_

#include <Math/Matrix.hpp>

#include <Objects/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Triangle.hpp>

#include <Objects/RenderObject.hpp>
#include <Objects/Lightining/LightSource.hpp>

#include <Logging/ObjectLogger.hpp>

class Projector
{
public:
    // TODO add documentation about it
    typedef struct ProjectionData // FIXME use Vectors instead of doubles
    {
        bool renderable = false;
        float x1 = 0, y1 = 0, z1 = 0;
        float x2 = 0, y2 = 0, z2 = 0;
        float x3 = 0, y3 = 0, z3 = 0;
        uint8_t light = 0;
    } ProjectionData;

    Projector(uint32_t _windowWidth, uint32_t _windowHeigth);

    ~Projector() = default;

    /**
     * @brief Projects given polygon using #projMatrix.
     *
     * @details Class used in #DrawMesh method. It takes 3D space parameters and projects given #poli accordingly to it's position (in future also rotation) and scene's lightining.
     *
     * @param poli Projected polygon.
     * @param pos Projected polygon's mesh position in 3D space.
     * @param rot Projected polygon's mesh rotataion in 3D space.
     * @param cam Camera, from which perspective the polygon will be projected.
     * @param projectLight Flag if the light should be proojected.
     *
     * @return Projected polygon. //TODO fix documentation
     */
    ProjectionData &ProjectPolygon(Polygon &poli, Matrix<float> &translationMat);

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
     * @param cam Camera from which perspective objects will be rendered.
     *
     * @sa Camera.hpp RenderObject.hpp
     */
    void RecalculateProjectionMatrix(Camera &cam);

    /**
     * @brief Recalculates the view matrix for given camera. //TODO fix documentation
     *
     * @param cam Camera from which perspective objects will be rendered.
     *
     * @sa Camera.hpp RenderObject.hpp
     */
    void RecalculateViewMatrix(Camera &cam);

    /**
     * @brief Recalculates the lightning for the next projection. It calulates the light direction and intensivity.
     *
     * @param light Light source from which light will be projected.
     * @param projectLight Flag if the light should be projected.
     */
    void RecalculateLightning(LightSource &light, bool projectLight);

    /**
     * @brief Calculates the translation matrix for given transform.
     *
     * @param transform Transform from which perspective object will be rendered.
     * @return Matrix<float>& Translation matrix for given object.
     */
    Matrix<float> &CalculateTranslationMatrix(Transform &transform);

    /* This value should not be changed without full understanding of this change! */
    static constexpr int PROJ_MATRIX_SIZE{4}; //!< Projection matrix size. Most of the time it will not changed as calculation for projection will most likely not changed.

private:
    uint32_t _width{0};      //!< Assigned window width. Calulated on Renderer creation.
    uint32_t _height{0};     //!< Assigned window height. Calulated on Renderer creation.
    float _aspectRatio{0.0}; //!< Assigned window aspect ration. Calulated on Renderer creation.

    Matrix<float> _projMat{PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0f};  //!< Projection matrix. See Renderer::RecalculateProjectionMatrix.
    Matrix<float> _transMat{PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0f}; //!< Translation matrix. See Renderer::CalculateTranslationMatrix.
    Matrix<float> _viewMat{PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0f};  //!< View matrix. See Renderer::RecalculateViewMatrix.

    Vector3<> r_lightDir{0.0f}; //!< Light direction. See Renderer::DrawMesh.
    uint8_t _lightIntensivity;  //!< Light intensivity. See Renderer::DrawMesh.
    bool _projectLight;         //!< Flag if the light should be projected. See Renderer::DrawMesh.

    ProjectionData r_result; //!< Result of projection. Temporary value returned when we finish projecting polygin. See Renderer::ProjectPolygon.
};

Projector::Projector(uint32_t _width, uint32_t _height) : _width(_width), _height(_height)
{
    _aspectRatio = ((float)_height / (float)_width);
}

Projector::ProjectionData &Projector::ProjectPolygon(Polygon &poli, Matrix<float> &translationMat)
{
    Vector4<> transformedP1 = poli.GetPoint(0).ToVector4(1.0f);
    Vector4<> transformedP2 = poli.GetPoint(1).ToVector4(1.0f);
    Vector4<> transformedP3 = poli.GetPoint(2).ToVector4(1.0f);

    /* Translation - object movement, rotation and scaling */
    transformedP1 *= translationMat;
    transformedP2 *= translationMat;
    transformedP3 *= translationMat;

    /* Calculating polygons plane normal vector to see which direction it is facing */
    Vector3<> normal = Vector3<>::PolygonNormal(transformedP1.ToVector3(), transformedP2.ToVector3(), transformedP3.ToVector3());

    /* Calculate dot product of this normal vector to see if it is visible by the camera*/
    r_result.renderable = normal.Dot(transformedP1.ToVector3()) < 0.0f;
    if (r_result.renderable)
    {
        /* Illumination - see how many light is being placed onto this plane */
        if (_projectLight)
        {
            float lightDotProduct = normal.Dot(r_lightDir);
            if (lightDotProduct < 0.0f)
                lightDotProduct = 0.0f;

            r_result.light = lightDotProduct * _lightIntensivity;
        }
        else
            r_result.light = 255;

        /* Camera movement */
        // transformedP1 *= r_viewMat; // Not working
        // transformedP2 *= r_viewMat;
        // transformedP3 *= r_viewMat;

        /* Projecting object's triangle onto 2D plane */
        transformedP1 *= _projMat;
        transformedP2 *= _projMat;
        transformedP3 *= _projMat;

        Vector3<> projectedP1 = transformedP1.ToVector3(); // Problem wyddaje się być w tym na czym wykonujemy tę wfunkcję (jak dajemy *this to normalnie wykonuje się = z init list)
        Vector3<> projectedP2 = transformedP2.ToVector3(); // FIXME moze brak copy constructora dla Vector3 iu Vector4 powoduje te wycieki???????
        Vector3<> projectedP3 = transformedP3.ToVector3();

        /* Scaling object's triangle to world space */
        projectedP1 /= transformedP1.W();
        projectedP2 /= transformedP2.W();
        projectedP3 /= transformedP3.W();

        Vector3<> viewOffset(1.0f, 1.0f, 0.0f);
        projectedP1 += viewOffset;
        projectedP2 += viewOffset;
        projectedP3 += viewOffset;

        projectedP1.SetX(projectedP1.X() * _width * 0.5);
        projectedP1.SetY(projectedP1.Y() * _height * 0.5);
        projectedP2.SetX(projectedP2.X() * _width * 0.5);
        projectedP2.SetY(projectedP2.Y() * _height * 0.5);
        projectedP3.SetX(projectedP3.X() * _width * 0.5);
        projectedP3.SetY(projectedP3.Y() * _height * 0.5);

        /* Assigning the result */
        r_result.x1 = projectedP1.X();
        r_result.y1 = projectedP1.Y();
        r_result.z1 = projectedP1.Z();

        r_result.x2 = projectedP2.X();
        r_result.y2 = projectedP2.Y();
        r_result.z2 = projectedP2.Z();

        r_result.x3 = projectedP3.X();
        r_result.y3 = projectedP3.Y();
        r_result.z3 = projectedP3.Z();
    }
    return r_result;
}

void Projector::RecalculateProjectionMatrix(Camera &cam)
{
    double q = cam.GetFFar() / (cam.GetFFar() - cam.GetFNear());
    _projMat[0][0] = _aspectRatio * cam.GetFFovRad();
    _projMat[1][1] = cam.GetFFovRad();
    _projMat[2][2] = q;
    _projMat[3][2] = 1.0;
    _projMat[2][3] = -cam.GetFNear() * q;
}

void Projector::RecalculateViewMatrix(Camera &cam)
{ // TODO Refactor - it does not work properly
    Vector3<> target = cam.GetTransform().GetPosition();
    // target += {0.0, 0.0, 0.0};
    target += cam.GetTransform().GetEulerRotation();
    // ObjectLogger::Log("Target", target);

    static Vector3<> newForward;
    newForward = target;
    newForward -= cam.GetTransform().GetPosition();
    // ObjectLogger::Log("New Forward Before normalization", newForward);
    newForward.Normalize();
    // ObjectLogger::Log("New Forward", newForward);

    static Vector3<> a;
    a = newForward;
    a *= newForward.Dot(Transform::Up());
    // ObjectLogger::Log("A", a);

    static Vector3<> newUp;
    newUp = Transform::Up();
    newUp -= a;
    newUp.Normalize();
    // ObjectLogger::Log("New Up", newUp);

    static Vector3<> newRight;
    newRight = newUp.Cross(newForward);
    // ObjectLogger::Log("New Right", newRight);

    // // First column
    // r_viewMat[0][0] = newRight.X();
    // r_viewMat[1][0] = newUp.X();
    // r_viewMat[2][0] = newForward.X();
    // r_viewMat[3][0] = cam.GetTransform().GetPosition().X();

    // // Second column
    // r_viewMat[0][1] = newRight.Y();
    // r_viewMat[1][1] = newUp.Y();
    // r_viewMat[2][1] = newForward.Y();
    // r_viewMat[3][1] = cam.GetTransform().GetPosition().Y();

    // // Third column
    // r_viewMat[0][2] = newRight.Z();
    // r_viewMat[1][2] = newUp.Z();
    // r_viewMat[2][2] = newForward.Z();
    // r_viewMat[3][2] = cam.GetTransform().GetPosition().Z();

    // // Fourth column
    // r_viewMat[0][3] = 0.0;
    // r_viewMat[1][3] = 0.0;
    // r_viewMat[2][3] = 0.0;
    // r_viewMat[3][3] = 1.0;

    //----------------------------------------

    // First column
    _viewMat[0][0] = newRight.X();
    _viewMat[0][1] = newRight.Y();
    _viewMat[0][2] = newRight.Z();
    _viewMat[0][3] = 0.0; // -newRight.Dot(cam.GetTransform().GetPosition())

    // Second column
    _viewMat[1][0] = newUp.X();
    _viewMat[1][1] = newUp.Y();
    _viewMat[1][2] = newUp.Z();
    _viewMat[1][3] = 0.0; // -newUp.Dot(cam.GetTransform().GetPosition())

    // Third column
    _viewMat[2][0] = newForward.X();
    _viewMat[2][1] = newForward.Y();
    _viewMat[2][2] = newForward.Z();
    _viewMat[2][3] = 0.0; // -newForward.Dot(cam.GetTransform().GetPosition())

    // Fourth column
    _viewMat[3][0] = cam.GetTransform().GetPosition().X();
    _viewMat[3][1] = cam.GetTransform().GetPosition().Y();
    _viewMat[3][2] = cam.GetTransform().GetPosition().Z();
    _viewMat[3][3] = 1.0;

    // Inversing this matrix - try to do it without transposing

    // First column
    _viewMat[0][0] = _viewMat[0][0];
    _viewMat[0][1] = _viewMat[1][0];
    _viewMat[0][2] = _viewMat[2][0];
    _viewMat[0][3] = 0.0f;

    // Second column
    _viewMat[1][0] = _viewMat[0][1];
    _viewMat[1][1] = _viewMat[1][1];
    _viewMat[1][2] = _viewMat[2][1];
    _viewMat[1][3] = 0.0f;

    // Third column
    _viewMat[2][0] = _viewMat[0][2];
    _viewMat[2][1] = _viewMat[1][2];
    _viewMat[2][2] = _viewMat[2][2];
    _viewMat[2][3] = 0.0f;

    // Fourth column
    _viewMat[3][0] = -(_viewMat[3][0] * _viewMat[0][0] + _viewMat[3][1] * _viewMat[1][0] + _viewMat[3][2] * _viewMat[2][0]);
    _viewMat[3][1] = -(_viewMat[3][0] * _viewMat[0][1] + _viewMat[3][1] * _viewMat[1][1] + _viewMat[3][2] * _viewMat[2][1]);
    _viewMat[3][2] = -(_viewMat[3][0] * _viewMat[0][2] + _viewMat[3][1] * _viewMat[1][2] + _viewMat[3][2] * _viewMat[2][2]);
    _viewMat[3][3] = 1.0f;
}

void Projector::RecalculateLightning(LightSource &lightSource, bool projectLight)
{

    r_lightDir = lightSource.GetTransform().GetEulerRotation().Normalized();
    _lightIntensivity = lightSource.GetIntensivity();
    _projectLight = projectLight;
}

Matrix<float> &Projector::CalculateTranslationMatrix(Transform &transform)
{ // TODO refactor this
    Matrix<float> translationMat(4, 4, 0.0);
    translationMat.MakeIdentity();
    translationMat[0][3] = transform.GetPosition().X();
    translationMat[1][3] = transform.GetPosition().Y();
    translationMat[2][3] = transform.GetPosition().Z();
    translationMat[3][3] = 1.0f;

    Matrix<float> scaleMat(4, 4, 0.0);
    scaleMat[0][0] = transform.GetScale().X();
    scaleMat[1][1] = transform.GetScale().Y();
    scaleMat[2][2] = transform.GetScale().Z();
    scaleMat[3][3] = 1.0f;

    Matrix<float> rotationZMat(4, 4, 0.0);
    rotationZMat[0][0] = Math::Cos(transform.GetEulerRotation().Z());
    rotationZMat[0][1] = Math::Sin(transform.GetEulerRotation().Z());
    rotationZMat[1][0] = -Math::Sin(transform.GetEulerRotation().Z());
    rotationZMat[1][1] = Math::Cos(transform.GetEulerRotation().Z());
    rotationZMat[2][2] = 1.0f;
    rotationZMat[3][3] = 1.0f;

    Matrix<float> rotationXMat(4, 4, 0.0);
    rotationXMat[0][0] = 1.0f;
    rotationXMat[1][1] = Math::Cos(transform.GetEulerRotation().X());
    rotationXMat[1][2] = Math::Sin(transform.GetEulerRotation().X());
    rotationXMat[2][1] = -Math::Sin(transform.GetEulerRotation().X());
    rotationXMat[2][2] = Math::Cos(transform.GetEulerRotation().X());
    rotationXMat[3][3] = 1.0f;

    Matrix<float> rotationYMat(4, 4, 0.0); // Not tested
    rotationYMat[0][0] = Math::Cos(transform.GetEulerRotation().Y());
    rotationYMat[0][2] = Math::Sin(transform.GetEulerRotation().Y());
    rotationYMat[2][0] = -Math::Sin(transform.GetEulerRotation().Y());
    rotationYMat[1][1] = 1.0f;
    rotationYMat[2][2] = Math::Cos(transform.GetEulerRotation().Y());
    rotationYMat[3][3] = 1.0f;

    Matrix<float> worldMat(4, 4, 0.0);
    worldMat.MakeIdentity();
    worldMat = rotationZMat;
    worldMat *= rotationXMat;
    worldMat *= rotationYMat;
    worldMat *= translationMat;
    worldMat *= scaleMat;

    _transMat = worldMat;
    return _transMat;
}

#endif /* _PROJECTOR_HPP_ */