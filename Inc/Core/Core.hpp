#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>

//#include <Core/Scene.hpp> //TODO: No need for complete type
#include <Rendering/RenderWindow.hpp>

class Scene;

class Core {
public:
  void OpenNewWindow(int width, int height, Scene* scene);

private:
  std::vector<RenderWindow*> openedWindows;
};

inline void Core::OpenNewWindow(int width, int height, Scene* scene) {
  RenderWindow window(width, height, scene);

  window.Start(); // TODO: run on new thread

  //openedWindows.push_back(&window);
}

#endif /* _CORE_HPP_ */
