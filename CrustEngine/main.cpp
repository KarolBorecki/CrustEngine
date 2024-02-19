#include <Logging/Logger.hpp>

#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Objects/Camera.hpp>
#include <Objects/Lightining/DirectionalLight.hpp>
#include <Objects/RenderObject.hpp>

#include <Rendering/Mesh.hpp>

#include <Files/MeshLoader.hpp>

#include <Math/Matrix.hpp>

#include <Scripting/SampleScripts/LoopMove.hpp>
#include <Scripting/SampleScripts/Mover.hpp>
#include <Scripting/SampleScripts/Rotator.hpp>
#include <Scripting/SampleScripts/Scaler.hpp>
#include <Scripting/SampleScripts/Spinner.hpp>

#include <iostream>
#include <Eigen/Dense>

// TODO implement toStrings - it is usefull at last
// TODO add SDL as submodule of a git repository - z modułami trzeba klonować git clone --recursive <URL>
// TODO change private variables names to '_<varname>'
// TODO learn abou cpp compilers
// TODO typeof is only for gcc, use deltype
// TODO create asset manager so we do not hgave to load files repeatedly
// TODO pass const& if possible - what does const keyword mean in method's variable? and what is const in method body?
// todo implement talising
int main(int argc, char *argv[])
{
    // Logger::Info("Engine Start");

    // Camera cam(90, 0.1, 1000.0);
    // cam.GetTransform().SetPosition(-4, -5, -10);
    // cam.GetTransform().SetEulerRotation(0, 0, 1);
    // Logger::Info("Camera created.");

    // Scene scene("T Scene", cam);
    // Logger::Info("Scene created.");

    // Mesh mesh("Sample mesh");
    // std::string name = argv[1];
    // std::string path = "/Users/karolborecki/Desktop/CrustEngine/CrustEngine/Tmp/meshes/" + name + ".obj";
    // MeshLoader::LoadMeshFromFile(path.c_str(), &mesh);
    // Logger::Info("Mesh '%s' loaded.", mesh.GetName().c_str());
    // RenderObject rObj(mesh);
    // rObj.GetTransform().SetPosition(0, 0, 12.0f);

    // Mesh mesh2("Sample mesh");
    // std::string path2 = "/Users/karolborecki/Desktop/CrustEngine/CrustEngine/Tmp/meshes/teapot.obj";
    // MeshLoader::LoadMeshFromFile(path2.c_str(), &mesh2);
    // Logger::Info("Mesh '%s' loaded.", mesh2.GetName().c_str());
    // RenderObject rObj2(mesh2);
    // rObj2.GetTransform().SetPosition(-5, 10, 8.0f);

    // Logger::Info("Render object created.");

    // Mover mover(14, 14, 14);
    // Mover mover2(15, 15, 15);
    // Rotator rotator(1.8f);
    // Scaler scaler(0.9f);
    // Spinner spinner(1.0f, 0.5f, 0.8f);

    // rObj.AttachScript(mover);
    // //rObj2.AttachScript(mover2);
    // rObj.AttachScript(rotator);
    // rObj.AttachScript(scaler);

    // // rObj.AttachScript(spinner);

    // Vector3 lightSourceDir(0.4f, -0.3f, -0.89f);
    // DirectionalLight dirLightSource(LightSource::INTENSIVITY_BRIGHT, lightSourceDir);

    // Logger::Info("Light source created.");
    // scene.AddObject(rObj);
    // // scene.AddObject(rObj2);
    // scene.AddObject(dirLightSource);

    // scene.SetLightProjection(true);

    // Logger::Info("Objectes added to the scene.");
    // Core core;
    // core.OpenNewWindow(800, 500, scene);
    // core.Quit();
    // Logger::Info("Engine work time: %lf [s]", TimeProvider::GetTime_s());

    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    return 0;
}