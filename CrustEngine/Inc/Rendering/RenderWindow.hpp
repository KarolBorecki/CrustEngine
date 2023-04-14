#ifndef _RENDERWINDOW_HPP_
#define _RENDERWINDOW_HPP_

#include <queue>

#include <Utils/TimeProvider.hpp>

#include <Core/Scene.hpp>
#include <Rendering/Renderer.hpp>
#include <Input/InputHandler.hpp>
#include <Rendering/Objects/RenderObject.hpp>
#include <Logging/ExceptionsHandler.hpp>

/**
 * @brief Class responsible to open window, load scene, manage renderer thread and pass render objects to rendering.
 */
class RenderWindow
{
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
  RenderWindow(uint32_t _width, uint32_t _height, Scene &_scene);
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
  void LoadScene(Scene &scene);

private:
  uint32_t width{0};           //!< Width of this window.
  uint32_t height{0};          //!< Height of this window.
  Renderer *renderer{nullptr}; //!< Widnows's renderer handler.
  Scene *loadedScene{nullptr}; //!< Loaded scene's handler.

  TimeProvider *timeProvider{nullptr};

  /**
   * @brief Cleans everything that was drawn on the window.
   */
  void Clean();
};

inline RenderWindow::RenderWindow(uint32_t _width, uint32_t _height, Scene &_scene)
{
  width = _width;
  height = _height;
  renderer = new Renderer(_width, _height);
  if (renderer->Init() != RendererWrapper::RendererStatus::STATUS_OK)
  {
    ExceptionsHandler::ThrowError("RenderWindow failed to initzialize!");
  }
  if (renderer->CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK)
  {
    ExceptionsHandler::ThrowError("RenderWindow failed to be created!");
  }
  LoadScene(_scene);
  timeProvider = new TimeProvider();
}

inline RenderWindow::~RenderWindow()
{
  delete renderer;
  delete timeProvider;
}

void RenderWindow::Start()
{
  loadedScene->Start();


  InputHandler::BeginInputMonitoring();

  while (renderer->IsRunning())
  {
    timeProvider->OnFrameStart();

    Clean();
    std::vector<RenderObject *> objs = loadedScene->GetObjectsToRender();
    for (auto obj : objs)
    {
      renderer->DrawMesh(obj->GetMesh(), obj->GetTransform().GetPosition(), obj->GetTransform().GetEulerRotation(), loadedScene->GetMainCamera(), loadedScene->GetLightSources()[0]->GetTransform().GetEulerRotation(), loadedScene->IsLightProjected());
    }
    loadedScene->Update(timeProvider->GetDeltaTime_s());

    renderer->Show();
    InputHandler::PollEvent();
    if(InputHandler::GetEvent().type == EVENT_WINDOW_QUIT) // FIXME How to figure out which window is supposed to be closed?
      {
        Logger::Log("QUIT - from render window");
        renderer->StopRunning();
      }else if(InputHandler::GetEvent().type == EVENT_KEY_DOWN) {
        Logger::Log("PRESSED - from render window");
      } else {
        Logger::Log("OTHER - from render window");
      }

    timeProvider->OnFrameEnd();
    // Logger::Info("This frame took: %lf [s] (%lf FPS)", timeProvider->GetDeltaTime_s(), timeProvider->GetFPS());
  }
  renderer->Quit();
  Logger::Info("Avreage frame time: %lf [s] (%lf FPS)", timeProvider->GetAverageFrameTime_s(), timeProvider->GetAverageFPS());
}

inline void RenderWindow::Close()
{
  renderer->StopRunning();
}

inline void RenderWindow::LoadScene(Scene &scene)
{ // TODO does not run start of newly loaded scene. Should stop this window and reload scene TODO - add stop window method
  loadedScene = &scene;
  renderer->SetWindowTitle(loadedScene->GetName());
  renderer->RecalculateProjectionMatrix(loadedScene->GetMainCamera());
}

inline void RenderWindow::Clean()
{
  renderer->SetDrawColor(0, 0, 0);
  renderer->Clean();
}

#endif /* _RENDERWINDOW_HPP_ */
