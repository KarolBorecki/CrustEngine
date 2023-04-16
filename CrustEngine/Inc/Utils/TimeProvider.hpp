#ifndef _TIMEPROVIDER_HPP_
#define _TIMEPROVIDER_HPP_

#include <chrono>

/**
 * @brief Class providing timing data in the engine.
 */
class TimeProvider
{
public:
  TimeProvider();
  virtual ~TimeProvider() = default;

  /**
   * @brief Returns time from engine's core start in milliseconds.
   */
  static double GetTime_ms();
  /**
   * @brief Returns time from engine's core start in seconds.
   */
  static double GetTime_s();

  /**
   * @brief Method called on each window's frame start.
   *
   * @details Saves time point of frame start to calculate how long this frame will take.
   */
  void OnFrameStart();
  /**
   * @brief Method called on each window's frame end.
   *
   * @details Saves time point of frame end to calculate how long this frame took.
   */
  void OnFrameEnd();

  /**
   * @brief Returns current frames per seconds value based on last frame time.
   */
  double GetFPS();
  /**
   * @brief Returns current average frames per seconds value based on all frames.
   *
   * @return Returns value of 1.0 / TimeProvider::GetAverageFrameTime_s.
   */
  double GetAverageFPS();

  /**
   * @brief Returns last frame time in seconds.
   */
  double GetDeltaTime_s();
  /**
   * @brief Returns last frame time in miliseconds.
   */
  double GetDeltaTime_ms();
  /**
   * @brief Returns average frame time from engine start in seconds.
   *
   * @return  TimeProvider::GetTime_s / #framesPassed;
   */
  double GetAverageFrameTime_s();

  /**
   * @brief Method called on engine's core start.
   *
   * @details Saves engine's core start time point.
   *
   * @sa Core.hpp
   */
  static void OnEngineStart();

  static constexpr double MILISECONDS_TO_SECONDS{0.001};

private:
  double frameDeltaTime_ms{0.0}; //!< Time that last frame took to complete.
  uint32_t framesPassed{0};      //!< Amount of frames that RenderWindow did from it start.

  std::chrono::steady_clock::time_point lastFrameStartTimePoint;            //!< Last frame saved time point at which it started.
  static inline std::chrono::steady_clock::time_point engineStartTimePoint; //!< Engine's core start time point saved in TimeProvider::OnEngineStart.
};

TimeProvider::TimeProvider() {}

double TimeProvider::GetTime_ms()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - engineStartTimePoint).count();
}

inline double TimeProvider::GetTime_s() { return GetTime_ms() * MILISECONDS_TO_SECONDS; }

void TimeProvider::OnFrameStart()
{
  lastFrameStartTimePoint = std::chrono::steady_clock::now();
}

void TimeProvider::OnFrameEnd()
{
  frameDeltaTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFrameStartTimePoint).count();
  framesPassed++;
}

inline double TimeProvider::GetFPS() { return 1 / GetDeltaTime_s(); }

inline double TimeProvider::GetAverageFPS() { return 1 / GetAverageFrameTime_s(); }

inline double TimeProvider::GetDeltaTime_s() { return GetDeltaTime_ms() * MILISECONDS_TO_SECONDS; }

inline double TimeProvider::GetDeltaTime_ms() { return frameDeltaTime_ms; }

inline double TimeProvider::GetAverageFrameTime_s() { return GetTime_s() / framesPassed; }

inline void TimeProvider::OnEngineStart() { engineStartTimePoint = std::chrono::steady_clock::now(); }

#endif /* _TIMEPROVIDER_HPP_ */
