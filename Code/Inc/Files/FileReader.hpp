#ifndef _FILEREADER_HPP_
#define _FILEREADER_HPP_

#include <Core/Logger.hpp>

#include <cstdarg>
#include <cstring>
#include <cstdio>


/**
* @brief Static class used to read datat from file in classic-printf format.
*/
class FileReader {
public:
  /**
  * @brief Method opens file with #fileName.
  *
  * @details Method opens file and assigns it to #openedFile field.
  * If file with passed path does not exit it throws a warning and exits the method.
  * If file could not be opened it thows a warning and exists the method.
  *
  * @param fileName New opened file path.
  */
  static void OpenFile(const char* fileName);
  /**
  * @brief Method closes #openedFile.
  *
  * @details Method closes #openedFile.
  * If #openedFile is NULL then throws a warning and exits the method.
  */
  static void CloseOpenedFile();

  /**
  * @brief Classic printf format-style function for reading #openedFile.
  *
  * @details Method reads from #openedFile using vfscanf and assigns the values accordingly to #format and args passed.
  *
  * @param format Format for reading the file. <a href="https://pl.wikibooks.org/wiki/C/printf">Read more.</a>
  * @param ... Pointers to next variables accordingly to #format.
  */
  static uint8_t GetLineFromOpenedFile(uint8_t expectedArgsCount, const char* format, ...);

  /**
  * @brief Getter for #openedFile handler.
  *
  * @return #openedFile field.
  */
  static FILE* GetOpenedFileHanlder();
private:
  static inline FILE* openedFile; //!< Currently opened file's handler.
};

inline void FileReader::OpenFile(const char* fileName) {
  if(openedFile != NULL) {
    Logger::Warning("Trying to open file %s, while previous is stil open!", fileName);
    return;
  }
  openedFile = fopen(fileName, "r");
  if (openedFile == NULL)
    Logger::Error("File %s could not be opened!", fileName);
}

inline void FileReader::CloseOpenedFile() {
  if(openedFile == NULL) {
    Logger::Warning("Trying to close file, but there is no opened file!");
    return;
  }
  fclose(openedFile);
}

uint8_t FileReader::GetLineFromOpenedFile(uint8_t expectedArgsCount, const char *format, ...)
{
  if (openedFile == NULL) {
    Logger::Warning("Trying to read file, but there is no opened file!");
    return 0;
  }
  va_list args;
  va_start(args, format);
  uint8_t count = vfscanf(openedFile, format, args);
  if(expectedArgsCount != count) return 0;
  va_end(args);

  return count;
}

inline FILE* FileReader::GetOpenedFileHanlder() { return openedFile; }

#endif /* _FILEREADER_HPP_ */
