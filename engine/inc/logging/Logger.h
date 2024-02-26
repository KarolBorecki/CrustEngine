#ifndef CRUSTENGINE_LOGGER_H
#define CRUSTENGINE_LOGGER_H

#include <cstdarg>
#include <cstring>
#include <cstdio>
#include "math/Matrix.h"

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

        /**
         * @brief Logs matrix onto the console.
         */
        template<class T, int H, int W>
        static void log(const char* p_info, const Matrix<T, H, W> &p_matrix);

        /**
         * @brief Logs 3 dimensional vector onto the console.
         */
        template<class T>
        static void log(const char* p_info, const Vector3<T> &p_vector);

        /**
         * @brief Logs 4 dimensional vector onto the console.
         */
        template<class T>
        static void log(const char* p_info, const Vector4<T> &p_vector);

        /**
         * @brief Sets console color to colorCode and console font style to styleCode;
         */
        static void setFont(int p_color_code, int p_style_code);
        /**
         * @brief Sets console color to colorCode.
         */
        static void setFont(int p_color_code);
    };

    inline void Logger::error(const char *p_format, ...)
    {
        setFont(Logger::FontColor::RED);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    inline void Logger::warning(const char *p_format, ...)
    {
        setFont(FontColor::YELLOW);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    inline void Logger::info(const char *p_format, ...)
    {
        setFont(FontColor::BLUE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    inline void Logger::log()
    {
        printf("\n");
    }

    inline void Logger::log(const char *p_format, ...)
    {
        setFont(FontColor::WHITE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
    }

    inline void Logger::log(int p_color_code, const char *p_format, ...)
    {
        setFont(p_color_code);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    inline void Logger::logInline(const char *p_format, ...)
    {
        setFont(FontColor::WHITE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        va_end(args);
    }

    template<typename T, int H, int W>
    void Logger::log(const char *p_info, const Matrix<T, H, W> &p_matrix) {
        log("%s", p_info);
        for (int y = 0; y < p_matrix.height(); ++y) {
            for (int x = 0; x < p_matrix.width(); ++x) {
                logInline("%.2f ", p_matrix(y, x));
            }
            log();
        }
        logInline("[%zu x %zu] \n", p_matrix.width(), p_matrix.height());

    }

    template<typename T>
    void Logger::log(const char *p_info, const Vector3<T> &v) {
        log("%s", p_info);
        logInline("[%.2f, %.2f, %.2f]\n", v.x(), v.y(), v.z());
    }

    template<class T>
    void Logger::log(const char *p_info, const Vector4<T> &p_vector) {
        log("%s", p_info);
        logInline("[%.2f, %.2f, %.2f, %.2f]\n", p_vector.x(), p_vector.y(), p_vector.z(), p_vector.w());
    }

    inline void Logger::setFont(int p_color_code, int p_style_code)
    {
        printf("\033[%dm", Logger::FontColor::WHITE);
        printf("\033[%dm", p_style_code);
        printf("\033[%dm", p_color_code);
    }

    inline void Logger::setFont(int colorCode)
    {
        setFont(colorCode, FontStyle::NORMAL);
    }
}

#endif /* CRUSTENGINE_LOGGER_H */
