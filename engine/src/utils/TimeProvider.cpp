#include "utils/TimeProvider.h"

namespace Crust {
    double TimeProvider::getTime_ms()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_engine_start_time_point).count();
    }

    double TimeProvider::getTime_s() { return getTime_ms() * MILISECONDS_TO_SECONDS; }

    void TimeProvider::onFrameStart()
    {
        m_last_frame_start_time_point = std::chrono::steady_clock::now();
    }

    void TimeProvider::onFrameEnd()
    {
        m_frame_delta_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - m_last_frame_start_time_point).count();
        m_frames_passed++;
    }

    double TimeProvider::getFPS() const { return 1 / getDeltaTime_s(); }

    double TimeProvider::getAverageFPS() const { return 1 / getAverageFrameTime_s(); }

    double TimeProvider::getDeltaTime_s() const { return getDeltaTime_ms() * MILISECONDS_TO_SECONDS; }

    double TimeProvider::getDeltaTime_ms() const { return m_frame_delta_time_ms; }

    double TimeProvider::getAverageFrameTime_s() const { return getTime_s() / m_frames_passed; }

    void TimeProvider::onEngineStart() { m_engine_start_time_point = std::chrono::steady_clock::now(); }

}
