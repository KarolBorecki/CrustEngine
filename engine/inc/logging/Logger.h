#ifndef CRUSTENGINE_LOGGER_H
#define CRUSTENGINE_LOGGER_H

#include <cstdarg>
#include <cstring>
#include <cstdio>

namespace Crust {
    /**
     * @brief Static class allowing to log with certain color and style on classic console with well-known printf() arguments.
     */
    class Logger
    {
    public:
        /**
         * @brief representing console color codes.
         */
        enum FontColor
        {
            WHITE = 0,
            GREY = 37,
            LIGHT_BLUE = 36,
            PINK = 35,
            GREEN = 32,
            BLUE = 34,  /* RESERVED FOR INFOS */
            RED = 31,   /* RESERVED FOR WARNINGS */
            YELLOW = 33 /* RESERVED FOR ERRORS */
        };

        /**
         * @brief Enumeration representing console font styles codes.
         */
        enum FontStyle
        {
            NORMAL = 0,
            BOLD = 1
        };

        /**
         * @brief Logs onto the console in red color.
         */
        static void error(const char *p_format, ...);
        /**
         * @brief Logs onto the console in yellow color.
         */
        static void warning(const char *p_format, ...);
        /**
         * @brief Logs onto the console in blue color.
         */
        static void info(const char *p_format, ...);

        /**
         * @brief Prints empty line onto the console.
         */
        static void log();

        /**
         * @brief Logs onto the console with standard printf-like interface.
         */
        static void log(const char *p_format, ...);

        /**
         * @brief Logs onto the console in specified colorCode color.
         */
        static void log(int p_color_code, const char *p_format, ...);

        /**
         * @brief Logs onto the console.
         */
        static void logInline(const char *p_format, ...);
//
//        /**
//         * @brief Logs core info onto the console.
//         */
//        static void log(Core& core) {
//            log("Core info:");
//            for (auto& window : core.getWindows()) {
//                if(window != nullptr)
//                    log(*window);
//            }
//        }
//
//        /**
//         * @brief Logs window info onto the console.
//         */
//        static void log(const Window& window) { // TODO: Add more info about window
//            log("Window[%d, %d]: %s", window.width(), window.height(), (window.scene() == nullptr ? "-" : window.scene()->getName()));
//        }
//
//        /**
//         * @brief Logs matrix onto the console.
//         */
//        template<class T, int H, int W>
//        static void log(const char* p_info, const Matrix<T, H, W> &p_matrix);
//
//        /**
//         * @brief Logs 3 dimensional vector onto the console.
//         */
//        template<class T>
//        static void log(const char* p_info, const Vector3<T> &p_vector);
//
//        /**
//         * @brief Logs 4 dimensional vector onto the console.
//         */
//        template<class T>
//        static void log(const char* p_info, const Vector4<T> &p_vector);

        /**
         * @brief Sets console color to colorCode and console font style to styleCode;
         */
        static void setFont(int p_color_code, int p_style_code);
        /**
         * @brief Sets console color to colorCode.
         */
        static void setFont(int p_color_code);
    };
}

#endif /* CRUSTENGINE_LOGGER_H */
