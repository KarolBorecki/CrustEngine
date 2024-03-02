#include <CrustEngine.h>

//TODO investigate [[nodiscard]] attribute
// TODO review reference vs pointer scenarios
// USE reference when you want to tell that object cannot exists withou another
// USE pointer in any other cases
int main(int argc, char *argv[])
{
    Crust::Core core;

    Crust::Scene scene;
    Crust::Camera camera(90, 0.1, 1000);
    scene.setMainCamera(camera);

    Crust::RenderObject object("/Users/karolborecki/Desktop/CrustEngine/Tmp/meshes/cube.obj");
    scene.addObject(object);

    Window window = core.openWindow(800, 600);
    window.loadScene(scene);

    core.quit();
    Crust::Logger::info("Quitting the engine.");


    Crust::Library2DWrapper wrapper;
    wrapper.init();
    wrapper.createWindow(800, 600);
    while(!wrapper.shouldClose()) {
        wrapper.onDrawStart();
        wrapper.drawTriangle(0, 0, 800, 0, 400, 600, 255);
        wrapper.onDrawEnd();
    }
    wrapper.quit();
    return 0;
}