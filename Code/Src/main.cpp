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
  Logger::Log(Logger::FontColor::LIGHT_BLUE, "================STARTING THE ENGINE================");
  Camera cam(90, 0.1, 1000.0);
  Scene scene("T Scene", &cam);

  Mesh mesh("Sample mesh");
  MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/mesh45deg.txt", &mesh);
  RenderObject rObj(&mesh);

  Mesh mesh2("Sample mesh2");
  MeshLoader::LoadMeshFromFile("/Users/karolborecki/Desktop/CrustEngine/mesh.txt", &mesh2);
  RenderObject rObj2(&mesh2);

  //scene.AddObject(rObj);
  scene.AddObject(rObj2);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);

  core.Quit();
  return 0;
}
