#ifndef CRUSTENGINE_VECTOR4_H
#define CRUSTENGINE_VECTOR4_H

#include <Eigen/Dense>

namespace Crust {
    /**
     * @brief A 4D vector.
     */
    template<typename T = float>
    class Vector4 : public Eigen::Vector4<T> {
    public:
        /**
         * @brief Construct a new Vector4 object with default values.
         */
        Vector4() : Eigen::Vector4<T>() {};
        /**
         * @brief Construct a new Vector4 object with the specified value for all components.
         *
         * @param p_val The value to set all components to.
         */
        explicit Vector4(T p_val) : Eigen::Vector4<T>(p_val, p_val, p_val, p_val) {};
        /**
         * @brief Construct a new Vector4 object with the specified values for each component.
         *
         * @param p_x The value for the x component.
         * @param p_y The value for the y component.
         * @param p_z The value for the z component.
         * @param p_w The value for the w component.
         */
        Vector4(T p_x, T p_y, T p_z, T p_w) : Eigen::Vector4<T>(p_x, p_y, p_z, p_w) {};

        template<typename D>
        Vector4<T>& operator=(const Eigen::MatrixBase<D>& other)
        {
            this->Eigen::Vector4<T>::operator=(other);
            return *this;
        }
    };
}

#endif /* CRUSTENGINE_VECTOR4_H */
