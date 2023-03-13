#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <Math/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Triangle.hpp>
#include <Rendering/Objects/RenderObject.hpp>

/**
 * @brief Class used to render simple shapes on the window.
 *
 * @details Class held by RenderWindow.hpp for drawing purposes.
 * It is able to render all shapes that is needed to show mesh on the flat screen.
 */
class Renderer : public RendererWrapper
{
public:
  /**
   * @details Creates new object of type Matrix for #projMatrix field.
   *
   * @param _width Width of the window that this Renderer is applied to.
   * @param _height Height of the window that this Renderer is applied to.
   */
  Renderer(uint32_t _width, uint32_t _height);
  /**
   * @details If projMatrix is not nullptr deletes it.
   */
  ~Renderer();

  /**
   * @brief Draws given triangle on the screen.
   *
   * @param tri Triangle that will be drawn.
   *
   * @sa Triangle.hpp
   */
  void DrawPolygon(Polygon& tri);

  /**
   * @brief Draws given mesh on the screen
   *
   * @details Class held by RenderWindow.hpp for drawing purposes.
   * It is able to render all shapes that is needed to show mesh on the flat screen.
   *
   * @param mesh Mesh that will be drawn.
   * @param pos Position in 3D space at which the mesh will be drawn.
   * @param rot Rotation in 3D space at which the mesh will be drawn.
   * @param cam Camera, from which perspective the mesh will be projected.
   * @param projectLight Flag if the light should be proojected.
   *
   * @sa Mesh.hpp
   */
  void DrawMesh(Mesh &mesh, Vector3 &pos, Vector3 &rot, Camera &cam, Vector3 &lightDir, bool projectLight);

  /**
   * @brief Projects given triangle using #projMatrix.
   *
   * @details Class held by RenderWindow.hpp for drawing purposes.
   * It is able to render all shapes that is needed to show mesh on the flat screen.
   *
   * @param tri Projected triangle.
   * @param pos Projected triangle's mesh position in 3D space.
   * @param rot Projected triangle's mesh rotataion in 3D space.
   * @param cam Camera, from which perspective the triangle will be projected.
   * @param projectLight Flag if the light should be proojected.
   *
   * @return Projected triangle.
   */
  Polygon &ProjectPolygon(Polygon &poli, Vector3 &pos, Vector3 &rot, Camera &cam, Vector3 &lightDir, bool projectLight);

  /**
   * @brief Getter for #projMatrix field.
   *
   * @return Handler to #projMatrix field.
   */
  Matrix<double> &GetProjectionMatrix() const;

  /**
   * @brief Recalculates the projection matrix for given camera.
   *
   * @details The projection matrix is calculated as here is explained: <a href="https://en.wikipedia.org/wiki/3D_projection#Perspective_projection">Projection matrix</a> <br>
   *
   * @note The engine calculation is made based on <a link="https://www.youtube.com/watch?v=ih20l3pJoeU">this formulas</a>.
   *
   * @param cam Camera from which perspective objects will rendered.
   *
   * @sa Camera.hpp RenderObject.hpp
   */
  void RecalculateProjectionMatrix(Camera &cam);

  /* This value should not be changed without full understanding of this change! */
  static constexpr int PROJ_MATRIX_SIZE{4};

private:
  double aspectRatio{0.0};    //!< Assigned window aspect ration. Calulated on Renderer creation.
  Matrix<double> *projMatrix; //!< Projection matrix. See Renderer::RecalculateProjectionMatrix.
};

Renderer::Renderer(uint32_t _width, uint32_t _height) : RendererWrapper(_width, _height)
{
  aspectRatio = ((double)_height / (double)_width);
  projMatrix = new Matrix<double>(PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0);
}

Renderer::~Renderer()
{
  if (projMatrix == nullptr)
    return;
  delete projMatrix;
}

void Renderer::DrawMesh(Mesh &mesh, Vector3 &pos, Vector3 &rot, Camera &cam, Vector3 &lightDir, bool projectLight)
{
  SetDrawColor(RendererWrapper::RendererColor::WHITE);
  for (int i = 0; i < mesh.GetPolygonsCount(); i++)
  {
    ProjectPolygon(mesh.GetPolygon(i), pos, rot, cam, lightDir, projectLight);
  }
}

