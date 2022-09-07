#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Core/Scene.hpp>

#include <Rendering/Renderer.hpp>
#include <Rendering/RenderObject.hpp>

class RenderWindow {
public:
  RenderWindow(int _width, int _height, Scene* _scene);
  virtual ~RenderWindow() = default; /* todo clean queue? */

  void Start();
  void Close();

  void AddObjectToRenderStack(RenderObject* obj);

private:
  Renderer* renderer { nullptr };
  Scene* loadedScene { nullptr };

  std::queue<RenderObject*> renderingStack;

  void Clean();
};

inline RenderWindow::RenderWindow(int _width, int _height, Scene* _scene) {
  Renderer rendererTemp(_width, _height);
  renderer = new Renderer(_width, _height);

  if(renderer->Init() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be initialized!");
    //TODO quit
  }
  if(renderer->CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be created!");
    //TODO quit
  }

  loadedScene = _scene;
}

inline void RenderWindow::Start() {
  while(renderer->IsRunning()) {
    Clean();

    renderer->DrawTri();

    renderer->Show();
    renderer->GetEvent();
  }
  renderer->Quit();
}

inline void RenderWindow::Close() {
  renderer->StopRunning();
  delete renderer;
}

inline void RenderWindow::AddObjectToRenderStack(RenderObject* obj) {
  renderingStack.push(obj);
}

inline void RenderWindow::Clean() {
  renderer->SetDrawColor(0,0,0);
  renderer->Clean();
}


#endif /* _RENDERWINDOW_HPP_ */
