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
    object.getMaterial().setDiffuse({43, 234, 76, 255});

    Crust::RenderObject object2("/Users/karolborecki/Desktop/cube/cube.obj");
    object2.transform().setSize(0.1, 0.1, 0.1);
    object2.transform().setPosition(0.55, 0.4, -1.2);
    object2.transform().setEulerRotation(0.0, 90.0, 0.0);
    object2.getMaterial().setDiffuse({40, 35, 223, 255});

    Crust::RenderObject object3("/Users/karolborecki/Desktop/cube/cube.obj");
    object3.transform().setSize(0.1, 0.1, 0.1);
    object3.transform().setPosition(-0.33, -0.4, -1.9);
    object3.transform().setEulerRotation(90.0, 0.0, 0.0);
    object3.getMaterial().setDiffuse({120, 30, 89, 255});

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
//
//    Crust::Vector3 intersection;
//    intersection = Crust::Math::v3IntersectEdge({0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 1.0, 0.0});
//    std::cout << "Intersection: " << intersection.x() << " " << intersection.y() << " " << intersection.z()
//              << std::endl;
//    std::cout << std::endl;
//
//    Crust::Vector3 v1(2.0, 0.25, 0.0);
//    Crust::Vector3 v2(3.5, 2.0, 0.0);
//    Crust::Triangle tri;
//    tri.setVertex(0, {1.0, 0.5, 0.0});
//    tri.setVertex(1, {3.0, 0.5, 0.0});
//    tri.setVertex(2, {1.5, 2.5, 0.0});
//    Crust::Triangle out_tri1;
//    Crust::Triangle out_tri2;
//    Crust::Triangle out_tri3;
//    uint8_t tri_count = Crust::Math::triangle2DClipAgainstEdge(v1, v2, tri, out_tri1, out_tri2, out_tri3);
//
//    std::cout << "Triangle count: " << (int) tri_count << std::endl;
//    std::cout << std::endl;
//    std::cout << "Triangle 1: " << out_tri1.getVertex(0).x() << " " << out_tri1.getVertex(0).y() << " "
//              << out_tri1.getVertex(0).z() << std::endl;
//    std::cout << "Triangle 1: " << out_tri1.getVertex(1).x() << " " << out_tri1.getVertex(1).y() << " "
//              << out_tri1.getVertex(1).z() << std::endl;
//    std::cout << "Triangle 1: " << out_tri1.getVertex(2).x() << " " << out_tri1.getVertex(2).y() << " "
//              << out_tri1.getVertex(2).z() << std::endl;
//    std::cout << std::endl;
//    std::cout << "Triangle 2: " << out_tri2.getVertex(0).x() << " " << out_tri2.getVertex(0).y() << " "
//              << out_tri2.getVertex(0).z() << std::endl;
//    std::cout << "Triangle 2: " << out_tri2.getVertex(1).x() << " " << out_tri2.getVertex(1).y() << " "
//              << out_tri2.getVertex(1).z() << std::endl;
//    std::cout << "Triangle 2: " << out_tri2.getVertex(2).x() << " " << out_tri2.getVertex(2).y() << " "
//              << out_tri2.getVertex(2).z() << std::endl;
//    std::cout << std::endl;
//    std::cout << "Triangle 3: " << out_tri3.getVertex(0).x() << " " << out_tri3.getVertex(0).y() << " "
//              << out_tri3.getVertex(0).z() << std::endl;
//    std::cout << "Triangle 3: " << out_tri3.getVertex(1).x() << " " << out_tri3.getVertex(1).y() << " "
//              << out_tri3.getVertex(1).z() << std::endl;
//    std::cout << "Triangle 3: " << out_tri3.getVertex(2).x() << " " << out_tri3.getVertex(2).y() << " "
//              << out_tri3.getVertex(2).z() << std::endl;
//
//    Crust::Library2DWrapper wrapper;
//    wrapper.init();
//    wrapper.createWindow(800, 600);
//    Crust::InputHandler::beginInputMonitoring();
//    while (!wrapper.shouldClose()) {
//        Crust::InputHandler::pollEvent();
//        wrapper.onDrawStart();
//        if (tri_count > 0)
//            wrapper.drawHollowTriangle(out_tri1.getVertex(0).x() * 100, out_tri1.getVertex(0).y() * 100,
//                                       out_tri1.getVertex(1).x() * 100,
//                                       out_tri1.getVertex(1).y() * 100, out_tri1.getVertex(2).x() * 100,
//                                       out_tri1.getVertex(2).y() * 100,
//                                       255);
//        if (tri_count > 1)
//            wrapper.drawHollowTriangle(out_tri2.getVertex(0).x() * 100, out_tri2.getVertex(0).y() * 100,
//                                       out_tri2.getVertex(1).x() * 100,
//                                       out_tri2.getVertex(1).y() * 100, out_tri2.getVertex(2).x() * 100,
//                                       out_tri2.getVertex(2).y() * 100,
//                                       255);
//        if (tri_count > 2)
//            wrapper.drawHollowTriangle(out_tri3.getVertex(0).x() * 100, out_tri3.getVertex(0).y() * 100,
//                                       out_tri3.getVertex(1).x() * 100,
//                                       out_tri3.getVertex(1).y() * 100, out_tri3.getVertex(2).x() * 100,
//                                       out_tri3.getVertex(2).y() * 100,
//                                       255);
//        wrapper.onDrawEnd();
//    }
//
//    wrapper.close();

    return 0;
}