Polygon &Renderer::ProjectPolygon(Polygon &poli, Vector3 &pos, Vector3 &rot, Camera &cam, Vector3 &lightDir, bool projectLight)
{

  // DOBIERA Pamięci!!!! Jednak nie XD Jednak tak :((((
  static Matrix<double> projMat = GetProjectionMatrix();
  static Polygon result;

  /* Moving object's triangle */
  static Vector3 movedP1;
  static Vector3 movedP2;
  static Vector3 movedP3;

  movedP1 = poli.GetPoint(0);
  movedP2 = poli.GetPoint(1);
  movedP3 = poli.GetPoint(2);

  movedP1 += pos;
  movedP2 += pos;
  movedP3 += pos;

  movedP1 -= cam.GetTransform().GetPosition(); //TODO move to local variable
  movedP2 -= cam.GetTransform().GetPosition();
  movedP3 -= cam.GetTransform().GetPosition();

  /* Normalizing object's triangle */
  static Vector3 normal;
  static Vector3 line1;
  static Vector3 line2;

  line1 = movedP2;
  line1 -= movedP1;

  line2 = movedP3;
  line2 -= movedP1;

  normal.SetX(line1.Y() * line2.Z() - line1.Z() * line2.Y());
  normal.SetY(line1.Z() * line2.X() - line1.X() * line2.Z());
  normal.SetZ(line1.X() * line2.Y() - line1.Y() * line2.X());

  static double normalLen;
  normalLen = Math::SquareRoot(normal.X() * normal.X() + normal.Y() * normal.Y() + normal.Z() * normal.Z());
  normal /= normalLen;

  /* calculate dot product */
  static double dotProduct;
  dotProduct = normal.X() * (movedP1.X() - cam.GetTransform().GetPosition().X()) +
               normal.Y() * (movedP1.Y() - cam.GetTransform().GetPosition().Y()) +
               normal.Z() * (movedP1.Z() - cam.GetTransform().GetPosition().Z());


  if (dotProduct < 0.0)
  {
    /* Illumination */
    static double lightDirNormalLen;
    static Vector3 lightDirNormal;
    static double lightDotProduct;

    if (projectLight)
    {
      lightDirNormal = lightDir;
      lightDirNormalLen = Math::SquareRoot(lightDir.X() * lightDir.X() + lightDir.Y() * lightDir.Y() + lightDir.Z() * lightDir.Z());
      lightDirNormal /= lightDirNormalLen;

      lightDotProduct = normal.X() * lightDirNormal.X() + normal.Y() * lightDirNormal.Y() + normal.Z() * lightDirNormal.Z();
    }
    else
    {
      lightDotProduct = 1.0;
    }

    /* Projecting object's triangle */
    static Vector4 extendedP1;
    static Vector4 extendedP2;
    static Vector4 extendedP3;

    extendedP1 = {movedP1.X(), movedP1.Y(), movedP1.Z(), 1.0};
    extendedP2 = {movedP2.X(), movedP2.Y(), movedP2.Z(), 1.0};
    extendedP3 = {movedP3.X(), movedP3.Y(), movedP3.Z(), 1.0};
 
    extendedP1 *= projMat; // Wynik tego mnozenia jest zly
    extendedP2 *= projMat;
    extendedP3 *= projMat;

    static Vector3 projectedP1;
    static Vector3 projectedP2;
    static Vector3 projectedP3;

    projectedP1 = {extendedP1.X(), extendedP1.Y(), extendedP1.Z()};
    projectedP2 = {extendedP2.X(), extendedP2.Y(), extendedP2.Z()};
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

    projectedP1.SetX(projectedP1.X() * Width());
    projectedP1.SetY(projectedP1.Y() * Height());
    projectedP2.SetX(projectedP2.X() * Width());
    projectedP2.SetY(projectedP2.Y() * Height());
    projectedP3.SetX(projectedP3.X() * Width());
    projectedP3.SetY(projectedP3.Y() * Height());

    result.SetPoints(projectedP1.X(), projectedP1.Y(), projectedP1.Z(), projectedP2.X(), projectedP2.Y(), projectedP2.Z(), projectedP3.X(), projectedP3.Y(), projectedP3.Z());
    DrawFilledTri(result.GetPoint(0).X(), result.GetPoint(0).Y(), result.GetPoint(1).X(), result.GetPoint(1).Y(), result.GetPoint(2).X(), result.GetPoint(2).Y(), (uint8_t)(lightDotProduct * 255), (uint8_t)(lightDotProduct * 255), (uint8_t)(lightDotProduct * 255));
  }
  return result;
}

inline Matrix<double> &Renderer::GetProjectionMatrix() const { return *projMatrix; }

void Renderer::RecalculateProjectionMatrix(Camera &cam)
{
  double q = cam.GetFFar() / (cam.GetFFar() - cam.GetFNear());
  (*projMatrix)[0][0] = aspectRatio * cam.GetFFovRad();
  (*projMatrix)[1][1] = cam.GetFFovRad();
  (*projMatrix)[2][2] = q;
  (*projMatrix)[3][2] = 1.0;
  (*projMatrix)[2][3] = -cam.GetFNear() * q;
}

#endif /* _RENDERER_HPP_ */
