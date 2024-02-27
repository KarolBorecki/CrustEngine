#include "math/Matrix.h"
#include "math/Vector3.h"
#include "math/Vector4.h"
#include "logging/Logger.h"

//TODO investigate [[nodiscard]] attribute
// TODO review reference vs pointer scenarios
// USE reference when you want to tell that object cannot exists withou another
// USE pointer in any other cases
int main(int argc, char *argv[])
{
    Crust::Matrix<float, 4, 4> matrix;
    Crust::Matrix<float, 4, 4> matrix2(2.0f);

    matrix.reset(5.0f);
    matrix(0, 0) = 2.0f;
    matrix(1, 3) = 69.0f;

    matrix2(0, 0) = 12.0f;
    matrix2(1, 3) = 45.0f;

    Crust::Logger::log("Matrix: ", matrix);
    Crust::Logger::log("Matrix2: ", matrix2);

    Crust::Matrix<float, 4, 4> matrix3;
    matrix3 = matrix - matrix2;
    matrix3 -= matrix2;
    Crust::Logger::log("Matrix - Matrix2: ", matrix3);

    Crust::Vector4<> v1(1.0f, 2.0f, 3.0f, 4.0f);
    Crust::Vector4<> v2(1.0f);
    Crust::Vector3<> v3(1.0f);


    return 0;
}