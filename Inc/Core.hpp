#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <Scene.hpp>
#include <Logger.hpp>
#include <Rendering/RendererWrapper.hpp>

class Core {
public:
  static void Run(int width, int height);

  static void LoadScene(Scene* scene);

private:
  static inline Scene* loadedScene { nullptr };
};

inline void Core::Run(int width, int height) {
  RendererWrapper drawer(width, height);
  if(drawer.Init() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be initialized!");
    return;
  }
  if(drawer.CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be created!");
    return;
  }
  while(drawer.IsRunning()) {
    drawer.SetDrawColor(0,0,0);
    drawer.Clean();

    drawer.SetDrawColor(RendererWrapper::RendererColor::RED);

    drawer.DrawLine(320, 200, 300, 240);
    drawer.DrawLine(300, 240, 340, 240);
    drawer.DrawLine(340, 240, 320, 200);

    drawer.Show();
    drawer.GetEvent();
  }

  drawer.Quit();
}

#endif /* _CORE_HPP_ */
