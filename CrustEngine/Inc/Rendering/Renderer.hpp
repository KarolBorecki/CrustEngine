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
   * @brief Renders given scene on the screen of this renderer.
   *
   * @param scene Scene to render.
   */
  void RenderScene(Scene &scene);

  void RenderObjectOntoScene(RenderObject &object, Scene &scene);

  /**
   * @brief Draws given mesh on the screen //TODO fix doc
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
  void RenderMeshWithTranslation(Mesh &mesh, Matrix<float> &translationMatrix);

private:
  Projector &r_projector;
};

Renderer::Renderer(uint32_t _width, uint32_t _height) : RendererWrapper(_width, _height), r_projector(*(new Projector(_width, _height)))
{
}

Renderer::~Renderer()
{
  delete &r_projector;
}

void Renderer::RenderScene(Scene &scene)
{
  SetDrawColor(RendererWrapper::RendererColor::WHITE);
  r_projector.RecalculateProjectionMatrix(scene.GetMainCamera());
  r_projector.RecalculateLightning(*scene.GetLightSources()[0], scene.IsLightProjected());
  for (auto &object : scene.GetObjectsToRender())
  {
    RenderObjectOntoScene(*object, scene);
  }
}

void Renderer::RenderObjectOntoScene(RenderObject &object, Scene &scene)
{
  if (object.IsActive())
  {
    static Matrix<float> translationMatrix;
    translationMatrix = r_projector.CalculateTranslationMatrix(object.GetTransform()); // Skok rzędu ~10FPS
    RenderMeshWithTranslation(object.GetMesh(), translationMatrix);
  }
}

void Renderer::RenderMeshWithTranslation(Mesh &mesh, Matrix<float> &translationMatrix)
{
  static Projector::ProjectionData tmpProjection;
  static std::vector<Projector::ProjectionData> projections;
  for (int i = 0; i < mesh.GetPolygonsCount(); i++)
  {
    tmpProjection = r_projector.ProjectPolygon(mesh.GetPolygon(i), translationMatrix);
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
    // #define LOG_RENDERER
#ifdef LOG_RENDERER
    Logger::Log("Drawing at: (%f, %f) (%f, %f) (%f, %f) [%d]", w.x1, w.y1, w.x2, w.y2, w.x3, w.y3, scene.IsLightProjected() ? w.light : 255);
#endif
    DrawFilledTri(w.x1, w.y1, w.x2, w.y2, w.x3, w.y3, w.light);
  }
  projections.clear();
}

#endif /* _RENDERER_HPP_ */
