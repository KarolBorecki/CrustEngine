#ifndef _EXCEPTIONSHANDLER_HPP_
#define _EXCEPTIONSHANDLER_HPP_

#include <Logging/Logger.hpp>

/**
 * @brief 
 */
class ExceptionsHandler
{
public:
  static void ThrowError(const char* format, ...);
  static void ThrowWarning(const char* format, ...);
  
};

void ExceptionsHandler::ThrowError(const char* format, ...) {
  va_list args;
  Logger::Error(format, args);
  throw std::runtime_error("RenderWindow failed to initzialize");
}

void ExceptionsHandler::ThrowWarning(const char* format, ...) {
  va_list args;
  Logger::Warning(format, args);
}




#endif /* _EXCEPTIONSHANDLER_HPP_ */
