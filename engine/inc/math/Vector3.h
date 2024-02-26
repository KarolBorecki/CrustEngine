#ifndef CRUSTENGINE_VECTOR3_H
#define CRUSTENGINE_VECTOR3_H

#include <Eigen/Dense>

namespace Crust {
    /**
     * @brief A 3D vector.
     */
    template<typename T = float>
    class Vector3 : public Eigen::Vector3<T> {
    public:
        /**
         * @brief Construct a new Vector3 object with default values.
         */
        Vector3() : Eigen::Vector3<T>() {};
        /**
         * @brief Construct a new Vector3 object with the specified value for all components.
         *
         * @param p_val The value to set all components to.
         */
        explicit Vector3(T p_val) : Eigen::Vector3<T>(p_val, p_val, p_val) {};
        /**
         * @brief Construct a new Vector3 object with the specified values for each component.
         *
         * @param p_x The value for the x component.
         * @param p_y The value for the y component.
         * @param p_z The value for the z component.
         */
        Vector3(T p_x, T p_y, T p_z) : Eigen::Vector3<T>(p_x, p_y, p_z) {};

        template<typename D>
        Vector3<T>& operator=(const Eigen::MatrixBase<D>& other)
        {
            this->Eigen::Vector3<T>::operator=(other);
            return *this;
        }
    };

}

#endif /* CRUSTENGINE_VECTOR3_H */
