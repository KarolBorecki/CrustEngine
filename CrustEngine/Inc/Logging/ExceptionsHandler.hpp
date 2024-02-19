#ifndef _EXCEPTIONSHANDLER_HPP_
#define _EXCEPTIONSHANDLER_HPP_

#include <stdexcept>

#include <Logging/Logger.hpp>

/**
 * @brief Crust engine exception's wrapper. This static class allows us to throw errors and warnings at anytime.
 */
class ExceptionsHandler
{
public:
/**
 * @brief Throws an error and ends the engine work immedietly. It also prints message in red color on the console.
 * 
 * @param format - message format in c-style.
 * @param ...  - format args.
 */
  static void ThrowError(const char* format, ...);

/**
 * @brief Throws a warning. It also prints message in yellow color on the console.
 * 
 * @param format - message format in c-style.
 * @param ...  - format args.
 */
  static void ThrowWarning(const char* format, ...);
  
};

void ExceptionsHandler::ThrowError(const char* format, ...) {
  va_list args;
  Logger::Error(format, args);
  throw std::runtime_error("");
}

void ExceptionsHandler::ThrowWarning(const char* format, ...) {
  va_list args;
  Logger::Warning(format, args);
}




#endif /* _EXCEPTIONSHANDLER_HPP_ */
