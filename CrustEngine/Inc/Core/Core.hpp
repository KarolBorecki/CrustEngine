#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>

#include <Utils/TimeProvider.hpp>

#include <Core/Scene.hpp>
#include <Rendering/RenderWindow.hpp>

/**
 * @brief Class, which helds opened windows and manages the engine work.
 */
class Core
{
public:
  Core();
  virtual ~Core() = default;
  /**
   * @brief Opens new RenderWindow of size #width x #height and default loaded scene set to #scene.
   *
   * @details Creates new object of instance RenderWindow and adds it to #openedWindows array. After this the created window starts using RenderWindow::Start().
   *
   * @param width The new opened window width.
   * @param height The new opened window height.
   * @param scene The new opened scene loaded scene. This can be changed with RenderWindow::LoadScene.
   *
   * @sa RenderWindow.hpp
   */
  void OpenNewWindow(uint32_t width, uint32_t uint32_t, Scene &scene);

  /**
   * @brief Closes the specified #window.
   *
   * @details Searches for #window inside #openedWindows array and runs RenderWindow::Close method and deletes it's object.
   *
   * @param window window to close.
   *
   * @sa RenderWindow.hpp
   */
  void CloseWindow(RenderWindow &window);
  /**
   * @brief Closes all opened windows
   *
   * @details Loops through #openedWindows array, runs RenderWindow::Close and deletes each window.
   *
   * @sa RenderWindow.hpp
   */
  void CloseAllWindows();
  /**
   * @brief Quits the engine. Should be called at program end.
   *
   * @details Runs RenderWindow::CloseAllWindows.
   */
  void Quit();

private:
  std::vector<RenderWindow *> openedWindows; //!< Array of currently opened windows.
};

inline Core::Core() { TimeProvider::OnEngineStart(); }

void Core::OpenNewWindow(uint32_t width, uint32_t height, Scene &scene)
{
  RenderWindow *window = new RenderWindow(width, height, scene);

  window->Start(); // TODO: run on new thread

  openedWindows.push_back(window);
}

void Core::CloseWindow(RenderWindow &window)
{
  window.Close();
  remove(openedWindows.begin(), openedWindows.end(), &window);
  delete &window;
}

void Core::CloseAllWindows()
{
  for (auto &window : openedWindows)
  {
    window->Close();
    delete window;
  }
  openedWindows.clear();
}

void Core::Quit()
{
  Logger::Info("Engine work time: %lf [s]", TimeProvider::GetTime_s());
  CloseAllWindows();
}

#endif /* _CORE_HPP_ */
