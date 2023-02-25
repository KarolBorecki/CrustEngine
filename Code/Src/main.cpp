#include <cstdlib> /* Plz no - atoi */

#include <Logging/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Mesh.hpp>
#include <Rendering/Objects/LightSource.hpp>
#include <Rendering/Objects/RenderObject.hpp>

#include <Files/MeshLoader.hpp>

#include <Physics/Matrix.hpp>

#include <Scripting/SampleScripts/LoopMove.hpp>
#include <Scripting/SampleScripts/Rotate.hpp>

int main(int argc, char* argv[])
{
  Logger::Info("================STARTING THE ENGINE================");
  Camera cam(90, 0.1, 1000.0);
  Scene scene("T Scene", &cam);

  Mesh mesh("Sample mesh");
  
  std::string name = argv[1];
  std::string path = "/Users/karolborecki/Desktop/CrustEngine/meshes/" + name + ".obj";
  
  MeshLoader::LoadMeshFromFile(path.c_str(), &mesh);
  RenderObject rObj(0,0,0,&mesh);


  LoopMove rObjMove(&rObj, -30, 10, -30, 20, -30, 30, 10, 10, 10);
  Rotate rObjRotation(&rObj);
  rObj.AttachScript(&rObjMove);
  // rObj.AttachScript(&rObjRotation);

  Vector3 lightSourceDir(0.6, 0.2, -0.5);
  LightSource lightSource(255, &lightSourceDir);

  scene.AddObject(&rObj);
  scene.AddObject(&lightSource);

  scene.SetLightProjection(true);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();
  Logger::Info("================ENGINE DONE================");

  return 0;
}
