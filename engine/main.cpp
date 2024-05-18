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

    uint8_t cube_count_x = 2;
    uint8_t cube_count_y = 2;
    uint8_t cube_count_z = 2;
    float cube_size = 0.3;
    float cube_spacing = 0.605; // cubes are of size 2
    for (uint8_t x = 0; x < cube_count_x; x++) {
        for (uint8_t y = 0; y < cube_count_y; y++) {
            for (uint8_t z = 0; z < cube_count_z; z++) {
                Crust::RenderObject *cube = new Crust::RenderObject("/Users/karolborecki/Desktop/cube/cube.obj");
                cube->transform().setSize(cube_size, cube_size, cube_size);
                cube->transform().setPosition(x * cube_spacing, y * cube_spacing, z * cube_spacing);
                cube->transform().setEulerRotation(0.0, 0.0, 0.0);
                cube->getMaterial().setDiffuse(
                        {(uint8_t) (120 + x * 150 / cube_count_x),
                         (uint8_t) (120 + y * 150 / cube_count_x),
                         (uint8_t) (120 + z * 150 / cube_count_x),
                         255});
                scene.addObject(*cube);
            }
        }
    }

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


    Crust::LightSource light(Crust::LightType::DIRECTIONAL, Crust::LightIntensity::INTENSIVITY_BRIGHT);
    light.transform().setEulerRotation(0.4, -0.9, -0.89);
    scene.addObject(light);

    Crust::Window *window = core.openWindow(900, 800);
    window->loadScene(scene);
    window->startRenderingLoop();
    return 0;
    Crust::Vector3 intersection;
    intersection = Crust::Math::v3IntersectEdge({0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 0.0},
                                                {1.0, 1.0, 0.0});
    std::cout << "Intersection: " << intersection.x() << " " << intersection.y() << " " << intersection.z()
              << std::endl;
    std::cout << std::endl;

    Crust::Vector3 v1(200.0, 25.0, 0.0);
    Crust::Vector3 v2(350.0, 200.0, 0.0);
    Crust::Vector3 v3(50.0, 150.0, 0.0);
    Crust::Triangle tri;
    tri.setVertex(0, {100.0, 50.0, 0.0});
    tri.setVertex(1, {300.0, 50.0, 0.0});
    tri.setVertex(2, {150.0, 250.0, 0.0});
    Crust::Triangle out_tri1;
    Crust::Triangle out_tri2;
    Crust::Triangle out_tri3;
    Crust::Triangle out_tri4;
    Crust::Triangle out_tri5;
    Crust::Triangle out_tri6;
    Crust::Triangle out_tri7;
    Crust::Triangle out_tri8;
    Crust::Triangle out_tri9;
    uint8_t tri_count = Crust::Math::triangle2DClipAgainstEdge(v1, v2, tri, out_tri1, out_tri2, out_tri3);

    uint8_t tri_count2 = Crust::Math::triangle2DClipAgainstEdge(v1, v3, tri, out_tri4, out_tri5, out_tri6);

    uint8_t tri_count3 = Crust::Math::triangle2DClipAgainstEdge(v3, v2, tri, out_tri7, out_tri8, out_tri9);

    std::cout << "Triangle count: " << (int) tri_count << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 1: " << out_tri1.getVertex(0).x() << " " << out_tri1.getVertex(0).y() << " "
              << out_tri1.getVertex(0).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri1.getVertex(1).x() << " " << out_tri1.getVertex(1).y() << " "
              << out_tri1.getVertex(1).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri1.getVertex(2).x() << " " << out_tri1.getVertex(2).y() << " "
              << out_tri1.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 2: " << out_tri2.getVertex(0).x() << " " << out_tri2.getVertex(0).y() << " "
              << out_tri2.getVertex(0).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri2.getVertex(1).x() << " " << out_tri2.getVertex(1).y() << " "
              << out_tri2.getVertex(1).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri2.getVertex(2).x() << " " << out_tri2.getVertex(2).y() << " "
              << out_tri2.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 3: " << out_tri3.getVertex(0).x() << " " << out_tri3.getVertex(0).y() << " "
              << out_tri3.getVertex(0).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri3.getVertex(1).x() << " " << out_tri3.getVertex(1).y() << " "
              << out_tri3.getVertex(1).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri3.getVertex(2).x() << " " << out_tri3.getVertex(2).y() << " "
              << out_tri3.getVertex(2).z() << std::endl;

    std::cout << std::endl;
    std::cout << "Triangle count: " << (int) tri_count2 << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 1: " << out_tri4.getVertex(0).x() << " " << out_tri4.getVertex(0).y() << " "
              << out_tri4.getVertex(0).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri4.getVertex(1).x() << " " << out_tri4.getVertex(1).y() << " "
              << out_tri4.getVertex(1).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri4.getVertex(2).x() << " " << out_tri4.getVertex(2).y() << " "
              << out_tri4.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 2: " << out_tri5.getVertex(0).x() << " " << out_tri5.getVertex(0).y() << " "
              << out_tri5.getVertex(0).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri5.getVertex(1).x() << " " << out_tri5.getVertex(1).y() << " "
              << out_tri5.getVertex(1).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri5.getVertex(2).x() << " " << out_tri5.getVertex(2).y() << " "
              << out_tri5.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 3: " << out_tri6.getVertex(0).x() << " " << out_tri6.getVertex(0).y() << " "
              << out_tri6.getVertex(0).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri6.getVertex(1).x() << " " << out_tri6.getVertex(1).y() << " "
              << out_tri6.getVertex(1).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri6.getVertex(2).x() << " " << out_tri6.getVertex(2).y() << " "
              << out_tri6.getVertex(2).z() << std::endl;

    std::cout << std::endl;
    std::cout << "Triangle count: " << (int) tri_count3 << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 1: " << out_tri7.getVertex(0).x() << " " << out_tri7.getVertex(0).y() << " "
              << out_tri7.getVertex(0).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri7.getVertex(1).x() << " " << out_tri7.getVertex(1).y() << " "
              << out_tri7.getVertex(1).z() << std::endl;
    std::cout << "Triangle 1: " << out_tri7.getVertex(2).x() << " " << out_tri7.getVertex(2).y() << " "
              << out_tri7.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 2: " << out_tri8.getVertex(0).x() << " " << out_tri8.getVertex(0).y() << " "
              << out_tri8.getVertex(0).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri8.getVertex(1).x() << " " << out_tri8.getVertex(1).y() << " "
              << out_tri8.getVertex(1).z() << std::endl;
    std::cout << "Triangle 2: " << out_tri8.getVertex(2).x() << " " << out_tri8.getVertex(2).y() << " "
              << out_tri8.getVertex(2).z() << std::endl;
    std::cout << std::endl;
    std::cout << "Triangle 3: " << out_tri9.getVertex(0).x() << " " << out_tri9.getVertex(0).y() << " "
              << out_tri9.getVertex(0).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri9.getVertex(1).x() << " " << out_tri9.getVertex(1).y() << " "
              << out_tri9.getVertex(1).z() << std::endl;
    std::cout << "Triangle 3: " << out_tri9.getVertex(2).x() << " " << out_tri9.getVertex(2).y() << " "
              << out_tri9.getVertex(2).z() << std::endl;


    Crust::Library2DWrapper wrapper;
    wrapper.init();
    wrapper.createWindow(800, 600);
    Crust::InputHandler::beginInputMonitoring();
    while (!wrapper.shouldClose()) {
        Crust::InputHandler::pollEvent();
        wrapper.onDrawStart();
        if (Crust::InputHandler::isPressed(Crust::Key::KEY_SPACE)) {
            wrapper.drawLine(v1.x(), v1.y(), v2.x(), v2.y(), 255, 255, 255, 255);
            wrapper.drawLine(v1.x(), v1.y(), v3.x(), v3.y(), 255, 255, 255, 255);
            wrapper.drawLine(v2.x(), v2.y(), v3.x(), v3.y(), 255, 255, 255, 255);
        }

        if (tri_count > 0)
            wrapper.drawHollowTriangle(out_tri1.getVertex(0).x(), out_tri1.getVertex(0).y(),
                                       out_tri1.getVertex(1).x(),
                                       out_tri1.getVertex(1).y(), out_tri1.getVertex(2).x(),
                                       out_tri1.getVertex(2).y(),
                                       255, 255, 255, 255);
        if (tri_count > 1)
            wrapper.drawHollowTriangle(out_tri2.getVertex(0).x(), out_tri2.getVertex(0).y(),
                                       out_tri2.getVertex(1).x(),
                                       out_tri2.getVertex(1).y(), out_tri2.getVertex(2).x(),
                                       out_tri2.getVertex(2).y(),
                                       255, 255, 255, 255);
        if (tri_count > 2)
            wrapper.drawHollowTriangle(out_tri3.getVertex(0).x(), out_tri3.getVertex(0).y(),
                                       out_tri3.getVertex(1).x(),
                                       out_tri3.getVertex(1).y(), out_tri3.getVertex(2).x(),
                                       out_tri3.getVertex(2).y(),
                                       255, 255, 255, 255);

        if (tri_count2 > 0)
            wrapper.drawHollowTriangle(out_tri4.getVertex(0).x(), out_tri4.getVertex(0).y(),
                                       out_tri4.getVertex(1).x(),
                                       out_tri4.getVertex(1).y(), out_tri4.getVertex(2).x(),
                                       out_tri4.getVertex(2).y(),
                                       20, 255, 255, 255);

        if (tri_count2 > 1)
            wrapper.drawHollowTriangle(out_tri5.getVertex(0).x(), out_tri5.getVertex(0).y(),
                                       out_tri5.getVertex(1).x(),
                                       out_tri5.getVertex(1).y(), out_tri5.getVertex(2).x(),
                                       out_tri5.getVertex(2).y(),
                                       20, 255, 255, 255);
        if (tri_count2 > 2)
            wrapper.drawHollowTriangle(out_tri6.getVertex(0).x(), out_tri6.getVertex(0).y(),
                                       out_tri6.getVertex(1).x(),
                                       out_tri6.getVertex(1).y(), out_tri6.getVertex(2).x(),
                                       out_tri6.getVertex(2).y(),
                                       20, 255, 255, 255);
        if (tri_count3 > 0)
            wrapper.drawHollowTriangle(out_tri7.getVertex(0).x(), out_tri7.getVertex(0).y(),
                                       out_tri7.getVertex(1).x(),
                                       out_tri7.getVertex(1).y(), out_tri7.getVertex(2).x(),
                                       out_tri7.getVertex(2).y(),
                                       255, 20, 255, 255);
        if (tri_count3 > 1)
            wrapper.drawHollowTriangle(out_tri8.getVertex(0).x(), out_tri8.getVertex(0).y(),
                                       out_tri8.getVertex(1).x(),
                                       out_tri8.getVertex(1).y(), out_tri8.getVertex(2).x(),
                                       out_tri8.getVertex(2).y(),
                                       255, 20, 255, 255);
        if (tri_count3 > 2)
            wrapper.drawHollowTriangle(out_tri9.getVertex(0).x(), out_tri9.getVertex(0).y(),
                                       out_tri9.getVertex(1).x(),
                                       out_tri9.getVertex(1).y(), out_tri9.getVertex(2).x(),
                                       out_tri9.getVertex(2).y(),
                                       255, 20, 255, 255);
        wrapper.onDrawEnd();
    }

    wrapper.close();

    return 0;
}