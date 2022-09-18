#ifndef _FILEREADER_HPP_
#define _FILEREADER_HPP_

#include <Core/Logger.hpp>

#include <fstream>
#include <sstream>
#include <string>

class FileReader {
public:
  static void OpenFile(const char* fileName);
  static void CloseOpenedFile();

  static char* GetLineFromOpenedFile();

  static constexpr int READ_BUFF_SIZE = 256;
private:
  static inline char readBuff[READ_BUFF_SIZE];
  static inline std::ifstream openedFile;
};

inline void FileReader::OpenFile(const char* fileName) {
  if(openedFile.is_open()) {
    Logger::Warning("Trying to open file %s, while previous is stil open!", fileName);
    return;
  }
  openedFile.open(fileName, std::ios::in);
  if (!openedFile.is_open())
    Logger::Error("File %s could not be opened!", fileName);
}

inline void FileReader::CloseOpenedFile() {
  if(!openedFile.is_open()) {
    Logger::Warning("Trying to close file, but there is no opened file!");
    return;
  }
  openedFile.close();
}

char* FileReader::GetLineFromOpenedFile() {
  if (!openedFile.is_open()) return nullptr;

  std::string line;
  if(!std::getline(openedFile, line))  return nullptr;

  strcpy(readBuff, line.c_str());
  return readBuff;
}

#endif /* _FILEREADER_HPP_ */
