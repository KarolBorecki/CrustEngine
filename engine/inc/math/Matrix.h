#ifndef CRUSTENGINE_MATRIX_H
#define CRUSTENGINE_MATRIX_H

#include <Eigen/Dense>

namespace Crust {
    /**
     * @brief Represents the mathematical matrix and is able to preform matrix calculations.
     *
     * @details This matrix class assumes that x value is the number of a column and y value is the number of a row.
     * This means that matrix[3][2] is value in 3rd row and 2nd column.
     * Also height says how many rows there are and width says how many columns there are.
     *
     * @tparam T Types of values held in this matrix.
     * @tparam H Amount of rows in this matrix.
     * @tparam W Amount of columns in this matrix.
     */
    template <typename T, int H, int W>
    class Matrix : public Eigen::Matrix<T, H, W> {
    public:
        Matrix() : Eigen::Matrix<T, H, W>() {};

        /**
         * @brief If width or height argument is zero then no space for matrix's array will be allocated.
         *
         * @param defaultVal The value that will be placed on each position in matrix.
         */
        explicit Matrix(T p_val);

        /**
         * @brief Get the height of the matrix.
         */
        inline uint16_t height() const { return (*this).rows(); };

        /**
         * @brief Get the width of the matrix.
         */
        inline uint16_t width() const { return (*this).cols(); };

        /**
         * @brief Reset all elements in matrix to the given value.
         *
         * @param p_val The value that will be placed on each position in matrix.
         */
        void reset(T p_val);

        /**
         * @brief Make this matrix an identity matrix.
         */
        void makeIdentity();

        template<typename D>
        Matrix<T, H, W>& operator=(const Eigen::MatrixBase <D>& other)
        {
            this->Eigen::Matrix<T, H, W>::operator=(other);
            return *this;
        }
    };

    typedef Matrix<float, 4, 4> Matrix4x4f;
    typedef Matrix<float, 3, 3> Matrix3x3f;

    typedef Matrix<double, 4, 4> Matrix4x4d;
    typedef Matrix<double, 3, 3> Matrix3x3d;

    template<typename T, int H, int W>
    Matrix<T, H, W>::Matrix(T p_val) : Eigen::Matrix<T, H, W>() {
        reset(p_val);
    }

    template<typename T, int H, int W>
    void Matrix<T, H, W>::reset(T p_val) {
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                (*this)(i, j) = p_val;
            }
        }
    }

    template<typename T, int H, int W>
    void Matrix<T, H, W>::makeIdentity() {
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                if (i == j) {
                    (*this)(i, j) = 1;
                } else {
                    (*this)(i, j) = 0;
                }
            }
        }

    }
}

#endif /* CRUSTENGINE_MATRIX_H */
