#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include <Physics/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Physics/Vector3.hpp>
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
  void ProjectTriangle(Triangle* tri);

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
  aspectRatio = ((double)_height / (double)_width);
  Logger::Log("ASPECT RATIO: %lf", aspectRatio);
  projMatrix = new Matrix(PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE, 0.0);
}

Renderer::~Renderer() {
  if (projMatrix == nullptr) return;
  delete projMatrix;
}

void Renderer::DrawTri(Triangle* tri) {
  Logger::Log(Logger::FontColor::LIGHT_BLUE, "Drawing:");
  Logger::Log(Logger::FontColor::LIGHT_BLUE, "%s", tri->ToString().c_str());
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
  Logger::Log("Drawing Mesh \' %s \'", mesh->GetName().c_str());

  SetDrawColor(RendererWrapper::RendererColor::WHITE);

  Vector3* p1; Vector3* p2; Vector3* p3;
  Matrix* projMat = GetProjectionMatrix();

  Matrix m1(1, 4, 0.0);
  Matrix m2(1, 4, 0.0);
  Matrix m3(1, 4, 0.0);

  Matrix outMatP1(1, 4, 0.0);
  Matrix outMatP2(1, 4, 0.0);
  Matrix outMatP3(1, 4, 0.0);

  double z1;
  double z2;
  double z3;

  Vector3 projectedP1(1.0);
  Vector3 projectedP2(1.0);
  Vector3 projectedP3(1.0);

  Logger::Log("Attempting to draw mesh");

  for(int i=0; i < mesh->GetTrianglesCount(); i++) {
    Logger::Log(Logger::FontColor::PINK, "Triangle number: %d", i);
    Logger::Log(Logger::FontColor::GREY, "%s", mesh->GetTriangle(i)->ToString().c_str());
    p1 = mesh->GetPoint(i, 0);
    p2 = mesh->GetPoint(i, 1);
    p3 = mesh->GetPoint(i, 2);

    m1.PutValue(0,0,p1->X()); m1.PutValue(0,1,p1->Y()); m1.PutValue(0,2,p1->Z()); m1.PutValue(0,3,1);
    m2.PutValue(0,0,p2->X()); m2.PutValue(0,1,p2->Y()); m2.PutValue(0,2,p2->Z()); m2.PutValue(0,3,1);
    m3.PutValue(0,0,p3->X()); m3.PutValue(0,1,p3->Y()); m3.PutValue(0,2,p3->Z()); m3.PutValue(0,3,1);

    Matrix::Multiply(&m1, projMat, outMatP1);
    Matrix::Multiply(&m2, projMat, outMatP2);
    Matrix::Multiply(&m3, projMat, outMatP3);

    Logger::Log(Logger::FontColor::PINK, "============MULTIPLING:");
    Logger::Log("After multiply matp1 %s", outMatP1.ToString().c_str());
    Logger::Log("After multiply matp2 %s", outMatP2.ToString().c_str());
    Logger::Log("After multiply matp3 %s", outMatP3.ToString().c_str());

    z1 = outMatP1.GetValue(0,3); if(z1 <= 0) {z1 = 1;};
    z2 = outMatP2.GetValue(0,3); if(z2 <= 0) {z2 = 1;};
    z3 = outMatP3.GetValue(0,3); if(z3 <= 0) {z3 = 1;};
    projectedP1.SetX(outMatP1.GetValue(0,0) / z1); projectedP1.SetY(outMatP1.GetValue(0,1) / z1); projectedP1.SetZ(outMatP1.GetValue(0,2) / z1);
    projectedP2.SetX(outMatP2.GetValue(0,0) / z2); projectedP2.SetY(outMatP2.GetValue(0,1) / z2); projectedP2.SetZ(outMatP2.GetValue(0,2) / z2);
    projectedP3.SetX(outMatP3.GetValue(0,0) / z3); projectedP3.SetY(outMatP3.GetValue(0,1) / z3); projectedP3.SetZ(outMatP3.GetValue(0,2) / z3);

    Logger::Log(Logger::FontColor::PINK, "============DIVISON(z1=%lf z2=%lf z3=%lf):", z1, z2, z3);
    Logger::Log("After z division projectedP1 %s", projectedP1.ToString().c_str());
    Logger::Log("After z division projectedP2 %s", projectedP2.ToString().c_str());
    Logger::Log("After z division projectedP3 %s", projectedP3.ToString().c_str());

    projectedP1.SetX((projectedP1.X() + 1.0) * 0.5 * Width()); projectedP1.SetY((projectedP1.Y() + 1.0) * 0.5 * Height());
    projectedP2.SetX((projectedP2.X() + 1.0) * 0.5 * Width()); projectedP2.SetY((projectedP2.Y() + 1.0) * 0.5 * Height());
    projectedP3.SetX((projectedP3.X() + 1.0) * 0.5 * Width()); projectedP3.SetY((projectedP3.Y() + 1.0) * 0.5 * Height());

    Logger::Log(Logger::FontColor::PINK, "============SCALING(+1.0  *0.5  w=*%d h=*%d):", Width(), Height());
    Logger::Log("After scaling projectedP1 %s", projectedP1.ToString().c_str());
    Logger::Log("After scaling projectedP2 %s", projectedP2.ToString().c_str());
    Logger::Log("After scaling projectedP3 %s", projectedP3.ToString().c_str());

    Triangle projTri(&projectedP1, &projectedP2, &projectedP3);

    DrawTri(&projTri);
    Logger::Log(Logger::FontColor::PINK, "======================================");
  }
}

inline Matrix* Renderer::GetProjectionMatrix() { return projMatrix; }

void Renderer::RecalculateProjectionMatrix(Camera* cam) {
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
}


#endif /* _DRAWER_HPP_ */
