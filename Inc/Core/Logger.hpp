#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <cstdarg>
#include <cstring>
#include <cstdio>

class Logger {
public:
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

  enum FontStyle {
    NORMAL = 0,
    BOLD = 1
  };

  static void Error(const char* format, ...);
  static void Warning(const char* format, ...);
  static void Info(const char* format, ...);

  static void Log(const char* format, ...);

  static void SetFont(int colorCode, int styleCode);
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

inline void Logger::SetFont(int colorCode, int styleCode) {
  printf("\033[%dm", Logger::FontColor::WHITE);
  printf("\033[%dm", styleCode);
  printf("\033[%dm", colorCode);
}

inline void Logger::SetFont(int colorCode) {
  SetFont(colorCode, FontStyle::NORMAL);
}

#endif /* _LOGGER_HPP_ */
