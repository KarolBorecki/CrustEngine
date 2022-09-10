#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>

#include <Core/Scene.hpp>
#include <Rendering/RenderWindow.hpp>

class Core {
public:
  void OpenNewWindow(int width, int height, Scene* scene);

  void CloseWindow(RenderWindow* window);
  void CloseAllWindows();
  void Quit();

private:
  std::vector<RenderWindow*> openedWindows;
};

inline void Core::OpenNewWindow(int width, int height, Scene* scene) {
  RenderWindow* window = new RenderWindow(width, height, scene);

  window->Start(); // TODO: run on new thread

  openedWindows.push_back(window);
}

inline void Core::CloseWindow(RenderWindow* window) {
  window->Close();
  remove(openedWindows.begin(), openedWindows.end(), window);
  delete window;
}

inline void Core::CloseAllWindows() {
  for (auto &window : openedWindows){
    window->Close();
    delete window;
  }
  openedWindows.clear();
}

inline void Core::Quit() {
  CloseAllWindows();
}

#endif /* _CORE_HPP_ */
