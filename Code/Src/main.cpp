#include <cstdlib> /* Plz no - atoi */

#include <Logging/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Mesh.hpp>
#include <Rendering/Objects/RenderObject.hpp>

#include <Files/MeshLoader.hpp>

#include <Physics/Matrix.hpp>

#include <Scripting/SampleScripts/LoopMove.hpp>

int main(int argc, char* argv[])
{
  Logger::Info("================STARTING THE ENGINE================");
  Camera cam(90, 0.1, 1000.0);
  Scene scene("T Scene", &cam);

  Mesh mesh("Sample mesh");
  MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/meshT.txt", &mesh);
  RenderObject rObj(0,0,0,&mesh);

  // Mesh mesh2("Sample mesh2");
  // MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/meshT.txt", &mesh2);
  // RenderObject rObj2(atoi(argv[0]), atoi(argv[1]), atoi(argv[1]), &mesh2);

  LoopMove rObjMove(&rObj, 1, 2, 3, 3, 2, 1);
  rObj.AttachScript(&rObjMove);

  scene.AddObject(&rObj);
  //scene.AddObject(&rObj2);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();
  Logger::Info("================ENGINE DONE================");

  return 0;
}
