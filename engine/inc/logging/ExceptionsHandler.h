#ifndef CRUSTENGINE_EXCEPTIONHANDLER_H
#define CRUSTENGINE_EXCEPTIONHANDLER_H

#include <stdexcept>

#include "logging/Logger.h"

namespace Crust
{
    /**
     * @brief Crust engine exception's wrapper. This static class allows us to throw errors and warnings at anytime.
     */
    class ExceptionsHandler
    {
    public:
        /**
         * @brief Throws an error and ends the engine work immedietly. It also prints message in red color on the console.
         *
         * @param p_format - message format in c-style.
         * @param ...  - format args.
         */
        static void throwError(const char* p_format, ...);

        /**
         * @brief Throws a warning. It also prints message in yellow color on the console.
         *
         * @param p_format - message format in c-style.
         * @param ...  - format args.
         */
        static void throwWarning(const char* p_format, ...);
    };
}

#endif /* CRUSTENGINE_EXCEPTIONHANDLER_H */
