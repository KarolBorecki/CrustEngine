#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <math.h> /* cos, sin, sqrt */

#include <Physics/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Physics/Vector3.hpp>
#include <Physics/Vector4.hpp>
#include <Physics/Triangle.hpp>
#include <Rendering/Objects/RenderObject.hpp>

/**
* @brief Class used to render simple shapes on the window.
*
* @details Class held by RenderWindow.hpp for drawing purposes.
* It is able to render all shapes that is needed to show mesh on the flat screen.
*/
class Renderer : public RendererWrapper {
public:
  /**
  * @details Creates new object of type Matrix for #projMatrix field.
  *
  * @param _width Width of the window that this Renderer is applied to.
  * @param _height Height of the window that this Renderer is applied to.
  */
  Renderer(int _width, int _height);
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
  void DrawTri(Triangle* tri);

  /**
  * @brief Draws given mesh on the screen
  *
  * @details Class held by RenderWindow.hpp for drawing purposes.
  * It is able to render all shapes that is needed to show mesh on the flat screen.
  *
  * @param mesh Mesh that will be drawn.
  * @param pos Position in 3D space at which the mesh will be drawn.
  * @param cam Camera, from which perspective the mesh will be projected.
  *
  * @sa Mesh.hpp
  */
  void DrawMesh(Mesh* mesh, Vector3* pos, Camera* cam, Vector3* lightDir);

  /**
  * @brief Projects given triangle using #projMatrix.
  *
  * @details Class held by RenderWindow.hpp for drawing purposes.
  * It is able to render all shapes that is needed to show mesh on the flat screen.
  *
  * @param tri Projected triangle.
  * @param pos Projected triangle's mesh position in 3D space.
  * @param cam Camera, from which perspective the triangle will be projected.
  *
  * @return Projected triangle.
  */
  Triangle* ProjectTriangle(Triangle* tri, Vector3* pos, Camera* cam, Vector3* lightDir);

  /**
  * @brief Getter for #projMatrix field.
  *
  * @return Handler to #projMatrix field.
  */
  Matrix* GetProjectionMatrix();

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
  void RecalculateProjectionMatrix(Camera* cam);

  /* This value should not be changed without full understanding of this change! */
  static constexpr int PROJ_MATRIX_SIZE { 4 };

private:
  double aspectRatio { 0.0 }; //!< Assigned window aspect ration. Calulated on Renderer creation.
  Matrix* projMatrix; //!< Projection matrix. See Renderer::RecalculateProjectionMatrix.

};

Renderer::Renderer(int _width, int _height) : RendererWrapper(_width, _height) {
  Logger::Log("============Rednerer creation============");
  aspectRatio = ((double)_height / (double)_width);
  Logger::Info("ASPECT RATIO: %lf", aspectRatio);
  projMatrix = new Matrix(PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0);
  Logger::Log("============Rednerer creation DONE============");
}

Renderer::~Renderer() {
  if (projMatrix == nullptr) return;
  delete projMatrix;
}

void Renderer::DrawMesh(Mesh* mesh, Vector3* pos, Camera* cam, Vector3* lightDir) {
  Logger::Log("Drawing mesh %s", mesh->GetName().c_str());
  SetDrawColor(RendererWrapper::RendererColor::WHITE);
  for(int i=0; i < mesh->GetTrianglesCount(); i++) {
    ProjectTriangle(mesh->GetTriangle(i), pos, cam, lightDir);
  }
  Logger::Log("Drawing mesh %s DONE!", mesh->GetName().c_str());
}

