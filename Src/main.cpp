#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Objects/RenderObject.hpp>

int main(int argc, char* argv[])
{
  Camera cam(0.5);
  Scene scene("Test Scene", &cam);

  Mesh mesh;
  // Represents the cube
  mesh.triangles = {
    // SOUTH
    {Vector3(0.0,0.0,0.0), Vector3(0.0,1.0,0.0), Vector3(1.0,1.0,0.0)},
    {Vector3(0.0,0.0,0.0), Vector3(1.0,1.0,0.0), Vector3(1.0,0.0,0.0)},
    // EAST
    {Vector3(1.0,0.0,0.0), Vector3(1.0,1.0,0.0), Vector3(1.0,1.0,1.0)},
    {Vector3(1.0,0.0,0.0), Vector3(1.0,1.0,1.0), Vector3(1.0,0.0,1.0)},
    // NORTH
    {Vector3(1.0,0.0,1.0), Vector3(1.0,1.0,1.0), Vector3(0.0,1.0,1.0)},
    {Vector3(1.0,0.0,1.0), Vector3(0.0,1.0,1.0), Vector3(0.0,0.0,1.0)},
    // WEST
    {Vector3(0.0,0.0,1.0), Vector3(0.0,1.0,1.0), Vector3(0.0,1.0,0.0)},
    {Vector3(0.0,0.0,1.0), Vector3(0.0,1.0,0.0), Vector3(0.0,0.0,0.0)},
    // TOP
    {Vector3(0.0,1.0,0.0), Vector3(0.0,1.0,1.0), Vector3(1.0,1.0,1.0)},
    {Vector3(0.0,1.0,0.0), Vector3(1.0,1.0,1.0), Vector3(1.0,1.0,0.0)},
    // BOTTOM
    {Vector3(1.0,0.0,1.0), Vector3(0.0,0.0,1.0), Vector3(0.0,0.0,0.0)},
    {Vector3(1.0,0.0,1.0), Vector3(0.0,0.0,0.0), Vector3(1.0,0.0,0.0)},
  };
  RenderObject object1(mesh);
  scene.AddObject(object1);

  Core core;
  core.OpenNewWindow(1000, 800, &scene);
  
  return 0;
}
