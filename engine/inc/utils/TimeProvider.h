#ifndef CRUSTENGINE_TIMEPROVIDER_H
#define CRUSTENGINE_TIMEPROVIDER_H

#include <chrono>

namespace Crust {
    /**
     * @brief Class providing timing data in the engine.
     */
    class TimeProvider
    {
    public:
        TimeProvider() = default;
        virtual ~TimeProvider() = default;

        /**
         * @brief Returns time from engine's core start in milliseconds.
         */
        static double getTime_ms();
        /**
         * @brief Returns time from engine's core start in seconds.
         */
        static double getTime_s();

        /**
         * @brief Method called on each window's frame start.
         *
         * @details Saves time point of frame start to calculate how long this frame will take.
         */
        void onFrameStart();
        /**
         * @brief Method called on each window's frame end.
         *
         * @details Saves time point of frame end to calculate how long this frame took.
         */
        void onFrameEnd();

        /**
         * @brief Returns current frames per seconds value based on last frame time.
         */
        double getFPS() const;
        /**
         * @brief Returns current average frames per seconds value based on all frames.
         *
         * @return Returns value of 1.0 / TimeProvider::GetAverageFrameTime_s.
         */
        double getAverageFPS() const;

        /**
         * @brief Returns last frame time in seconds.
         */
        double getDeltaTime_s() const;
        /**
         * @brief Returns last frame time in miliseconds.
         */
        double getDeltaTime_ms() const;
        /**
         * @brief Returns average frame time from engine start in seconds.
         *
         * @return  TimeProvider::getTimeS / #framesPassed;
         */
        double getAverageFrameTime_s() const;

        /**
         * @brief Method called on engine's core start.
         *
         * @details Saves engine's core start time point.
         *
         * @sa Core.hpp
         */
        static void onEngineStart();

        static constexpr double MILISECONDS_TO_SECONDS{0.001};

    private:
        double m_frame_delta_time_ms { 0.0 }; //!< Time that last frame took to complete.
        uint32_t m_frames_passed { 0 };      //!< Amount of frames that RenderWindow did from it start.

        std::chrono::steady_clock::time_point m_last_frame_start_time_point;            //!< Last frame saved time point at which it started.
        static inline std::chrono::steady_clock::time_point m_engine_start_time_point; //!< Engine's core start time point saved in TimeProvider::OnEngineStart.
    };
}

#endif /* CRUSTENGINE_TIMEPROVIDER_H */
