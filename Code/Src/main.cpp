// #include <cstdlib> /* Plz no - atoi */

#include <Logging/Logger.hpp>
#include <iostream>

// #include <Core/Camera.hpp>
// #include <Core/Scene.hpp>
// #include <Core/Core.hpp>

// #include <Rendering/Mesh.hpp>
// #include <Rendering/Objects/Lightining/DirectionalLight.hpp>
// #include <Rendering/Objects/RenderObject.hpp>

// #include <Files/MeshLoader.hpp>

#include <Physics/Matrix.hpp>

// #include <Scripting/SampleScripts/LoopMove.hpp>
// #include <Scripting/SampleScripts/Rotate.hpp>

// TODO move all implementation to src files

void print_mat(Matrix<double> &mat)
{
  std::string result = "";
  result += "Matrix<" + std::to_string(mat.GetID()) + "> of size: " + std::to_string(mat.Height()) + "x" + std::to_string(mat.Width()) + "\n";
  if (mat.Height() * mat.Width() > 320)
    Logger::Error("Too big matrix");
  for (int r = 0; r < mat.Height(); r++)
  {
    for (int c = 0; c < mat.Width(); c++)
    {
      result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" + boost::lexical_cast<std::string>(mat[c][r]) + " ";
    }
    result += "\n";
  }
  Logger::Info("%s", result.c_str());
}

int main(int argc, char *argv[])
{
  // Camera cam(90, 0.1, 1000.0);
  // Scene scene("T Scene", &cam);

  // Mesh mesh("Sample mesh");

  // std::string name = argv[1];
  // std::string path = "/Users/karolborecki/Desktop/CrustEngine/meshes/" + name + ".obj";

  // MeshLoader::LoadMeshFromFile(path.c_str(), &mesh);
  // RenderObject rObj(&mesh);

  // LoopMove rObjMove(-100, 0, -100, 0, -100, 0, 10, 5, 7);
  // cam.AttachScript(&rObjMove);
  // // Rotate rObjRotation(&rObj);
  // // rObj.AttachScript(&rObjMove);
  // // rObj.AttachScript(&rObjRotation);

  // Vector3 lightSourceDir(0.6, 0.2, -0.5);
  // DirectionalLight dirLightSource(255, &lightSourceDir);

  // scene.AddObject(&rObj);
  // scene.AddObject(&dirLightSource);

  // scene.SetLightProjection(true);

  // Core core;
  // core.OpenNewWindow(1000, 800, &scene);

  // core.Quit();

  Matrix<double> t1(3, 3, 10.0);
  // t1[0][0] = 1;
  // t1[1][0] = 2;

  // t1[0][1] = 3;
  // t1[1][1] = 4;

  // t1[0][2] = 5;
  // t1[1][2] = 6;

  // print_mat(t1);

  Matrix<double> t2(3, 3, 2.0);
  // t2[0][0] = 6;
  // t2[1][0] = 5;
  // t2[2][0] = 4;

  // t2[0][1] = 3;
  // t2[1][1] = 2;
  // t2[2][1] = 1;

  // print_mat(t2);

  // print_mat(t1);
  // print_mat(t2);
  print_mat(t1 + t2);
  return 0;
}