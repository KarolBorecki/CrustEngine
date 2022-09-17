#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Objects/RenderObject.hpp>

#include <Physics/Matrix.hpp>

int main(int argc, char* argv[])
{

  Camera cam(90, 0.1, 100.0);
  Scene scene("Test Scene", &cam);

/*  Mesh mesh;
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
*/
  Core core;
  core.OpenNewWindow(1000, 800, &scene);

/*
  Matrix m(2, 2);
  m.PutValue(0,0,1);
  m.PutValue(0,1,2);
  m.PutValue(1,0,3);
  m.PutValue(1,1,4);
  Logger::Log(m.ToString().c_str());

  Matrix m2(2, 2);
  m2.PutValue(0,0,5);
  m2.PutValue(0,1,6);
  m2.PutValue(1,0,7);
  m2.PutValue(1,1,8);
  Logger::Log(m2.ToString().c_str());

  Matrix result = Matrix::Multiply(&m, &m2);
  Logger::Log(result.ToString().c_str());
*/
core.CloseAllWindows();
  return 0;
}
