#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>
#include <string>

#include <Core/Camera.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Rendering/Objects/Object.hpp>

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
  * @details Adds the object to the #objects array and if is type of RenderObject adds it's handler to renderObjects array.
  *
  * @param obj Added object.
  *
  * @sa Object.hpp RenderObject.hpp
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
  * @brief Getter for #name field.
  *
  * @return #name field.
  */
  std::string GetName();

private:
  std::string name; //!< Scene name, also used as window caption.
  Camera* mainCamera { nullptr }; //!< Main camera from which perspective the projection will be calculated.

  std::vector<Object*> objects; //!< Objects present on the scene.
  std::vector<RenderObject*> renderObjects; //!< Renderable objects present on the scene. This array is sub-array of objects.
};

inline Scene::Scene(std::string _name, Camera* _mainCamera) : name(_name), mainCamera(_mainCamera) {Logger::Log("============Creating Scene============");Logger::Log("============Creating Scene DONE============");}

inline Camera* Scene::GetMainCamera() { return mainCamera; }

void Scene::AddObject(Object* obj) {
  objects.push_back(obj);
  RenderObject* renderObj = static_cast<RenderObject*>(obj);
  if(renderObj != nullptr)
    renderObjects.push_back(renderObj);
}

inline std::vector<RenderObject*> Scene::GetObjectsToRender() { return renderObjects; }

inline std::string Scene::GetName() { return name; }

#endif /* _SCENE_HPP_ */
