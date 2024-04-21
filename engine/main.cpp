#include <CrustEngine.h>
# include <iostream>
#include "scripting/examples/Rotator.h"
#include "scripting/examples/Mover.h"
#include "scripting/examples/CameraCotroller.h"

int main(int argc, char *argv[]) {
    Crust::Core core;

    Crust::Scene scene;
    Crust::Camera camera(90, 0.1, 300);
    Crust::CameraController controller(0.5, 0.5, 0.5);
    camera.attachScript(controller);
    scene.setMainCamera(camera);

    Crust::RenderObject axis("/Users/karolborecki/Desktop/cube/cube.obj");
    axis.transform().setSize(0.1, 0.1, 0.1);
    axis.transform().setPosition(0.0, 0.0, -2.0);

    Crust::RenderObject object("/Users/karolborecki/Desktop/cube/cube.obj");
    object.transform().setSize(0.1, 0.1, 0.1);
    object.transform().setPosition(0.4, 0.0, -0.8);
    object.transform().setEulerRotation(0.0, 0.0, 90.0);

    Crust::RenderObject object2("/Users/karolborecki/Desktop/cube/cube.obj");
    object2.transform().setSize(0.1, 0.1, 0.1);
    object2.transform().setPosition(0.55, 0.4, -1.2);
    object2.transform().setEulerRotation(0.0, 90.0, 0.0);

    Crust::RenderObject object3("/Users/karolborecki/Desktop/cube/cube.obj");
    object3.transform().setSize(0.1, 0.1, 0.1);
    object3.transform().setPosition(-0.33, -0.4, -1.9);
    object3.transform().setEulerRotation(90.0, 0.0, 0.0);

    scene.addObject(object);
    scene.addObject(object2);
    scene.addObject(axis);
    scene.addObject(object3);

    Crust::LightSource light(Crust::LightType::DIRECTIONAL, Crust::LightIntensity::INTENSIVITY_BRIGHT);
    light.transform().setEulerRotation(0.4, -0.3, -0.89);
    scene.addObject(light);

    Crust::Window *window = core.openWindow(900, 800);
    window->loadScene(scene);
    window->startRenderingLoop();
    return 0;
}