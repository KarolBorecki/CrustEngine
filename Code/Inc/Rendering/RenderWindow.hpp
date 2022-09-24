#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Core/Scene.hpp>
#include <Rendering/Renderer.hpp>
#include <Rendering/Objects/RenderObject.hpp>

/**
* @brief Class responsible to open window, load scene, manage renderer thread and pass render objects to rendering.
*/
class RenderWindow {
public:
  /**
  * @brief Creates new window and loads given scene.
  *
  * @details Creates new Renderer object and tries to call RendererWrapper::Init and RendererWrapper::CreateWindow methods.
  * if fails logs and error using Logger::Error. If nor error occured loads given scene.
  *
  * @param _width New window width.
  * @param _height New window height.
  * @param scene Scene to load as first.
  */
  RenderWindow(int _width, int _height, Scene* _scene);
  /**
  * @details If renderer is not nullptr deletes it.
  */
  ~RenderWindow();

  /**
  * @brief Starts the window rendering process.
  */
  void Start();
  /**
  * @brief Stops the window rendering process.
  */
  void Close();

  /**
  * @brief Loads scene.
  *
  * @param scene Handler to scene handler, which will be loaded.
  */
  void LoadScene(Scene* scene);

private:
  int width { 0 }; //!< Width of this window.
  int height { 0 }; //!< Height of this window.
  Renderer* renderer { nullptr }; //!< Widnows's renderer handler.
  Scene* loadedScene { nullptr }; //!< Loaded scene's handler.

  /**
  * @brief Cleans everything that was drawn on the window.
  */
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
  if(renderer == nullptr) return;
  delete renderer;
}

void RenderWindow::Start() {
  Logger::Info("==================Starting drawing process==================");
  while(renderer->IsRunning()) {
    Clean();
    std::vector<RenderObject*> objs = loadedScene->GetObjectsToRender();
    for (auto obj : objs) {
      renderer->DrawMesh(obj->GetMesh());
    }
    // renderer->SetDrawColor(0, 255, 0);
    // Vector3 p1(100.0, 100.0, 0.0);
    // Vector3 p2(300.0, 100.0, 0.0);
    // Vector3 p3(300.0, 300.0, 0.0);
    // Triangle tri(&p1, &p2, &p3);
    // renderer->DrawTri(&tri);
    //
    // renderer->SetDrawColor(255, 0, 0);
    // renderer->DrawTri(0.0, 0.0, 0.0, 200.0, 200.0, 200.0);

    renderer->Show();
    renderer->GetEvent();
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

void RenderWindow::Clean() {
  renderer->SetDrawColor(0,0,0);
  renderer->Clean();
}


#endif /* _RENDERWINDOW_HPP_ */
