#include <Core/Logger.hpp>

#include <Core/Camera.hpp>
#include <Core/Scene.hpp>
#include <Core/Core.hpp>

#include <Rendering/Objects/RenderObject.hpp>

#include <Physics/Matrix.hpp>

int main(int argc, char* argv[])
{
  Logger::Log("Vec3 test");
  Vector3 vec1(1, 2, 3);
  Logger::Log(vec1.ToString().c_str());

  Matrix vec2(3, 3);
  vec2.PutValue(0,0,1);
  vec2.PutValue(0,1,2);
  vec2.PutValue(0,2,3);
  vec2.PutValue(1,0,4);
  vec2.PutValue(1,1,5);
  vec2.PutValue(1,2,6);
  vec2.PutValue(2,0,7);
  vec2.PutValue(2,1,8);
  vec2.PutValue(2,2,9);
  Logger::Log(vec2.ToString().c_str());

  Matrix result = Matrix::Multiply(&vec1, &vec2);
  Logger::Log(result.ToString().c_str());

  Camera cam(90, 0.1, 100.0);
  Scene scene("T Scene", &cam);

  Logger::Info("Creating Mesh");
  Mesh mesh;
  // Represents the cube
  mesh.triangles = {
    // SOUTH
    {new Vector3(0.0,0.0,0.0), new Vector3(0.0,1.0,0.0), new Vector3(1.0,1.0,0.0)},
    {new Vector3(0.0,0.0,0.0), new Vector3(1.0,1.0,0.0), new Vector3(1.0,0.0,0.0)},
    // EAST
    {new Vector3(1.0,0.0,0.0), new Vector3(1.0,1.0,0.0), new Vector3(1.0,1.0,1.0)},
    {new Vector3(1.0,0.0,0.0), new Vector3(1.0,1.0,1.0), new Vector3(1.0,0.0,1.0)},
    // NORTH
    {new Vector3(1.0,0.0,1.0), new Vector3(1.0,1.0,1.0), new Vector3(0.0,1.0,1.0)},
    {new Vector3(1.0,0.0,1.0), new Vector3(0.0,1.0,1.0), new Vector3(0.0,0.0,1.0)},
    // WEST
    {new Vector3(0.0,0.0,1.0), new Vector3(0.0,1.0,1.0), new Vector3(0.0,1.0,0.0)},
    {new Vector3(0.0,0.0,1.0), new Vector3(0.0,1.0,0.0), new Vector3(0.0,0.0,0.0)},
    // TOP
    {new Vector3(0.0,1.0,0.0), new Vector3(0.0,1.0,1.0), new Vector3(1.0,1.0,1.0)},
    {new Vector3(0.0,1.0,0.0), new Vector3(1.0,1.0,1.0), new Vector3(1.0,1.0,0.0)},
    // BOTTOM
    {new Vector3(1.0,0.0,1.0), new Vector3(0.0,0.0,1.0), new Vector3(0.0,0.0,0.0)},
    {new Vector3(1.0,0.0,1.0), new Vector3(0.0,0.0,0.0), new Vector3(1.0,0.0,0.0)},
  };
  Logger::Info("Mesh created");

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

  core.Quit();
  return 0;
}
