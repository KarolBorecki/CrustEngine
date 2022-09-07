#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

int main(int argc, char* argv[])
{
  Camera cam(0.5);
  Scene scene(&cam);
  Core core;
  core.OpenNewWindow(1000, 800, &scene);
  return 0;
}
