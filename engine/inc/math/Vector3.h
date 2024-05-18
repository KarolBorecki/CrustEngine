#ifndef CRUSTENGINE_VECTOR3_H
#define CRUSTENGINE_VECTOR3_H

#include <Eigen/Dense>

namespace Crust {
    typedef Eigen::Matrix<double, 1, 3> Vector3;
    typedef Eigen::Matrix<double, 1, 3> Vector3d;
    
    static const Eigen::Matrix<double, 1, 3> Vector3Zero = Eigen::Matrix<double, 1, 3>::Zero();
}

#endif /* CRUSTENGINE_VECTOR3_H */
