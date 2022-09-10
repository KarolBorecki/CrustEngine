#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <vector>
#include <string>

#include <Core/Camera.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Rendering/Objects/Object.hpp>

class Scene {
public:
  Scene(std::string _name, Camera* _mainCamera);
  virtual ~Scene() = default;

  void AddObject(Object obj);
  std::vector<RenderObject*> GetObjectsToRender();

  std::string GetName();

private:
  std::string name;
  Camera* mainCamera { nullptr };

  std::vector<Object> objects;
  std::vector<RenderObject*> renderObjects;
};

inline Scene::Scene(std::string _name, Camera* _mainCamera) : name(_name), mainCamera(_mainCamera) {}

inline void Scene::AddObject(Object obj) {
  objects.push_back(obj);
  RenderObject* renderObj = static_cast<RenderObject*>(&obj);
  if(renderObj != nullptr)
    renderObjects.push_back(renderObj);
}

inline std::vector<RenderObject*> Scene::GetObjectsToRender() { return renderObjects; }

inline std::string Scene::GetName() { return name; }

#endif /* _SCENE_HPP_ */
