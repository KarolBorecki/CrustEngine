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
  MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/VideoShip.obj", &mesh);
  RenderObject rObj(0,0,0,&mesh);


  LoopMove rObjMove(&rObj, -2, 2, -3, 3, 3, 7, 1, 2, 3);
  Rotate rObjRotation(&rObj);
  rObj.AttachScript(&rObjMove);
  // rObj.AttachScript(&rObjRotation);

  Vector3 lightSourceDir(0.6, 0.2, -0.5);
  LightSource lightSource(255, &lightSourceDir);

  scene.AddObject(&rObj);
  scene.AddObject(&lightSource);

  scene.SetLightProjection(false);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();
  Logger::Info("================ENGINE DONE================");

  return 0;
}
