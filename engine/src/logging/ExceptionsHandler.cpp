#include "logging/ExceptionsHandler.h"

namespace Crust
{
    void ExceptionsHandler::throwError(const char* p_format, ...) {
        va_list args;
        Logger::error(p_format, args);
        throw std::runtime_error("");
    }

    void ExceptionsHandler::throwWarning(const char* p_format, ...) {
        va_list args;
        Logger::warning(p_format, args);
    }
}
