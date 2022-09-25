#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include <math.h> /* cos, sin */

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
  * @brief Draws triangle with given coordinates on the screen.
  *
  * @param p1X Point 1 X.
  * @param p1Y Point 1 Y.
  * @param p2X Point 2 X.
  * @param p2Y Point 2 Y.
  * @param p3X Point 3 X.
  * @param p3Y Point 3 Y.
  */
  void DrawTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y);

  /**
  * @brief Draws given mesh on the screen
  *
  * @details Class held by RenderWindow.hpp for drawing purposes.
  * It is able to render all shapes that is needed to show mesh on the flat screen.
  *
  * @param mesh Mesh that will be drawn.
  *
  * @sa Mesh.hpp
  */
  void DrawMesh(Mesh* mesh);

  /**
  * @brief Projects given triangle using #projMatrix.
  *
  * @details Class held by RenderWindow.hpp for drawing purposes.
  * It is able to render all shapes that is needed to show mesh on the flat screen.
  */
  Triangle ProjectTriangle(Triangle* tri);

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

void Renderer::DrawTri(Triangle* tri) {
  DrawLine(tri->GetPoint(0)->X(), tri->GetPoint(0)->Y(), tri->GetPoint(1)->X(), tri->GetPoint(1)->Y());
  DrawLine(tri->GetPoint(1)->X(), tri->GetPoint(1)->Y(), tri->GetPoint(2)->X(), tri->GetPoint(2)->Y());
  DrawLine(tri->GetPoint(2)->X(), tri->GetPoint(2)->Y(), tri->GetPoint(0)->X(), tri->GetPoint(0)->Y());
}

void Renderer::DrawTri(double p1X, double p1Y, double p2X, double p2Y, double p3X, double p3Y) {
  DrawLine(p1X, p1Y, p2X, p2Y);
  DrawLine(p2X, p2Y, p3X, p3Y);
  DrawLine(p3X, p3Y, p1X, p1Y);
}

void Renderer::DrawMesh(Mesh* mesh) {
  Logger::Log("============Drawing mesh %s============", mesh->GetName().c_str());
  SetDrawColor(RendererWrapper::RendererColor::WHITE);
  for(int i=0; i < mesh->GetTrianglesCount(); i++) {
    Triangle projTri = ProjectTriangle(mesh->GetTriangle(i));
    DrawTri(&projTri);
  }
  Logger::Log("============Drawing mesh %s DONE============", mesh->GetName().c_str());
}

Triangle Renderer::ProjectTriangle(Triangle* tri) {
    //DOBIERA Pamięci!!!! Jednak nie XD
  static Matrix* projMat = GetProjectionMatrix();

  //TODO play around with static values
  static Vector4 extendedP1;
  static Vector4 extendedP2;
  static Vector4 extendedP3;
  extendedP1.SetXYZW(tri->GetPoint(0), 1.0);
  extendedP2.SetXYZW(tri->GetPoint(1), 1.0);
  extendedP3.SetXYZW(tri->GetPoint(2), 1.0);

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

  static Triangle result;
  result.SetPoints(projectedP1.X(), projectedP1.Y(), projectedP1.Z(), projectedP2.X(), projectedP2.Y(), projectedP2.Z(), projectedP3.X(), projectedP3.Y(), projectedP3.Z());
  return result;
}

inline Matrix* Renderer::GetProjectionMatrix() { return projMatrix; }

void Renderer::RecalculateProjectionMatrix(Camera* cam) {
  Logger::Log("============Recalculating projection matrix============");
  double a = aspectRatio;
  float f = cam->GetFFovRad();
  double q = cam->GetFFar() / (cam->GetFFar() - cam->GetFNear());
  double zNear = cam->GetFNear();
  Logger::Log(Logger::FontColor::GREY, "a=%lf, f=%lf, q=%lf, zNear=%lf", a, f, q, zNear);
  projMatrix->PutValue(0, 0, a * f);
  projMatrix->PutValue(1, 1, f);
  projMatrix->PutValue(2, 2, q);
  projMatrix->PutValue(2, 3, 1.0);
  projMatrix->PutValue(3, 2, -zNear * q);
  Logger::Info(projMatrix->ToString().c_str());
  Logger::Log("============Recalculating projection matrix DONE============");
}


#endif /* _DRAWER_HPP_ */
