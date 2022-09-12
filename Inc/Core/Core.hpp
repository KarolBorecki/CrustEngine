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

void Core::OpenNewWindow(int width, int height, Scene* scene) {
  RenderWindow* window = new RenderWindow(width, height, scene);
  Logger::Log("Staring the window...");
  window->Start(); // TODO: run on new thread
  Logger::Error("After window started!");
  openedWindows.push_back(window);
}

void Core::CloseWindow(RenderWindow* window) {
  window->Close();
  remove(openedWindows.begin(), openedWindows.end(), window);
  delete window;
}

void Core::CloseAllWindows() {
  for (auto &window : openedWindows){
    window->Close();
    delete window;
  }
  openedWindows.clear();
}

void Core::Quit() {
  CloseAllWindows();
}

#endif /* _CORE_HPP_ */
