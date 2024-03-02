#include "logging/Logger.h"

namespace Crust {
    void Logger::error(const char *p_format, ...)
    {
        setFont(Logger::FontColor::RED);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    void Logger::warning(const char *p_format, ...)
    {
        setFont(FontColor::YELLOW);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    void Logger::info(const char *p_format, ...)
    {
        setFont(FontColor::BLUE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    void Logger::log()
    {
        printf("\n");
    }

    void Logger::log(const char *p_format, ...)
    {
        setFont(FontColor::WHITE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
    }

    void Logger::log(int p_color_code, const char *p_format, ...)
    {
        setFont(p_color_code);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        printf("\n");
        va_end(args);
        setFont(FontColor::WHITE);
    }

    void Logger::logInline(const char *p_format, ...)
    {
        setFont(FontColor::WHITE);
        va_list args;
        va_start(args, p_format);
        vprintf(p_format, args);
        va_end(args);
    }

//    template<typename T, int H, int W>
//    void Logger::log(const char *p_info, const Matrix<T, H, W> &p_matrix) {
//        log("%s", p_info);
//        for (int y = 0; y < p_matrix.height(); ++y) {
//            for (int x = 0; x < p_matrix.width(); ++x) {
//                logInline("%.2f ", p_matrix(y, x));
//            }
//            log();
//        }
//        logInline("[%zu x %zu] \n", p_matrix.width(), p_matrix.height());
//
//    }
//
//    template<typename T>
//    void Logger::log(const char *p_info, const Vector3<T> &v) {
//        log("%s", p_info);
//        logInline("[%.2f, %.2f, %.2f]\n", v.x(), v.y(), v.z());
//    }
//
//    template<class T>
//    void Logger::log(const char *p_info, const Vector4<T> &p_vector) {
//        log("%s", p_info);
//        logInline("[%.2f, %.2f, %.2f, %.2f]\n", p_vector.x(), p_vector.y(), p_vector.z(), p_vector.w());
//    }

    void Logger::setFont(int p_color_code, int p_style_code)
    {
        printf("\033[%dm", Logger::FontColor::WHITE);
        printf("\033[%dm", p_style_code);
        printf("\033[%dm", p_color_code);
    }

    void Logger::setFont(int colorCode)
    {
        setFont(colorCode, FontStyle::NORMAL);
    }
}

