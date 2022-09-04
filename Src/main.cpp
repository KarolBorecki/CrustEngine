#include <Logger.hpp>

#include <SDLWrapper.hpp>


int main(int argc, char* argv[])
{
  Drawer drawer(800, 600);
  if(drawer.Init() != Drawer::DrawerStatus::STATUS_OK) {
    Logger::Error("Drawer could not be initialized!");
    return 1;
  }
  if(drawer.CreateWindow() != Drawer::DrawerStatus::STATUS_OK) {
    Logger::Error("Drawer could not be created!");
    return 1;
  }
  while(drawer.IsRunning()) {
    drawer.SetDrawColor(0,0,0);
    drawer.Clean();

    drawer.SetDrawColor(Drawer::DrawerColor::RED);

    drawer.DrawLine(320, 200, 300, 240);
    drawer.DrawLine(300, 240, 340, 240);
    drawer.DrawLine(340, 240, 320, 200);

    drawer.Show();
    drawer.GetEvent();
  }

  drawer.Quit();
  return 0;
}
