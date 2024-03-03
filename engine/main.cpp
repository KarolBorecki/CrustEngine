#include <CrustEngine.h>

int main(int argc, char *argv[])
{
    Crust::Core core;

    Crust::Scene scene;
    Crust::Camera camera(90, 0.1, 1000);
    scene.setMainCamera(camera);

    Crust::RenderObject object("/Users/karolborecki/Desktop/CrustEngine/Tmp/meshes/cube.obj");
    scene.addObject(object);

    Crust::Window* window = core.openWindow(800, 600);
    window->loadScene(scene);
    window->startRenderingLoop();
    return 0;
}