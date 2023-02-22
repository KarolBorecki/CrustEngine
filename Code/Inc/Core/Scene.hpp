#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>
#include <string>

#include <Core/Camera.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Rendering/Objects/LightSource.hpp>
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
class Scene {
public:
  /**
  * @param _name Scene name, used as RenderWindow's window caption.
  * @param _mainCamera Main camera handler.
  */
  Scene(std::string _name, Camera* _mainCamera);
  ~Scene() {};

  void Start();

  void Update(double deltaTime);

  /**
  * @brief Getter for #mainCamera field.
  *
  * @return Pointer to #mainCamera.
  *
  * @sa Camera.hpp
  */
  Camera* GetMainCamera();

  /**
  * @brief Adds the object to the scene.
  *
  * @details Adds the object to the #objects array and if is type of RenderObject or LightSource adds it's handler to #renderObjects or #lightSources array.
  *
  * @param obj Added object.
  *
  * @sa Object.hpp RenderObject.hpp LightSource.hpp
  */
  void AddObject(Object* obj);
  /**
  * @brief Getter for #renderObjects field.
  *
  * @return #renderObjects field.
  *
  * @sa RenderObject.hpp
  */
  std::vector<RenderObject*> GetObjectsToRender();

  /**
  * @brief Getter for #lightSources field.
  *
  * @return #lightSources field.
  *
  * @sa LightSource.hpp
  */
  std::vector<LightSource*> GetLightSources();

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
  std::string name; //!< Scene name, also used as window caption.
  Camera* mainCamera { nullptr }; //!< Main camera from which perspective the projection will be calculated.

  bool projectLight { true }; //!< If true the light will be projected accordingly to light sources, if false all mesh's faces will be projected with maximum lighting.

  std::vector<Object*> objects; //!< Objects present on the scene.
  std::vector<RenderObject*> renderObjects; //!< Renderable objects present on the scene. This array is sub-array of objects.
  std::vector<LightSource*> lightSources; //!< Light sources in the scene. This array is sub-array of objects.
};

inline Scene::Scene(std::string _name, Camera* _mainCamera) : name(_name), mainCamera(_mainCamera) {Logger::Log("============Creating Scene============");Logger::Log("============Creating Scene DONE============");}

void Scene::Start() {
  for(auto obj : objects)
    for(auto script : obj->GetScripts())
      script->Start();
}

void Scene::Update(double deltaTime) {
  for(auto obj : objects)
    for(auto script : obj->GetScripts())
      script->Update(deltaTime);
}

inline Camera* Scene::GetMainCamera() { return mainCamera; }

void Scene::AddObject(Object* obj) {
  Logger::Info("Adding object<%d>", obj->GetID());
  objects.push_back(obj);

  RenderObject* renderObj = dynamic_cast<RenderObject*>(obj);
  if(renderObj != nullptr) {
    Logger::Log("Obj<%d> is renderable!", obj->GetID());
    renderObjects.push_back(renderObj);
  }

  LightSource* lightSource = dynamic_cast<LightSource*>(obj);
  if(lightSource != nullptr) {
    Logger::Log("Obj<%d> is light!", obj->GetID());
    lightSources.push_back(lightSource);
  }
}

inline std::vector<RenderObject*> Scene::GetObjectsToRender() { return renderObjects; }

inline std::vector<LightSource*> Scene::GetLightSources() { return lightSources; }

inline bool Scene::IsLightProjected() { return projectLight; }

inline void Scene::SetLightProjection(bool project) { projectLight = project; }

inline std::string Scene::GetName() { return name; }

#endif /* _SCENE_HPP_ */
