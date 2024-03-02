#ifndef _CORE_HPP_
#define _CORE_HPP_

#include <vector>

#include <Utils/TimeProvider.hpp>

#include <Core/Scene.hpp>
#include <Rendering/RenderWindow.hpp>

// TODO maybe it doestn't need to be a class
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
  void OpenNewWindow(uint16_t width, uint16_t height, Scene &scene);

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
  std::vector<RenderWindow *> _openedWindows; //!< Array of currently opened windows.
};

inline Core::Core() { TimeProvider::OnEngineStart(); }

void Core::OpenNewWindow(uint16_t width, uint16_t height, Scene &scene)
{
  if (width == 0 || height == 0)
    ExceptionsHandler::ThrowError("Error while opening new window: Width or Height cannot be equal to 0!");

  RenderWindow *window = new RenderWindow(width, height, scene);
  window->Start(); // TODO: run on new thread

  _openedWindows.push_back(window);
}

void Core::CloseWindow(RenderWindow &window)
{
  window.Close();
  remove(_openedWindows.begin(), _openedWindows.end(), &window);
  delete &window;
}

void Core::CloseAllWindows()
{
  for (auto &window : _openedWindows)
  {
    if (window == nullptr)
      continue;
    window->Close();
    delete window;
  }
  _openedWindows.clear();
}

void Core::Quit()
{
  CloseAllWindows();
}

#endif /* _CORE_HPP_ */
