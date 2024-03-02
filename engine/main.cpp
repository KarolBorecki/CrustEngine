#include <CrustEngine.h>

using namespace Crust; // TODO DELETE

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

    Crust::RenderObject object("../resources/models/cube.obj");
    scene.addObject(object);

    Window window = core.openWindow(800, 600);
    window.loadScene(scene);

    core.quit();
    Crust::Logger::info("Quitting the engine.");
    return 0;
}