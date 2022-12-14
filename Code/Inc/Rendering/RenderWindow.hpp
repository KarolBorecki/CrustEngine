#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Utils/TimeProvider.hpp>

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

  TimeProvider* timeProvider;

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
    throw std::runtime_error("RenderWindow failed to initzialize");
  }
  if(renderer->CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK) {
    Logger::Error("Drawer could not be created!");
    throw std::runtime_error("RenderWindow failed to initzialize");
  }

  LoadScene(_scene);

  timeProvider = new TimeProvider();
}

RenderWindow::~RenderWindow() {
  delete renderer;
  delete timeProvider;
}

void RenderWindow::Start() {
  Logger::Info("==================Starting drawing process==================");
  // double moveSpeedX = 1;
  // double moveSpeedY = 2;
  // double moveSpeedZ = 0.5;
  //
  // int moveDirX = 1;
  // int moveDirY = 1;
  // int moveDirZ = 1;
  //
  // int maxPos = 2;

  loadedScene->Start();

  while(renderer->IsRunning()) {
    timeProvider->OnFrameStart();

    Clean();
    std::vector<RenderObject*> objs = loadedScene->GetObjectsToRender();
    for (auto obj : objs) {
      renderer->DrawMesh(obj->GetMesh(), obj->GetPosition(), loadedScene->GetMainCamera(), loadedScene->GetLightSources().at(0)->GetDirection());

      // if(moveDirX > 0 && obj->GetPosition()->X() >= maxPos) moveDirX = -1;
      // if(moveDirX < 0 && obj->GetPosition()->X() <= -maxPos) moveDirX = 1;
      //
      // if(moveDirY > 0 && obj->GetPosition()->Y() >= maxPos) moveDirY = -1;
      // if(moveDirY < 0 && obj->GetPosition()->Y() <= -maxPos) moveDirY = 1;
      //
      // if(moveDirZ > 0 && obj->GetPosition()->Z() >= maxPos) moveDirZ = -1;
      // if(moveDirZ < 0 && obj->GetPosition()->Z() <= -maxPos) moveDirZ = 1;
      // obj->Move(moveDirX * moveSpeedX * timeProvider->GetDeltaTime_s(), moveDirY * moveSpeedY * timeProvider->GetDeltaTime_s(), moveDirZ * moveSpeedZ * timeProvider->GetDeltaTime_s());

    }
    loadedScene->Update(timeProvider->GetDeltaTime_s());

    renderer->Show();
    renderer->GetEvent();

    timeProvider->OnFrameEnd();
    Logger::Info("This frame took: %lf [s] (%lf FPS)", timeProvider->GetDeltaTime_s(), timeProvider->GetFPS());
  }
  renderer->Quit();
  Logger::Info("Avreage frame time: %lf [s] (%lf FPS)", timeProvider->GetAverageFrameTime_s(), timeProvider->GetAverageFPS());
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
