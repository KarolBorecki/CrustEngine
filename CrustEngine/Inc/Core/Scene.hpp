#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>
#include <string>

#include <Core/Camera.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Rendering/Objects/Lightining/LightSource.hpp>
#include <Rendering/Objects/Object.hpp>

#include <Scripting/CrustScript.hpp>

/* For now only objects can be added/changed, camera must stay the same! */
/**
 * @brief Class holding objects rendered on window and camera, from which the projection will be calculated.
 *
 * @details This class is passed to render window as the information what to render and how to render.
 * The RenderWindow loads scene and calcuates the projection matrix based on #mainCamera values.
 * At each frame RenderWindow goes through renderObjects and draws it.
 *
 * @sa RenderWindow.hpp Camera.hpp Object.hpp
 */
class Scene
{
public:
  /**
   * @param _name Scene name, used as RenderWindow's window caption.
   * @param _mainCamera Main camera handler.
   */
  Scene(std::string _name, Camera &_mainCamera);
  ~Scene(){};

  /**
   * @brief Loads the scene. Performs cleanup and gets the scene ready for rendering. Should be called on load from render window (It is done by render window).
   */
  void OnLoad();

  /**
   * @brief Unloads the scene. Performs cleanup and gets the scene ready for new load. Should be called after the scene was unlaoded from render window (It is done by render window).
   *
   */
  void OnUnLoad();

  /**
   * @brief Starts the scene. Loads all scripts, calls Start on it and performs cleanup. Should be called before rendering of this scene happens (It is done by render window).
   */
  void Start();

  /**
   * @brief Updates the scene. Calls update for each script. Should be called once per frame (It is done by render window).
   *
   * @param deltaTime Time that passed since last frame was rendered.
   */
  void Update(double deltaTime);

  /**
   * @brief Getter for #mainCamera field.
   *
   * @return Pointer to #mainCamera.
   *
   * @sa Camera.hpp
   */
  Camera &GetMainCamera();

  /**
   * @brief Setter for #mainCamera field.
   *
   * @return Reference to camera, which will be new main camera (From it's perspective the world will be rendered).
   *
   * @sa Camera.hpp
   */
  void SetMainCamera(Camera &newMainCamera);

  /**
   * @brief Adds the object to the scene.
   *
   * @details Adds the object to the #objects array and if is type of RenderObject or LightSource adds it's handler to #renderObjects or #lightSources array.
   *
   * @param obj Added object.
   *
   * @sa Object.hpp RenderObject.hpp LightSource.hpp
   */
  void AddObject(Object &obj);
  /**
   * @brief Getter for #renderObjects field.
   *
   * @return #renderObjects field.
   *
   * @sa RenderObject.hpp
   */
  std::vector<RenderObject *> GetObjectsToRender();

  /**
   * @brief Getter for #lightSources field.
   *
   * @return #lightSources field.
   *
   * @sa LightSource.hpp
   */
  std::vector<LightSource *> GetLightSources();

  /**
   * @brief Getter for #projectLight field.
   *
   * @return #lightSources field, which represents if the lightning is done accordingly to light sources on the scene or set to maximum on each face.
   */
  bool IsLightProjected();

  /**
   * @brief Sets if the light should be projected.
   */
  void SetLightProjection(bool project);

  /**
   * @brief Getter for #name field.
   *
   * @return #name field.
   */
  std::string GetName();

private:
  std::string _name;            //!< Scene name, also used as window caption on top of the renderer window.
  bool _started{false};         //!< Flag that says if given scene already started - was loaded or performed Start on every script in this scene.
  bool _loaded{false};          //!< Flag that says if given scene is currently loaded on any render window.
  Camera *p_mainCamera{nullptr}; //!< Main camera from which perspective the projection will be calculated.

  bool _projectLight{true}; //!< If true the light will be projected accordingly to light sources, if false all mesh's faces will be projected with maximum lighting.

  std::vector<Object *> _objects;             //!< Objects present on the scene.
  std::vector<RenderObject *> _renderObjects; //!< Renderable objects present on the scene. This array is sub-array of objects.
  std::vector<LightSource *> _lightSources;   //!< Light sources in the scene. This array is sub-array of objects.
};

inline Scene::Scene(std::string name, Camera &mainCamera) : _name(name), p_mainCamera(&mainCamera)
{
  AddObject(*p_mainCamera);
}

void Scene::OnLoad()
{
  _loaded = true;
  Start();
}

void Scene::OnUnLoad()
{
  _loaded = false;
  _started = false;
}

void Scene::Start()
{
  if (_started)
    return;

  for (auto obj : _objects)
    for (auto script : obj->GetScripts())
      script->Start();

  _started = true;
}

void Scene::Update(double deltaTime)
{
  for (auto obj : _objects)
  {
    for (auto script : obj->GetScripts())
    {
      if (script == nullptr)
        continue;
      script->Update(deltaTime);
    }
  }
}

inline Camera &Scene::GetMainCamera() { return *p_mainCamera; }

inline void Scene::SetMainCamera(Camera &newMainCamera) { p_mainCamera = &newMainCamera; }

void Scene::AddObject(Object &obj)
{
  _objects.push_back(&obj);

  RenderObject *renderObj = dynamic_cast<RenderObject *>(&obj);
  if (renderObj != nullptr)
  {
    _renderObjects.push_back(renderObj);
  }

  LightSource *lightSource = dynamic_cast<LightSource *>(&obj);
  if (lightSource != nullptr)
  {
    _lightSources.push_back(lightSource);
  }
}

inline std::vector<RenderObject *> Scene::GetObjectsToRender() { return _renderObjects; }

inline std::vector<LightSource *> Scene::GetLightSources() { return _lightSources; } // TODO maybe return just 1 light source by reference?

inline bool Scene::IsLightProjected() { return _projectLight; }

inline void Scene::SetLightProjection(bool project) { _projectLight = project; }

inline std::string Scene::GetName() { return _name; }

#endif /* _SCENE_HPP_ */
