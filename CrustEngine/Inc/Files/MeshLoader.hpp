#ifndef _MESHLOADER_HPP_
#define _MESHLOADER_HPP_

#include <fstream>
#include <string>
#include <vector>

#include <Logging/ExceptionsHandler.hpp>

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
   *   - *.obj <br>
   */
  static void LoadMeshFromFile(const char *fileName, Mesh *outMesh);

private:
  /**
   * @brief Reads mesh from *.obj file and saves it to Mesh object.
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
    ExceptionsHandler::ThrowWarning("No mathing file extension for file: %s - The mesh will not be loaded.", fileName);
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

  std::vector<double> points;

  int currentPoint = 0;
  int currentTri = 0;

  while (std::getline(file, line))
  {

    analysed_line = line.c_str();
    if (sscanf(analysed_line, "v %lf %lf %lf", &x, &y, &z) == 3)
    {
      points.push_back(x);
      points.push_back(y);
      points.push_back(z);
    }
    else if (sscanf(analysed_line, "vn %lf %lf %lf", &x, &y, &z) == 3)
    {
      // TODO mesh obj loader - usage for vn data
    }
    else if (sscanf(analysed_line, "vt %lf %lf %lf", &x, &y, &z) == 3)
    {
      // TODO mesh obj loader - usage for vt data
    }
    else if (sscanf(analysed_line, "f %d %d %d", &p1_index, &p2_index, &p3_index) == 3)
    {
      // TODO rework this
      outMesh->AddPolygon(*(new Polygon(points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2], // TODO make static polygon and pass it as copy
                                        points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2],
                                        points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2])));
    }
    else if (sscanf(analysed_line, "f %d/%d %d/%d %d/%d", &p1_index, &t1_index, &p2_index, &t2_index, &p3_index, &t3_index) == 6)
    {
      outMesh->AddPolygon(*(new Polygon(points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2],
                                        points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2],
                                        points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2])));
    }
    else if (sscanf(analysed_line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &p1_index, &t1_index, &n1_index, &p2_index, &t2_index, &n2_index, &p3_index, &t3_index, &n3_index) == 9)
    {
      outMesh->AddPolygon(*(new Polygon(points[(p1_index - 1) * 3], points[(p1_index - 1) * 3 + 1], points[(p1_index - 1) * 3 + 2],
                                        points[(p2_index - 1) * 3], points[(p2_index - 1) * 3 + 1], points[(p2_index - 1) * 3 + 2],
                                        points[(p3_index - 1) * 3], points[(p3_index - 1) * 3 + 1], points[(p3_index - 1) * 3 + 2])));
    }
    else if (sscanf(analysed_line, "usemtl %s", str) == 1)
    {
      // TODO mesh obj loader - usage for usemtl data
    }
    else if (sscanf(analysed_line, "s %s", str) == 1)
    {
      // TODO mesh obj loader - usage for s off
    }
    else
    {
      ExceptionsHandler::ThrowWarning("No matching rule for line: %s in obj's file %s", analysed_line, fileName);
    }
  }
}

#endif /* _MESHLOADER_HPP_ */
