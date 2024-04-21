#ifndef CRUSTENGINE_MATRIX_H
#define CRUSTENGINE_MATRIX_H

#include <Eigen/Dense>

namespace Crust {
    typedef Eigen::Matrix<double, 1, 4> Matrix1x4f;

    typedef Eigen::Matrix<double, 4, 4> Matrix4x4f;
    typedef Eigen::Matrix<double, 3, 3> Matrix3x3f;

    typedef Eigen::Matrix<double, 4, 4> Matrix4x4d;
    typedef Eigen::Matrix<double, 3, 3> Matrix3x3d;
}

#endif /* CRUSTENGINE_MATRIX_H */
