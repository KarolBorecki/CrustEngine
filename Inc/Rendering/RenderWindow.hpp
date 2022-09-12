#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Core/Scene.hpp>
#include <Rendering/Renderer.hpp>
#include <Rendering/Objects/RenderObject.hpp>

class RenderWindow {
public:
  RenderWindow(int _width, int _height, Scene* _scene);
  virtual ~RenderWindow(); /* todo clean queue? */

  void Start();
  void Close();

  void LoadScene(Scene* scene);

  void AddObjectToRenderStack(RenderObject* obj);

private:
  int width { 0 };
  int height { 0 };
  Renderer* renderer { nullptr };
  Scene* loadedScene { nullptr };

  std::queue<RenderObject*> renderingStack;

  void Clean();
};

RenderWindow::RenderWindow(int _width, int _height, Scene* _scene) {
  width = _width;
  height = _height;

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

RenderWindow::~RenderWindow() {
  if (renderer == nullptr) return;
  delete renderer;
}

void RenderWindow::Start() {
  while(renderer->IsRunning()) {
    Clean();

    renderer->DrawTri();

    Logger::Log("Getting render objects...");
    std::vector<RenderObject*> objs = loadedScene->GetObjectsToRender();
    Logger::Log("Render objects got!");
    for (auto obj : objs) {
      Logger::Error("Getting point 0...");
      Vector3 point0 = obj->GetMesh()->triangles.begin()->point[0];
      Logger::Info("Point 0 got!");
      Logger::Error("Getting point 1...");
      Vector3 point1 = obj->GetMesh()->triangles.begin()->point[1];
      Logger::Info("Point 1 got!");
      Logger::Error("Getting point 2...");
      Vector3 point2 = obj->GetMesh()->triangles.begin()->point[2];
      Logger::Info("Point 2 got!");
      //Logger::Info("Rendering trangle:\n   %.1f %.1f %.1f \n   %.1f %.1f %.1f \n   %.1f %.1f %.1f", point0.X(), point0.Y(), point0.Z(), point1.X(), point1.Y(), point1.Z(), point2.X(), point2.Y(), point2.Z());

      //for (auto tri : obj->GetMesh()->triangles)
    }
    Logger::Warning("Showing...");
    renderer->Show();
    Logger::Info("Shown!");
    Logger::Warning("Getting event...");
    renderer->GetEvent();
    Logger::Info("Event got!");
  }
  renderer->Quit();
}

void RenderWindow::Close() {
  renderer->StopRunning();
}

void RenderWindow::LoadScene(Scene* scene) {
  loadedScene = scene;
  renderer->SetWindowTitle(scene->GetName());
  renderer->RecalculateProjectionMatrix(scene->GetMainCamera());
}

void RenderWindow::AddObjectToRenderStack(RenderObject* obj) {
  renderingStack.push(obj);
}

void RenderWindow::Clean() {
  renderer->SetDrawColor(0,0,0);
  renderer->Clean();
}


#endif /* _RENDERWINDOW_HPP_ */
