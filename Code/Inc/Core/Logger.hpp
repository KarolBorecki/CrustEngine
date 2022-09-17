#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <cstdarg>
#include <cstring>
#include <cstdio>

/**
* @brief Static class allowing to log with certain color and style on classic console with well-known printf() arguments.
*/
class Logger {
public:
  /**
  * Enumeration representing console color codes.
  */
  enum FontColor {
    WHITE = 0,
    GREY = 37,
    LIGHT_BLUE = 36,
    PINK = 35,
    BLUE = 34,
    RED = 31,
    YELLOW = 33,
    GREEN = 32
  };

  /**
  * Enumeration representing console font styles codes.
  */
  enum FontStyle {
    NORMAL = 0,
    BOLD = 1
  };

  /**
  * @brief Logs onto the console in red color.
  */
  static void Error(const char* format, ...);
  /**
  * @brief Logs onto the console in yellow color.
  */
  static void Warning(const char* format, ...);
  /**
  * @brief Logs onto the console in blue color.
  */
  static void Info(const char* format, ...);

  /**
  * @brief Logs onto the console.
  */
  static void Log(const char* format, ...);
  /**
  * @brief Logs onto the console in colorCode color.
  */
  static void Log(int colorCode, const char* format, ...);

  /**
  * @brief Sets console color to colorCode and console font style to styleCode;
  */
  static void SetFont(int colorCode, int styleCode);
  /**
  * @brief Sets console color to colorCode.
  */
  static void SetFont(int colorCode);
};


inline void Logger::Error(const char* format, ...) {
  SetFont(Logger::FontColor::RED);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  printf("\n");
  va_end(args);
  SetFont(FontColor::WHITE);
}

inline void Logger::Warning(const char* format, ...) {
  SetFont(FontColor::YELLOW);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  printf("\n");
  va_end(args);
  SetFont(FontColor::WHITE);
}

inline void Logger::Info(const char* format, ...) {
  SetFont(FontColor::BLUE);
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  printf("\n");
  va_end(args);
  SetFont(FontColor::WHITE);
}

inline void Logger::Log(const char* format, ...){
    SetFont(FontColor::WHITE);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

inline void Logger::Log(int colorCode, const char* format, ...){
    SetFont(colorCode);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
    SetFont(FontColor::WHITE);
}

inline void Logger::SetFont(int colorCode, int styleCode) {
  printf("\033[%dm", Logger::FontColor::WHITE);
  printf("\033[%dm", styleCode);
  printf("\033[%dm", colorCode);
}

inline void Logger::SetFont(int colorCode) {
  SetFont(colorCode, FontStyle::NORMAL);
}

#endif /* _LOGGER_HPP_ */
