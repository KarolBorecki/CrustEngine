#include <cstdlib> /* Plz no - atoi */

#include <Logging/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Mesh.hpp>
#include <Rendering/Objects/Lightining/DirectionalLight.hpp>
#include <Rendering/Objects/RenderObject.hpp>

#include <Files/MeshLoader.hpp>

#include <Physics/Matrix.hpp>

#include <Scripting/SampleScripts/LoopMove.hpp>
#include <Scripting/SampleScripts/Rotate.hpp>

int main(int argc, char* argv[])
{
  Camera cam(90, 0.1, 1000.0);
  Scene scene("T Scene", &cam);

  Mesh mesh("Sample mesh");
  
  std::string name = argv[1];
  std::string path = "/Users/karolborecki/Desktop/CrustEngine/meshes/" + name + ".obj";

  MeshLoader::LoadMeshFromFile(path.c_str(), &mesh);
  RenderObject rObj(&mesh);

  LoopMove rObjMove(-100, 0, -100, 0, -100, 0, 10, 5, 7);
  cam.AttachScript(&rObjMove);
  // Rotate rObjRotation(&rObj);
  // rObj.AttachScript(&rObjMove);
  // rObj.AttachScript(&rObjRotation);

  Vector3 lightSourceDir(0.6, 0.2, -0.5);
  DirectionalLight dirLightSource(255, &lightSourceDir);

  scene.AddObject(&rObj);
  scene.AddObject(&dirLightSource);

  scene.SetLightProjection(true);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();

  return 0;
}