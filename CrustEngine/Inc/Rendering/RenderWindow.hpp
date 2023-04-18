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
   * @details Starts loop that performs rendering as long as renderer is opened and running.
   * At each frame it calculates FPS, Polls for any pending input events, updates loaded scene by calling #Update method,
   * checks if last event that occured was not EVENT_QUIT and if so ends the renderer work, cleans window and draws projected polygons.
   *
   * @sa Renderer.hpp,
   */
  void Start();

  /**
   * @brief Stops the window rendering process bu killing the renderer. When called the #Start method stops it's loop.
   */
  void Close();

  /**
   * @brief Loads new scene that will be rendered in this window.
   * @details Unloads previously loaded scene by calling #OnUnLoad. gets new scene's name as caption. Recalculates projection matrix according to new scene's main camera and calls #OnLoad on new scene.
   *
   * @param scene Handler to scene handler, which will be loaded.
   */
  void LoadScene(Scene &scene);

    /**
   * @brief Un loads currently loaded scene. After tyhis operation nothing will be rendered onto the screen.
   * @details Unloads loaded scene by calling #OnUnLoad and by setting #loadedScene to nullptr. Also fills Renderer's #projMatrix with zeros.
   */
  void UnLoadScene();

private:
  uint32_t width{0};           //!< Width of this window.
  uint32_t height{0};          //!< Height of this window.
  Renderer *renderer{nullptr}; //!< Widnows's renderer handler.
  Scene *loadedScene{nullptr}; //!< Loaded scene's handler.

  TimeProvider *timeProvider{nullptr}; //!< Windows's time provider that calculates it's work time, FPS etc...

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
  if (renderer == nullptr || timeProvider == nullptr)
    ExceptionsHandler::ThrowError("Cannot start renderer window - It was not properly initialized!");

  static std::vector<RenderObject *> objs;
  loadedScene->Start();

  InputHandler::BeginInputMonitoring();

  while (renderer->IsRunning())
  {
    timeProvider->OnFrameStart();

    InputHandler::PollEvent();

    if (InputHandler::GetLastEvent().type == Event::EVENT_WINDOW_QUIT) // FIXME How to figure out which window is supposed to be closed?
      Close();

    Clean();
    if (loadedScene != nullptr)
    {
      loadedScene->Update(timeProvider->GetDeltaTime_s());
      objs = loadedScene->GetObjectsToRender();
      for (auto obj : objs)
      {
        renderer->RenderMesh(*obj, *loadedScene); 
      }
    }

    renderer->Show();

    timeProvider->OnFrameEnd();
    // Logger::Info("This frame took: %lf [s] (%lf FPS)", timeProvider->GetDeltaTime_s(), timeProvider->GetFPS());// TODO Debug log
  }
  renderer->Quit();
  Logger::Info("Avreage frame time: %lf [s] (%lf FPS)", timeProvider->GetAverageFrameTime_s(), timeProvider->GetAverageFPS()); // TODO Debug log
}

inline void RenderWindow::Close()
{
  renderer->StopRunning();
}

void RenderWindow::LoadScene(Scene &scene)
{
  if (loadedScene != nullptr)
    loadedScene->OnUnLoad();
  loadedScene = &scene;
  renderer->SetWindowTitle(loadedScene->GetName());
  loadedScene->OnLoad();
}

void RenderWindow::UnLoadScene()
{
  if (loadedScene == nullptr) return;
  
  loadedScene->OnUnLoad();
  loadedScene = nullptr;
  renderer->SetWindowTitle("No scene");
}

inline void RenderWindow::Clean()
{
  renderer->SetDrawColor(0, 0, 0);
  renderer->Clean();
}

#endif /* _RENDERWINDOW_HPP_ */
