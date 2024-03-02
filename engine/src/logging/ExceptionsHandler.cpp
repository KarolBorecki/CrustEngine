#include "logging/ExceptionsHandler.h"

namespace Crust
{
    void ExceptionsHandler::throwError(const char* p_format, ...) {
        va_list args;
        printf("\033[%dm", Logger::FontColor::RED);
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        throw std::runtime_error("");
    }

    void ExceptionsHandler::throwWarning(const char* p_format, ...) {
        va_list args;
        printf("\033[%dm", Logger::FontColor::YELLOW);
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
    }
}
