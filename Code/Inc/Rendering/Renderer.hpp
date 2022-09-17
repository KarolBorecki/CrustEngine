#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include <Physics/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>
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

  void DrawTri();
  /**
  * @brief Draws given mesh on the screen
  *
  * @details Class held by RenderWindow.hpp for drawing purposes.
  * It is able to render all shapes that is needed to show mesh on the flat screen.
  */
  void DrawMesh(Mesh* mesh);

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
  Matrix* projMatrix { nullptr }; //!< Projection matrix. See Renderer::RecalculateProjectionMatrix.
};

Renderer::Renderer(int _width, int _height) : RendererWrapper(_width, _height) {
  aspectRatio = _height / _width;
  projMatrix = new Matrix(PROJ_MATRIX_SIZE, PROJ_MATRIX_SIZE);
}

Renderer::~Renderer() {
  if (projMatrix == nullptr) return;
  delete projMatrix;
}

void Renderer::DrawTri() {
  SetDrawColor(RendererWrapper::RendererColor::RED);

  DrawLine(320, 200, 300, 240);
  DrawLine(300, 240, 340, 240);
  DrawLine(340, 240, 320, 200);
}

void Renderer::DrawMesh(Mesh* mesh) {
  if(mesh== NULL) Logger::Info("MESH NULL");
  Matrix* m = &(mesh->triangles[0].point[0]);

  if(m == NULL) Logger::Info("M NULL");
  Logger::Log("M ROWS: %d", m->Rows());
  Logger::Log("2");
  Matrix* m2 = GetProjectionMatrix();
  Logger::Log(m2->ToString().c_str());

  Matrix result = Matrix::Multiply(m, m2);
  Logger::Log(result.ToString().c_str());
}

inline Matrix* Renderer::GetProjectionMatrix() { return projMatrix; }

void Renderer::RecalculateProjectionMatrix(Camera* cam) {
  projMatrix->PutValue(0, 0, aspectRatio / cam->GetFFovRad());
  projMatrix->PutValue(0, 1, 0.0);
  projMatrix->PutValue(0, 2, 0.0);
  projMatrix->PutValue(0, 3, 0.0);

  projMatrix->PutValue(1, 0, 0.0);
  projMatrix->PutValue(1, 1, cam->GetFFovRad());
  projMatrix->PutValue(1, 2, 0.0);
  projMatrix->PutValue(1, 3, 0.0);

  projMatrix->PutValue(2, 0, 0.0);
  projMatrix->PutValue(2, 1, 0.0);
  projMatrix->PutValue(2, 2, cam->GetFFar() / (cam->GetFFar() - cam->GetFNear()));
  projMatrix->PutValue(2, 3, 1.0);

  projMatrix->PutValue(3, 0, 0.0);
  projMatrix->PutValue(3, 1, 0.0);
  projMatrix->PutValue(3, 2, -(cam->GetFFar() * cam->GetFNear()) / (cam->GetFFar() - cam->GetFNear()));
  projMatrix->PutValue(3, 3, 0.0);
  Logger::Warning(projMatrix->ToString().c_str());
}


#endif /* _DRAWER_HPP_ */
