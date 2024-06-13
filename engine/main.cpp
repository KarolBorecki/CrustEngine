#include <CrustEngine.h>
# include <iostream>
#include "scripting/examples/Rotator.h"
#include "scripting/examples/Mover.h"
#include "scripting/examples/CameraCotroller.h"

int main(int argc, char *argv[]) {
    Crust::Core core;

    Crust::Scene scene;
    Crust::Camera camera(90, 0.1, 300);
    Crust::CameraController controller(0.7, 0.7, 0.7);
    camera.transform().setPosition(0, 0, -2);
    camera.attachScript(controller);
    scene.setMainCamera(camera);

    uint8_t cube_count_x = 3;
    uint8_t cube_count_y = 2;
    uint8_t cube_count_z = 2;
    float cube_size = 0.3;
    float cube_spacing = 0.62; // cubes are of size 2
    for (uint8_t x = 0; x < cube_count_x; x++) {
        for (uint8_t y = 0; y < cube_count_y; y++) {
            for (uint8_t z = 0; z < cube_count_z; z++) {
                Crust::RenderObject *cube = new Crust::RenderObject("/Users/karolborecki/Desktop/cube/cube.obj");
                cube->transform().setSize(cube_size, cube_size, cube_size);
                cube->transform().setPosition(x * cube_spacing, y * cube_spacing, z * cube_spacing);
                cube->transform().setEulerRotation(0.0, 0.0, 0.0);
                cube->getMaterial().setDiffuse(
                        {(float) ((80 + x * 90 / cube_count_x) / 255),
                         (float) ((80 + y * 90 / cube_count_x) / 255),
                         (float) ((80 + z * 90 / cube_count_x) / 255),
                         1.0f});
                cube->getMaterial().setShininess(x * y * z * 7);
                scene.addObject(*cube);
            }
        }
    }

    Crust::RenderObject *video = new Crust::RenderObject("/Users/karolborecki/Desktop/cube/VideoShip.obj");
    video->transform().setSize(cube_size, cube_size, cube_size);
    video->transform().setPosition(2, 2, 2);
    video->transform().setEulerRotation(0.0, 0.0, 0.0);
    video->getMaterial().setDiffuse(
            {0.1f, 0.5f, 0.9f, 1.0f});
    scene.addObject(*video);

//    Crust::RenderObject cube1("/Users/karolborecki/Desktop/cube/cube.obj");
//    cube1.transform().setSize(1, 0.1, 0.1);
//    cube1.transform().setPosition(0, 0, 0);
//    cube1.transform().setEulerRotation(0.0, 60.0, -45.0);
//    cube1.getMaterial().setDiffuse({0, 255, 0, 255});
//    scene.addObject(cube1);
//
//    Crust::RenderObject cube2("/Users/karolborecki/Desktop/cube/cube.obj");
//    cube2.transform().setSize(1, 0.1, 0.1);
//    cube2.transform().setPosition(0.6, -0.4, 0);
//    cube2.transform().setEulerRotation(0.0, 0.0, 0.0);
//    cube2.getMaterial().setDiffuse({0, 0, 255, 255});
//    scene.addObject(cube2);
//
//    Crust::RenderObject cube3("/Users/karolborecki/Desktop/cube/cube.obj");
//    cube3.transform().setSize(1, 0.1, 0.1);
//    cube3.transform().setPosition(0, 0.0, -0.2);
//    cube3.transform().setEulerRotation(0.0, -30.0, 45.0);
//    cube3.getMaterial().setDiffuse({255, 0, 0, 255});
//    scene.addObject(cube3);


    Crust::LightSource light(Crust::LightType::DIRECTIONAL, 0.79f);
    light.transform().setEulerRotation(0.4, -0.9, -0.89);
    scene.addObject(light);

    Crust::Window *window = core.openWindow(900, 800);
    window->loadScene(scene);
    window->startRenderingLoop();
    return 0;
}