Triangle* Renderer::ProjectTriangle(Triangle* tri, Vector3* pos, Camera* cam, Vector3* lightDir) {
  //DOBIERA Pamięci!!!! Jednak nie XD Jednak tak :((((
  static Matrix* projMat = GetProjectionMatrix();
  static Triangle result;

  /* Moving object's triangle */
  static Vector3 movedP1;
  static Vector3 movedP2;
  static Vector3 movedP3;

  movedP1.SetXYZ(tri->GetPoint(0));
  movedP2.SetXYZ(tri->GetPoint(1));
  movedP3.SetXYZ(tri->GetPoint(2));

  Matrix::Add(&movedP1, pos);
  Matrix::Add(&movedP2, pos);
  Matrix::Add(&movedP3, pos);

  /* Normalizing object's triangle */
  static Vector3 normal;
  static Vector3 line1;
  static Vector3 line2;

  line1.SetX(movedP2.X() - movedP1.X());
  line1.SetY(movedP2.Y() - movedP1.Y());
  line1.SetZ(movedP2.Z() - movedP1.Z());

  line2.SetX(movedP3.X() - movedP1.X());
  line2.SetY(movedP3.Y() - movedP1.Y());
  line2.SetZ(movedP3.Z() - movedP1.Z());

  normal.SetX(line1.Y() * line2.Z() - line1.Z() * line2.Y());
  normal.SetY(line1.Z() * line2.X() - line1.X() * line2.Z());
  normal.SetZ(line1.X() * line2.Y() - line1.Y() * line2.X());

  static double normalLen;
  normalLen = sqrt(normal.X() * normal.X() + normal.Y() * normal.Y() + normal.Z() * normal.Z());
  Matrix::Divide(&normal, normalLen);

  /* calculate dot product */
  static double dotProduct;
  dotProduct = normal.X() * (movedP1.X() - cam->GetPosition()->X()) +
               normal.Y() * (movedP1.Y() - cam->GetPosition()->Y()) +
               normal.Z() * (movedP1.Z() - cam->GetPosition()->Z());

  if(dotProduct < 0.0) {
    /* Illumination */
    static double lightDirNormalLen;
    static Vector3 lightDirNormal;
    lightDirNormal.SetXYZ(lightDir);
    lightDirNormalLen = sqrt(lightDir->X() * lightDir->X() + lightDir->Y() * lightDir->Y() + lightDir->Z() * lightDir->Z());
    Matrix::Divide(&lightDirNormal, lightDirNormalLen);
    static double lightDotProduct;
    lightDotProduct = normal.X() * lightDirNormal.X() + normal.Y() * lightDirNormal.Y() + normal.Z() * lightDirNormal.Z();

    /* Projecting object's triangle */
    static Vector4 extendedP1;
    static Vector4 extendedP2;
    static Vector4 extendedP3;

    extendedP1.SetXYZW(&movedP1, 1.0);
    extendedP2.SetXYZW(&movedP2, 1.0);
    extendedP3.SetXYZW(&movedP3, 1.0);

    static Vector4 outMatP1;
    static Vector4 outMatP2;
    static Vector4 outMatP3;

    Matrix::Multiply(&extendedP1, projMat, outMatP1);
    Matrix::Multiply(&extendedP2, projMat, outMatP2);
    Matrix::Multiply(&extendedP3, projMat, outMatP3);

    static Vector3 projectedP1;
    static Vector3 projectedP2;
    static Vector3 projectedP3;

    projectedP1.SetXYZ(outMatP1.GetValue(0,0), outMatP1.GetValue(0,1), outMatP1.GetValue(0,2));
    projectedP2.SetXYZ(outMatP2.GetValue(0,0), outMatP2.GetValue(0,1), outMatP2.GetValue(0,2));
    projectedP3.SetXYZ(outMatP3.GetValue(0,0), outMatP3.GetValue(0,1), outMatP3.GetValue(0,2));

    /* Scaling object's triangle to world space */
    Matrix::Divide(&projectedP1, outMatP1.GetValue(0,3));
    Matrix::Divide(&projectedP2, outMatP2.GetValue(0,3));
    Matrix::Divide(&projectedP3, outMatP3.GetValue(0,3));

    Matrix::Add(&projectedP1, 1);
    Matrix::Add(&projectedP2, 1);
    Matrix::Add(&projectedP3, 1);

    Matrix::Multiply(&projectedP1, 0.5);
    Matrix::Multiply(&projectedP2, 0.5);
    Matrix::Multiply(&projectedP3, 0.5);

    projectedP1.SetX(projectedP1.X() * Width()); projectedP1.SetY(projectedP1.Y() * Height());
    projectedP2.SetX(projectedP2.X() * Width()); projectedP2.SetY(projectedP2.Y() * Height());
    projectedP3.SetX(projectedP3.X() * Width()); projectedP3.SetY(projectedP3.Y() * Height());


    result.SetPoints(projectedP1.X(), projectedP1.Y(), projectedP1.Z(), projectedP2.X(), projectedP2.Y(), projectedP2.Z(), projectedP3.X(), projectedP3.Y(), projectedP3.Z());
    Logger::Log("Dot producy illumination: %lf", lightDotProduct);
    DrawFilledTri(result.GetPoint(0)->X(), result.GetPoint(0)->Y(), result.GetPoint(1)->X(), result.GetPoint(1)->Y(), result.GetPoint(2)->X(), result.GetPoint(2)->Y(), (uint8_t)(lightDotProduct*255), (uint8_t)(lightDotProduct*255), (uint8_t)(lightDotProduct*255));
  }
  return &result;
}

inline Matrix* Renderer::GetProjectionMatrix() { return projMatrix; }

void Renderer::RecalculateProjectionMatrix(Camera* cam) {
  double q = cam->GetFFar() / (cam->GetFFar() - cam->GetFNear());
  projMatrix->PutValue(0, 0, aspectRatio * cam->GetFFovRad());
  projMatrix->PutValue(1, 1, cam->GetFFovRad());
  projMatrix->PutValue(2, 2, q);
  projMatrix->PutValue(2, 3, 1.0);
  projMatrix->PutValue(3, 2, -cam->GetFNear() * q);
  Logger::Info(projMatrix->ToString().c_str());
}


#endif /* _RENDERER_HPP_ */
