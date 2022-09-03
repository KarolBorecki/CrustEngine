// #include <iostream>
//
// #include "../Inc/DrawerWrapper.hpp"
//
// int main(int argc, char* argv[])
// {
//   Drawer drawer(800, 600);
//   if(drawer.Init() != Drawer::DrawerStatus::STATUS_OK) return 1;
//   if(drawer.CreateWindow() != Drawer::DrawerStatus::STATUS_OK) return 1;
//
//   while(drawe.IsRunning()) {
//
//     drawer.GetEvent();
//   }
//
//   drawer.Clean();
//     //
//     // if (SDL_Init(SDL_INIT_VIDEO) == 0) {
//     //     SDL_Window* window = NULL;
//     //     SDL_Renderer* renderer = NULL;
//     //
//     //     if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
//     //         SDL_bool done = SDL_FALSE;
//     //
//     //         while (!done) {
//     //             SDL_Event event;
//     //
//     //             SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//     //             SDL_RenderClear(renderer);
//     //
//     //             SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//     //             SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
//     //             SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
//     //             SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
//     //             SDL_RenderPresent(renderer);
//     //
//     //             while (SDL_PollEvent(&event)) {
//     //                 if (event.type == SDL_QUIT) {
//     //                     done = SDL_TRUE;
//     //                 }
//     //             }
//     //         }
//     //     }
//     //
//     //
//     // }
//     // if (renderer) {
//     //     SDL_DestroyRenderer(renderer);
//     // }
//     // if (window) {
//     //     SDL_DestroyWindow(window);
//     // }
//     // SDL_Quit();
//     return 0;
// }

#include <iostream>

#include "../Inc/SDLWrapper.hpp"

int main(int argc, char* argv[])
{
  Drawer drawer(800, 600);
  if(drawer.Init() != Drawer::DrawerStatus::STATUS_OK) {
    std::cout<<"Drawer not initied!"<<std::endl;
    return 1;
  }
  if(drawer.CreateWindow() != Drawer::DrawerStatus::STATUS_OK) {
    std::cout<<"Window not created!"<<std::endl;
    return 1;
  }
  while(drawer.IsRunning()) {
    std::cout<<"RUNNING"<<std::endl;

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
