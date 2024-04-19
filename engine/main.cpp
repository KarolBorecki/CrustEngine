#include <CrustEngine.h>

#include "scripting/examples/Rotator.h"
#include "scripting/examples/Mover.h"

int main(int argc, char *argv[])
{
    Crust::Core core;

    Crust::Scene scene;
    Crust::Camera camera(90, 0.1, 300);
    scene.setMainCamera(camera);

    Crust::RenderObject object("/Users/karolborecki/Desktop/cube/VideoShip.obj");
    object.transform().setSize(0.1f, 0.1f, 0.1f);
    object.transform().setPosition(0.0f, 0.0f, -1.5f);
//    Crust::Rotator rotator(0.4f, 0.3f, 0.3f);
    Crust::Mover mover;
     object.attachScript(mover);

    scene.addObject(object);

    Crust::LightSource light(Crust::LightType::DIRECTIONAL, Crust::LightIntensity::INTENSIVITY_BRIGHT);
    light.transform().setEulerRotation(0.4f, -0.3f, -0.89f);
    scene.addObject(light);

    Crust::Window* window = core.openWindow(800, 600);
    window->loadScene(scene);
    window->startRenderingLoop();
    return 0;
}