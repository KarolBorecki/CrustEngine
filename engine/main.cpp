#include <CrustEngine.h>
# include <iostream>
#include "scripting/examples/Rotator.h"
#include "scripting/examples/Mover.h"
#include "scripting/examples/CameraCotroller.h"

int main(int argc, char *argv[]) {
//    Crust::Core core;
//
//    Crust::Scene scene;
//    Crust::Camera camera(90, 0.1, 300);
//    Crust::CameraController controller(0.5f, 0.5f, 0.5f);
//    camera.attachScript(controller);
//    scene.setMainCamera(camera);
//
//    Crust::RenderObject axis("/Users/karolborecki/Desktop/cube/axis.obj");
//    axis.transform().setSize(0.1f, 0.1f, 0.1f);
//    axis.transform().setPosition(0.0f, 0.0f, -2.0f);
//
//    Crust::RenderObject object("/Users/karolborecki/Desktop/cube/cube.obj");
//    object.transform().setSize(0.1f, 0.1f, 0.1f);
//    object.transform().setPosition(0.4f, 0.0f, -0.8f);
//    Crust::Rotator rotator(0.5f, 0.6f, 0.7f);
//    object.attachScript(rotator);
//
//    Crust::RenderObject object2("/Users/karolborecki/Desktop/cube/cube.obj");
//    object2.transform().setSize(0.1f, 0.1f, 0.1f);
//    object2.transform().setPosition(0.55f, 0.4f, -1.2f);
//    Crust::Rotator rotator2(0.1f, 0.9f, 0.4f);
//    object2.attachScript(rotator2);
//
////    Crust::RenderObject object3("/Users/karolborecki/Desktop/cube/cube.obj");
////    object2.transform().setSize(0.1f, 0.1f, 0.1f);
////    object2.transform().setPosition(-0.33f, -0.4f, -1.9f);
////    Crust::Rotator rotator3(0.4f, 0.2f, 0.5f);
////    object2.attachScript(rotator3);
//
//    scene.addObject(object);
////    scene.addObject(object2);
//    scene.addObject(axis);
////    scene.addObject(object3);
//
//    Crust::LightSource light(Crust::LightType::DIRECTIONAL, Crust::LightIntensity::INTENSIVITY_BRIGHT);
//    light.transform().setEulerRotation(0.4f, -0.3f, -0.89f);
//    scene.addObject(light);
//
//    Crust::Window *window = core.openWindow(900, 800);
//    window->loadScene(scene);
//    window->startRenderingLoop();

    Crust::Vector3 p = Crust::Math::v3IntersectPlane(Crust::Vector3(0.0f, 0.0f, 0.3f), Crust::Vector3(0.0f, 0.0f, 1.0f),
                                                     Crust::Vector3(0.0f, 0.0f, 0.0f),
                                                     Crust::Vector3(1.0f, 1.0f, 1.0f));
    std::cout << p << std::endl;
    return 0;
}