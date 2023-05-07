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
  uint32_t _width{0};            //!< Width of this window. //TODO change to uint16_t
  uint32_t _height{0};           //!< Height of this window.
  Renderer *p_renderer{nullptr}; //!< Widnows's renderer handler.
  Scene *p_loadedScene{nullptr}; //!< Loaded scene's handler.

  TimeProvider *p_timeProvider{nullptr}; //!< Windows's time provider that calculates it's work time, FPS etc...

  /**
   * @brief Cleans everything that was drawn on the window.
   */
  void Clean();
};

inline RenderWindow::RenderWindow(uint32_t _width, uint32_t _height, Scene &_scene)
{
  _width = _width;
  _height = _height;
  p_renderer = new Renderer(_width, _height);
  if (p_renderer->Init() != RendererWrapper::RendererStatus::STATUS_OK)
  {
    ExceptionsHandler::ThrowError("RenderWindow failed to initzialize!");
  }
  if (p_renderer->CreateWindow() != RendererWrapper::RendererStatus::STATUS_OK)
  {
    ExceptionsHandler::ThrowError("RenderWindow failed to be created!");
  }
  LoadScene(_scene);
  p_timeProvider = new TimeProvider();
}

inline RenderWindow::~RenderWindow()
{
  delete p_renderer;
  delete p_timeProvider;
}

void RenderWindow::Start()
{
  if (p_renderer == nullptr || p_timeProvider == nullptr)
    ExceptionsHandler::ThrowError("Cannot start renderer window - It was not properly initialized!");

  static std::vector<RenderObject *> objs;
  p_loadedScene->Start();

  InputHandler::BeginInputMonitoring();
  while (p_renderer->IsRunning())
  {
    p_timeProvider->OnFrameStart();

    InputHandler::PollEvent();

    if (InputHandler::GetLastEvent().type == Event::EVENT_WINDOW_QUIT) // FIXME How to figure out which window is supposed to be closed?
      Close();

    Clean();
    if (p_loadedScene != nullptr)
    {
      p_loadedScene->Update(p_timeProvider->GetDeltaTime_s());
      p_renderer->RenderScene(*p_loadedScene);
    }

    p_renderer->Show();

    p_timeProvider->OnFrameEnd();
    // Logger::Info("This frame took: %lf [s] (%lf FPS)", timeProvider->GetDeltaTime_s(), timeProvider->GetFPS());// TODO Debug log
  }
  p_renderer->Quit();
  Logger::Info("Avreage frame time: %lf [s] (%lf FPS)", p_timeProvider->GetAverageFrameTime_s(), p_timeProvider->GetAverageFPS()); // TODO Debug log
}

inline void RenderWindow::Close()
{
  p_renderer->StopRunning();
}

void RenderWindow::LoadScene(Scene &scene)
{
  if (p_loadedScene != nullptr)
    p_loadedScene->OnUnLoad();
  p_loadedScene = &scene;
  p_renderer->SetWindowTitle(p_loadedScene->GetName());
  p_loadedScene->OnLoad();
}

void RenderWindow::UnLoadScene()
{
  if (p_loadedScene == nullptr)
    return;

  p_loadedScene->OnUnLoad();
  p_loadedScene = nullptr;
  p_renderer->SetWindowTitle("No scene");
}

inline void RenderWindow::Clean()
{
  p_renderer->SetDrawColor(0, 0, 0);
  p_renderer->Clean();
}

#endif /* _RENDERWINDOW_HPP_ */
