#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include <Physics/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>
#include <Rendering/Objects/RenderObject.hpp>

class Renderer : public RendererWrapper{
public:
  Renderer(int _width, int _height);
  ~Renderer();

  void DrawTri();
  void DrawMesh(Mesh* mesh);

  Matrix* GetProjectionMatrix();

  void RecalculateProjectionMatrix(Camera* cam);

  static constexpr int PROJ_MATRIX_SIZE { 4 }; /* It will always be like this */

private:
  double aspectRatio { 0.0 };
  Matrix* projMatrix { nullptr };
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
