#ifndef _TIMEPROVIDER_HPP_
#define _TIMEPROVIDER_HPP_

#include <chrono>

class TimeProvider {
public:
  TimeProvider();
  virtual ~TimeProvider() = default;

  static double GetTime_ms();
  static double GetTime_s();

  void OnFrameStart();
  void OnFrameEnd();

  double GetDeltaTime_s();
  double GetDeltaTime_ms();
  double GetAverageFrameTime_s();

  static void OnEngineStart();

  static constexpr double MILISECONDS_TO_SECONDS { 0.001 };

private:
  double frameDeltaTime_ms { 0.0 };
  uint32_t framesPassed { 0 };

  std::chrono::steady_clock::time_point lastFrameStartTimePoint;
  static inline std::chrono::steady_clock::time_point engineStartTimePoint;
};

TimeProvider::TimeProvider() {}

double TimeProvider::GetTime_ms() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - engineStartTimePoint).count();
}

double TimeProvider::GetTime_s() {
  return GetTime_ms() * MILISECONDS_TO_SECONDS;
}

void TimeProvider::OnFrameStart() {
  Logger::Log("frame start %lf [ms]", GetDeltaTime_ms());
  lastFrameStartTimePoint = std::chrono::steady_clock::now();
}

void TimeProvider::OnFrameEnd() {
  frameDeltaTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastFrameStartTimePoint).count();
  Logger::Log("frame end %lf [ms]", GetDeltaTime_ms());
  framesPassed++;
}

inline double TimeProvider::GetDeltaTime_s() { return GetDeltaTime_ms() * MILISECONDS_TO_SECONDS; }

inline double TimeProvider::GetDeltaTime_ms() { return frameDeltaTime_ms; }

inline double TimeProvider::GetAverageFrameTime_s() { return GetTime_s() / framesPassed; }

inline void TimeProvider::OnEngineStart() { engineStartTimePoint = std::chrono::steady_clock::now(); }

#endif /* _TIMEPROVIDER_HPP_ */
