#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include <Math/Matrix.hpp>

#include <Core/Camera.hpp>

#include <Rendering/RendererWrapper.hpp>

#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>
#include <Math/Triangle.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Rendering/Projector.hpp>

#include <algorithm>

/**
 * @brief Class used to render simple shapes on the window.
 *
 * @details Class held by RenderWindow.hpp for drawing purposes.
 * It is able to render all shapes that is needed to show mesh on the flat screen.
 * It is able to render renderable objects on the screen with given lightning. Refer to #RenderWindow class for more information as this class itself is more low level.
 *
 * @sa RenderWindow.hpp
 */
class Renderer : public RendererWrapper
{
public:
  /**
   * @details Creates new object of type Renderer allocates Matrix for #projMatrix field.
   * @details Constructor does not initalize new Renderer properly. In order to init a renderer You need to call #Init and #CreateWindow methods.
   * Also remember to load new scene so that renderer has something to render.
   *
   * @param _width Width of the window that this Renderer is applied to.
   * @param _height Height of the window that this Renderer is applied to.
   */
  Renderer(uint32_t _width, uint32_t _height);

  ~Renderer();

  /**
   * @brief Draws given mesh on the screen
   *
   * @details Class held by RenderWindow.hpp for drawing purposes.
   * It is able to render all shapes that is needed to show mesh on the flat screen.
   * It also considers lightning and object's postion (In future also rotation).
   *
   * @param mesh Mesh that will be drawn.
   * @param pos Position in 3D space at which the mesh will be drawn.
   * @param rot Rotation in 3D space at which the mesh will be drawn.
   * @param cam Camera, from which perspective the mesh will be projected.
   * @param lightDir lightning direction on the scene. Right now Crust engine only supports 1 directional light on the scene //TODO
   * @param projectLight Flag if the light should be proojected.
   *
   * @sa Mesh.hpp
   */
  void RenderMesh(RenderObject &object, Scene &scene);

private:
  Projector &projector;
};

Renderer::Renderer(uint32_t _width, uint32_t _height) : RendererWrapper(_width, _height), projector(*(new Projector(_width, _height)))
{
}

Renderer::~Renderer()
{
  delete &projector;
}

void Renderer::RenderMesh(RenderObject &object, Scene &scene)
{
  SetDrawColor(RendererWrapper::RendererColor::WHITE);
  projector.RecalculateProjectionMatrix(scene.GetMainCamera());

  static Projector::ProjectionData tmpProjection;
  static std::vector<Projector::ProjectionData> projections;
  for (int i = 0; i < object.GetMesh().GetPolygonsCount(); i++) // TODO use auto for
  {
    tmpProjection = projector.ProjectPolygon(object.GetMesh().GetPolygon(i), object.GetTransform(), scene.GetMainCamera(), scene.GetLightSources()[0]->GetTransform().GetEulerRotation());
    if (tmpProjection.renderable)
      projections.push_back(tmpProjection);
  }

  sort(projections.begin(), projections.end(), [](const Projector::ProjectionData &a, const Projector::ProjectionData &b)
       { 
        /* https://en.wikipedia.org/wiki/Painter%27s_algorithm */
        double za = (a.z1 + a.z2 + a.z3) / 3;
        double zb = (b.z1 + b.z2 + b.z3) / 3;
        return za > zb; });

  for (auto &w : projections)
  {
    DrawFilledTri(w.x1, w.y1, w.x2, w.y2, w.x3, w.y3, w.light);
  }
  projections.clear();
}

#endif /* _RENDERER_HPP_ */
