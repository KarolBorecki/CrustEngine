#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Objects/RenderObject.hpp>

#include <Files/FileReader.hpp>

#include <Physics/Matrix.hpp>

int main(int argc, char* argv[])
{
  //Camera cam(90, 0.1, 100.0);
  //Scene scene("T Scene", &cam);


  Logger::Info("Creating Mesh");
  Mesh mesh;
  // Represents the cube
  Vector3 v1(0.0,0.0,0.0);
  Logger::Error("Vector observed: Vector3<%d>", v1.GetID());
  // TODO the objects are deleted after function call ends!
  mesh.triangles.push_back({v1,  Vector3(0.0,1.0,0.0),  Vector3(1.0,1.0,0.0)});
  mesh.triangles.push_back({ Vector3(0.0,0.0,0.0),  Vector3(1.0,1.0,0.0),  Vector3(1.0,0.0,0.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,0.0),  Vector3(1.0,1.0,0.0),  Vector3(1.0,1.0,1.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,0.0),  Vector3(1.0,1.0,1.0),  Vector3(1.0,0.0,1.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,1.0),  Vector3(1.0,1.0,1.0),  Vector3(0.0,1.0,1.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,1.0),  Vector3(0.0,1.0,1.0),  Vector3(0.0,0.0,1.0)});
  mesh.triangles.push_back({ Vector3(0.0,0.0,1.0),  Vector3(0.0,1.0,1.0),  Vector3(0.0,1.0,0.0)});
  mesh.triangles.push_back({ Vector3(0.0,0.0,1.0),  Vector3(0.0,1.0,0.0),  Vector3(0.0,0.0,0.0)});
  mesh.triangles.push_back({ Vector3(0.0,1.0,0.0),  Vector3(0.0,1.0,1.0),  Vector3(1.0,1.0,1.0)});
  mesh.triangles.push_back({ Vector3(0.0,1.0,0.0),  Vector3(1.0,1.0,1.0),  Vector3(1.0,1.0,0.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,1.0),  Vector3(0.0,0.0,1.0),  Vector3(0.0,0.0,0.0)});
  mesh.triangles.push_back({ Vector3(1.0,0.0,1.0),  Vector3(0.0,0.0,0.0),  Vector3(1.0,0.0,0.0)});

  Logger::Info("Mesh created");
  RenderObject rObj(&mesh);
  //Logger::Warning("Mesh: %f", rObj.GetMesh()->triangles[0].point[0].X());

  //Core core;
  //core.OpenNewWindow(1000, 800, &scene);

  //core.Quit();
  return 0;
}
