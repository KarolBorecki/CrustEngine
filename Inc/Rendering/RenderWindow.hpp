#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Core/Scene.hpp>
#include <Rendering/Renderer.hpp>
#include <Rendering/Objects/RenderObject.hpp>

class RenderWindow {
public:
  RenderWindow(int _width, int _height, Scene* _scene);
  virtual ~RenderWindow() = default; /* todo clean queue? */

  void Start();
  void Close();

  void LoadScene(Scene* scene);

  void AddObjectToRenderStack(RenderObject* obj);

private:
  int width { 0 };
  int height { 0 };
  double aspectRation { 0.0 };
  Renderer* renderer { nullptr };
  Scene* loadedScene { nullptr };

  std::queue<RenderObject*> renderingStack;

  void Clean();
};

inline RenderWindow::RenderWindow(int _width, int _height, Scene* _scene) {
  width = _width;
  height = _height;
  aspectRation = height / width;

  renderer = new Renderer(_width, _height);

  if(renderer->Init() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be initialized!");
    //TODO quit
  }
  if(renderer->CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be created!");
    //TODO quit
  }

  LoadScene(_scene);
}

inline void RenderWindow::Start() {
  while(renderer->IsRunning()) {
    Clean();

    renderer->DrawTri();
    for (auto obj : loadedScene->GetObjectsToRender()) {
      Vector3 point0 = obj->GetMesh()->triangles.begin()->point[0];
      Vector3 point1 = obj->GetMesh()->triangles.begin()->point[1];
      Vector3 point2 = obj->GetMesh()->triangles.begin()->point[2];
      Logger::Info("Rendering trangle:\n   %.1f %.1f %.1f \n   %.1f %.1f %.1f \n   %.1f %.1f %.1f", point0.x, point0.y, point0.z, point1.x, point1.y, point1.z, point2.x, point2.y, point2.z);

      //for (auto tri : obj->GetMesh()->triangles)
    }

    renderer->Show();
    renderer->GetEvent();
  }
  renderer->Quit();
}

inline void RenderWindow::Close() {
  renderer->StopRunning();
  delete renderer;
}

inline void RenderWindow::LoadScene(Scene* scene) {
  loadedScene = scene;
  renderer->SetWindowTitle(scene->GetName());
}

inline void RenderWindow::AddObjectToRenderStack(RenderObject* obj) {
  renderingStack.push(obj);
}

inline void RenderWindow::Clean() {
  renderer->SetDrawColor(0,0,0);
  renderer->Clean();
}


#endif /* _RENDERWINDOW_HPP_ */
