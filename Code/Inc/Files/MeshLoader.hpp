#ifndef _MESHLOADER_HPP_
#define _MESHLOADER_HPP_

#include <string.h>

#include <Files/FileReader.hpp>

// TODO add detection to file extensions

/**
* @brief Class used to read meshes from *.obj file
*/
class MeshLoader {
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
  static void LoadMeshFromFile(const char* fileName, Mesh* outMesh);

private:
  /**
  * @brief Reads mesh from *.obj file and returns Mesh object.
  *
  * @details Opens file of #filename, reads the content in *.obj convention and creates Mesh object.
  * Before returning it closes the opened file.
  *
  * @sa FileReader.hpp <a href="https://en.wikipedia.org/wiki/Wavefront_.obj_file">*.obj file extensions</a>
  */
  static void ReadFromObj(const char* fileName, Mesh* outMesh);
  /**
  * @brief Reads mesh from *.txt file and returns Mesh object.
  *
  * @details Opens file of #filename, reads the content in CrustEngine's convention and creates Mesh object.
  * Before returning it closes the opened file. <br>
  * The CrustEngine convention of mesh file is: <br>
  * 3 vectors per line in pattern: [%lf, %lf, %lf;] <br>
  * Each line represent a mesh's triangle. The example file can bee seen in /mesh.txt. It represents a cube.
  *
  * @sa FileReader.hpp <a href="https://en.wikipedia.org/wiki/Wavefront_.obj_file">*.obj file extensions</a>
  */
  static void ReadFromTxt(const char* fileName, Mesh* outMesh);
};

void MeshLoader::LoadMeshFromFile(const char* fileName, Mesh* outMesh) {
  uint8_t fileNameLen = strlen(fileName);

  if(fileName[fileNameLen-1] == 'j' && fileName[fileNameLen-2] == 'b' && fileName[fileNameLen-3] == 'o' && fileName[fileNameLen-4] == '.')
    ReadFromObj(fileName, outMesh);
  else if(fileName[fileNameLen-1] == 't' && fileName[fileNameLen-2] == 'x' && fileName[fileNameLen-3] == 't' && fileName[fileNameLen-4] == '.')
    ReadFromTxt(fileName, outMesh);
  else
    Logger::Error("No mathing file extension for file: %s", fileName);
}

//TODO Need to figure out how to converte vertex to triangles
void MeshLoader::ReadFromObj(const char* fileName, Mesh* outMesh) {
  FileReader::OpenFile(fileName);

  char materialName[256];
  char objectName[256];
  FileReader::GetLineFromOpenedFile(1, "mtllib %s\n", materialName);
  FileReader::GetLineFromOpenedFile(1, "o %s\n", objectName);

  Logger::Log(Logger::FontColor::LIGHT_BLUE, "Reading *.obj file: %s, with mtl name: %s", objectName, materialName);

  char vertexType[3] = {'\0'};
  double d1=1.0,d2=1.0,d3=1.0;
  while (FileReader::GetLineFromOpenedFile(1, "%s", vertexType) > 0) {
    if(vertexType[0] == 'v' && vertexType[1] == '\0') {
      FileReader::GetLineFromOpenedFile(3, " %lf %lf %lf\n", &d1, &d2, &d3);
      Logger::Log(Logger::FontColor::LIGHT_BLUE, "%s: %lf, %lf, %lf", vertexType, d1, d2, d3);
    }
    else if(vertexType[0] == 'v' && vertexType[1] == 't') {
      FileReader::GetLineFromOpenedFile(2, " %lf %lf\n", &d1, &d2);
      Logger::Log(Logger::FontColor::LIGHT_BLUE, "%s: %lf, %lf", vertexType, d1, d2);
    }
    else if(vertexType[0] == 'v' && vertexType[1] == 'n') {
      FileReader::GetLineFromOpenedFile(3, " %lf %lf %lf\n", &d1, &d2, &d3);
      Logger::Log(Logger::FontColor::LIGHT_BLUE, "%s: %lf, %lf, %lf", vertexType, d1, d2, d3);
    }
  }

  FileReader::CloseOpenedFile();
}

void MeshLoader::ReadFromTxt(const char* fileName, Mesh* outMesh) {
  FileReader::OpenFile(fileName);
  outMesh->SetName(fileName);

  double d1,d2,d3,d4,d5,d6,d7,d8,d9;
  while (FileReader::GetLineFromOpenedFile(9, "%lf, %lf, %lf; %lf, %lf, %lf; %lf, %lf, %lf;", &d1, &d2, &d3, &d4, &d5, &d6, &d7, &d8, &d9) == 9) {
    Vector3* v1 = new Vector3(d1, d2, d3);
    Vector3* v2 = new Vector3(d4, d5, d6);
    Vector3* v3 = new Vector3(d7, d8, d9);
    Triangle* tri = new Triangle(v1, v2, v3);
    outMesh->AddTriangle(tri);
  }
  Logger::Log("Mesh %s loading done.", outMesh->GetName().c_str());
  FileReader::CloseOpenedFile();
}

#endif /* _MESHLOADER_HPP_ */
