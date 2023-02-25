#ifndef _MESHLOADER_HPP_
#define _MESHLOADER_HPP_

#include <fstream>
#include <string>
#include <vector>

/**
 * @brief Class used to read meshes from *.obj file
 */
class MeshLoader
{
public:
  /**
   * @brief Saves mesh saved in #outMesh from passed file's path.
   *
   * @details Recognizes the file's extension by 4 last characters and calls MeshLoader::ReadFromObj or MeshLoader::ReadFromTxt method.
   * If no match for file extension was found then logs an error and returns blank mesh. <br>
   * Supported file extensions: <br>
   *   - *.txt <br>
   *   - *.obj <br>
   */
  static void LoadMeshFromFile(const char *fileName, Mesh *outMesh);

private:
  /**
   * @brief Reads mesh from *.obj file and returns Mesh object.
   *
   * @details Opens file of #filename, reads the content in *.obj convention and creates Mesh object.
   * Before returning it closes the opened file.
   *
   * @sa FileReader.hpp <a href="https://en.wikipedia.org/wiki/Wavefront_.obj_file">*.obj file extensions</a>
   */
  static void ParseObjToMesh(const char *fileName, Mesh *outMesh);

};

void MeshLoader::LoadMeshFromFile(const char *fileName, Mesh *outMesh)
{
  uint8_t fileNameLen = strlen(fileName);

  if (fileName[fileNameLen - 1] == 'j' && fileName[fileNameLen - 2] == 'b' && fileName[fileNameLen - 3] == 'o' && fileName[fileNameLen - 4] == '.')
    ParseObjToMesh(fileName, outMesh);
  else
    Logger::Error("No mathing file extension for file: %s", fileName);
}

void MeshLoader::ParseObjToMesh(const char *fileName, Mesh *outMesh)
{
  std::ifstream file(fileName);
  std::string line;
  const char *analysed_line;

  char str[256];
  double x = 1.0, y = 1.0, z = 1.0;             // Points values
  int p1_index = 1, p2_index = 1, p3_index = 1; // Points indexes
  int t1_index = 1, t2_index = 1, t3_index = 1; // Textures indexes
  int n1_index = 1, n2_index = 1, n3_index = 1; // Normals indexes

  std::vector<Vector3*> points;
  std::vector<Triangle*> tri;

  int currentPoint = 0;
  int currentTri = 0;

  while (std::getline(file, line))
  {

    analysed_line = line.c_str();
    Logger::Log("NOWA LINIA: %s", analysed_line);

    if (sscanf(analysed_line, "v %lf %lf %lf", &x, &y, &z) == 3)
    {
      points.push_back(new Vector3(x, y, z));
      Logger::Log(Logger::LIGHT_BLUE, "V -> %lf, %lf, %lf", x, y, z);
    }
    else if (sscanf(analysed_line, "vn %lf %lf %lf", &x, &y, &z) == 3)
    {
      Logger::Log(Logger::LIGHT_BLUE, "VN -> "); // TODO
    }
    else if (sscanf(analysed_line, "vt %lf %lf %lf", &x, &y, &z) == 3)
    {
      Logger::Log(Logger::LIGHT_BLUE, "VT -> "); // TODO
    }
    else if (sscanf(analysed_line, "f %d %d %d", &p1_index, &p2_index, &p3_index) == 3)
    {
      Logger::Log(Logger::LIGHT_BLUE, "F -> %d, %d, %d", p1_index, p2_index, p3_index);
      tri.push_back(new Triangle(points[p1_index - 1], points[p2_index - 1], points[p3_index - 1]));
    }
    else if (sscanf(analysed_line, "f %d/%d %d/%d %d/%d", &p1_index, &t1_index, &p2_index, &t2_index, &p3_index, &t3_index) == 6)
    {
      Logger::Log(Logger::LIGHT_BLUE, "F -> %d/%d, %d/%d, %d/%d", p1_index, t1_index, p2_index, t2_index, p3_index, t3_index);
      tri.push_back(new Triangle(points[p1_index - 1], points[p2_index - 1], points[p3_index - 1]));
    }
    else if (sscanf(analysed_line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &p1_index, &t1_index, &n1_index, &p2_index, &t2_index, &n2_index, &p3_index, &t3_index, &n3_index) == 9)
    {
      Logger::Log(Logger::LIGHT_BLUE, "F -> %d/%d/%d, %d/%d/%d, %d/%d/%d", p1_index, t1_index, n1_index, p2_index, t2_index, n2_index, p3_index, t3_index, n3_index);
      tri.push_back(new Triangle(points[p1_index - 1], points[p2_index - 1], points[p3_index - 1]));
    }
    else if (sscanf(analysed_line, "usemtl %s", str) == 1)
    {
      Logger::Log(Logger::LIGHT_BLUE, "usemtl -> %s", str);
    }
    else if (sscanf(analysed_line, "s %s", str) == 1)
    {
      Logger::Log(Logger::LIGHT_BLUE, "s -> %s", str);
    }
  }
  Logger::Log(Logger::LIGHT_BLUE, "Reading mesh end.");

  for (int i = 0; i < tri.size(); i++)
  {
    Logger::Log(Logger::FontColor::LIGHT_BLUE, "Adding tri: %d", i);
    outMesh->AddTriangle(tri.at(i));
  }
}

#endif /* _MESHLOADER_HPP_ */
