#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Mesh.hpp>
#include <Rendering/Objects/RenderObject.hpp>

#include <Files/MeshLoader.hpp>

#include <Physics/Matrix.hpp>

int main(int argc, char* argv[])
{
  Camera cam(90, 0.1, 100.0);
  Scene scene("T Scene", &cam);

  Mesh mesh = MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/mesh.txt");
  RenderObject rObj(&mesh);
  Logger::Log("%s", rObj.ToString().c_str());

  scene.AddObject(rObj);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();
  return 0;
}
