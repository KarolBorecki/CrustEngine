#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <Core/Camera.hpp>

class Scene {
public:
  Scene(Camera* _mainCamera);
  virtual ~Scene() = default;

private:
  Camera* mainCamera { nullptr };
};

inline Scene::Scene(Camera* _mainCamera) : mainCamera(_mainCamera) {}

#endif /* _SCENE_HPP_ */
