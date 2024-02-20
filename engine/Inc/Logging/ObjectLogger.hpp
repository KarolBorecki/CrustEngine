#ifndef _OBJECTLOGGER_HPP_
#define _OBJECTLOGGER_HPP_

#include <Logging/Logger.hpp>
#include <Math/Matrix.hpp>
#include <Math/Vector3.hpp>
#include <Math/Vector4.hpp>

class ObjectLogger
{
public:
  static void Log(const char* info, Matrix<float> &matrix);

  static void Log(const char* info, Vector3<float> &matrix);

  static void Log(const char* info, Vector4<float> &matrix);
};

inline void ObjectLogger::Log(const char* info, Matrix<float> &matrix)
{
  Logger::Log("%s", info);
  for (int y = 0; y < matrix.Height(); ++y)
  {
    for (int x = 0; x < matrix.Width(); ++x)
    {
      Logger::LogInline("%f ", matrix[x][y]);
    }
    Logger::LogInline("\n");
  }
  Logger::LogInline("[%zu x %zu] \n", matrix.Width(), matrix.Height());
}

inline void ObjectLogger::Log(const char* info, Vector3<float> &vector)
{
  Logger::Log("%s (%f, %f, %f) [%zu x %zu]\n", info, vector.X(), vector.Y(), vector.Z(), vector.Width(), vector.Height());
}

inline void ObjectLogger::Log(const char* info, Vector4<float> &vector)
{
  Logger::Log("%s(%f, %f, %f, %f) [%zu x %zu]\n", info, vector.X(), vector.Y(), vector.Z(), vector.W(), vector.Width(), vector.Height());
}


#endif /* _OBJECTLOGGER_HPP_ */
