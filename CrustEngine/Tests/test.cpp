#include <Math/MatrixTests.hpp>
#include <Math/Matrix.hpp>
#include <Math/Vector3.hpp>

#include <Logging/Logger.hpp>

int main(int argc, char *argv[])
{
    Vector3 m(3, 1, 0.0);
    m = { 1.112, -2.223, 3.334};

    Vector3 m2(3, 1, 0.0);

    m2 = m;

    Logger::Info("%lf, %lf, %lf", m2.X(), m2.Y(), m2.Z());

    return 0;
}