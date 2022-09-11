#ifndef _DRAWER_HPP_
#define _DRAWER_HPP_

#include <Rendering/RendererWrapper.hpp>
#include <Rendering/Objects/RenderObject.hpp>

class Renderer : public RendererWrapper{
public:
  Renderer(int _width, int _height) : RendererWrapper(_width, _height) {}
  virtual ~Renderer() = default;

  void DrawTri();
  void DrawMesh(Mesh* mesh);

private:
};

void Renderer::DrawTri() {
  SetDrawColor(RendererWrapper::RendererColor::RED);

  DrawLine(320, 200, 300, 240);
  DrawLine(300, 240, 340, 240);
  DrawLine(340, 240, 320, 200);
}


#endif /* _DRAWER_HPP_ */
