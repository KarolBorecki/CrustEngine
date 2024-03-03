#include <CrustEngine.h>

//TODO investigate [[nodiscard]] attribute
// TODO review reference vs pointer scenarios
// USE reference when you want to tell that object cannot exists withou another
// USE pointer in any other cases
int main(int argc, char *argv[])
{
//    Crust::Core core;
//
//    Crust::Scene scene;
//    Crust::Camera camera(90, 0.1, 1000);
//    scene.setMainCamera(camera);
//
//    Crust::RenderObject object("/Users/karolborecki/Desktop/CrustEngine/Tmp/meshes/cube.obj");
//    scene.addObject(object);
//
//    Crust::Window window = core.openWindow(800, 600);
//    window.loadScene(scene);
//
//    core.quit();
//    Crust::Logger::info("Quitting the engine.");
//

    Crust::Library2DWrapper wrapper;
    Crust::Status status = wrapper.init();
    if(status != Crust::OK) {
        Crust::Logger::error("Error while initializing window.");
        return 1;
    }
    status = wrapper.createWindow(800, 600);
    if(status != Crust::OK) {
        Crust::Logger::error("Error while creating window.");
        return 1;
    }
    while(1) {
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                break;
            }
        }
        wrapper.onDrawStart();
        wrapper.drawTriangle(0, 0, 800, 0, 400, 600, 255);
        wrapper.onDrawEnd();
Crust::Logger::info("Drawing");
    }
    wrapper.quit();
    return 0;
}