#include <Logging/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Mesh.hpp>
#include <Rendering/Objects/Lightining/DirectionalLight.hpp>
#include <Rendering/Objects/RenderObject.hpp>

#include <Files/MeshLoader.hpp>

#include <Math/Matrix.hpp>

#include <Scripting/SampleScripts/LoopMove.hpp>
#include <Scripting/SampleScripts/Mover.hpp>

// TODO implement to strings - it is usefull at last
int main(int argc, char *argv[])
{
    Logger::Info("Engine Start");

    Camera cam(90, 0.1, 1000.0);
    cam.GetTransform().SetPosition(-4, -5, -10);

    Scene scene("T Scene", cam);

    Mesh mesh("Sample mesh");

    std::string name = argv[1];
    std::string path = "/Users/karolborecki/Desktop/CrustEngine/CrustEngine/Tmp/meshes/" + name + ".obj";

    MeshLoader::LoadMeshFromFile(path.c_str(), &mesh);
    RenderObject rObj(mesh);

    // LoopMove rObjMove(-50, 50, 0, 0, 0, 0, 10, 0, 0);
    // cam.AttachScript(&rObjMove);
    // Rotate rObjRotation(&rObj);
    // rObj.AttachScript(&rObjMove);
    // rObj.AttachScript(&rObjRotation);

    Mover mover(12, 12, 12);
    cam.AttachScript(mover);
    //rObj.AttachScript(mover);

    Vector3 lightSourceDir(0.6, 0.2, -0.5);
    DirectionalLight dirLightSource(255, lightSourceDir);

    scene.AddObject(rObj);
    scene.AddObject(dirLightSource);

    Core core;
    core.OpenNewWindow(1000, 800, scene);
    core.Quit();
    Logger::Info("Engine work time: %lf [s]", TimeProvider::GetTime_s());
    return 0;
}