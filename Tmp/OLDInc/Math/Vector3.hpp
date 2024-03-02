#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

#include <cstdint>

#include <Math/Matrix.hpp>
#include <Math/Vector4.hpp>

namespace crust {
    template<class T, typename E>
    class Vector4;

/**
 * @brief Represents mathematical vector3.
 */
    template<class T = float, typename E = typename std::enable_if<std::is_floating_point<T>::value>::type>
    class Vector3 : public Matrix<T> {
    public:
        /**
         * @brief Creates blank vector that consists of zeros.
         */
        Vector3() {
            SetX(0.0);
            SetY(0.0);
            SetZ(0.0);
        }

        Vector3(const Vector3<float, void>& v3) {
            SetX(v3.X());
            SetY(v3.Y());
            SetZ(v3.Z());
        }

        /**
         * @param valXYZ Value for each X, Y and Z fields.
         */
        Vector3(T valXYZ);

        /**
         * @param x Value for X field.
         * @param y Value for Y field.
         * @param z Value for Z field.
         */
        Vector3(T x, T y, T z);

        ~Vector3();

        /**
         * @brief Getter for Vector3 x value.
         */
        T X() const;

        /**
         * @brief Getter for Vector3 y value.
         */
        T Y() const;

        /**
         * @brief Getter for Vector3 z value.
         */
        T Z() const;

        /**
         * @brief Setter for Vector3 x value.
         *
         * @param valX New value of vector's x.
         */
        void SetX(T valX);

        /**
         * @brief Setter for Vector3 y value.
         *
         * @param valY New value of vector's y.
         */
        void SetY(T valY);

        /**
         * @brief Setter for Vector3 z value.
         *
         * @param valZ New value of vector's z.
         */
        void SetZ(T valZ);

        /**
         * @brief Calculates length of this vector.
         *
         * @return float Length of this vector.
         */
        float Length() const;

        /**
         * @brief Normalizes this vector. Warning! This method modifies this vector, value will be changed and old vector's state will be lost.
         */
        void Normalize();

        /**
         * @brief Calculates normal of this vector and returns new vector with calculated values. It does not modify the original vector.
         *
         * @return Vector3<T, E> Normal of this vector. Copy.
         */
        Vector3<T, E> Normalized();

        /**
         * @brief Calculates dot product of this vector and given vector.
         *
         * @param other Vector to calculate dot product with.
         * @return float Dot product of this vector and given vector.
         */
        float Dot(const Vector3<T, E> &other) const;

        /**
         * @brief Calculates cross product of this vector and given vector.
         *
         * @param other Vector to calculate cross product with.
         * @return Vector3<T, E> Cross product of this vector and given vector.
         */
        Vector3<T, E> Cross(const Vector3<T, E> &other) const;

        /**
         * @brief Calculates normal vector of plane that this polygon represents.
         *
         * @return Vector3& Normal vector of this plane.
         */
        static Vector3<T, E> PolygonNormal(Vector3<> p1, Vector3<> p2, Vector3<> p3);

        /**
         * @brief Converts this vector to Vector4.
         *
         * @param wVal Value of w field in new Vector4.
         *
         * @return Vector4<T, E> Vector4 with X, Y and Z values from this vector and given w value.
         */
        crust::Vector4<T, E> ToVector4(T wVal) const;

        //TODO add overload for multiply and make it more optimized
        /**
       * @brief Mimic #other vector4. Copy X, Y, Z values and disobeys 'W' value.
       * @details No changes will be done on #other matrix. Data held until this point on this vector3 will be lost.
       *
       * @param other Vector4 from which copy of X, Y and Z values will be performed.
       * @return Vector3<> & Reference to *this Vector3 with values X, Y and Z exactly the same as #other Vactor4.
       */
        crust::Vector3<T, E> &operator=(const Vector4<T, E> &other) noexcept;

    private:
        static inline constexpr uint8_t _VECTOR3_WIDTH{3};
        static inline constexpr uint8_t _VECTOR3_HEIGHT{1};
    };

    template<typename T, typename E>
    inline Vector3<T, E>::Vector3(T valXYZ) : Vector3(valXYZ, valXYZ, valXYZ) {}

    template<class T, typename E>
    inline Vector3<T, E>::Vector3(T x, T y, T z) : Matrix<T>(_VECTOR3_HEIGHT, _VECTOR3_WIDTH) {
        SetX(x);
        SetY(y);
        SetZ(z);
    }

    template<typename T, typename E>
    inline Vector3<T, E>::~Vector3() {}

    template<typename T, typename E>
    inline T Vector3<T, E>::X() const { return (*this)[0][0]; }

    template<typename T, typename E>
    inline T Vector3<T, E>::Y() const { return (*this)[1][0]; }

    template<typename T, typename E>
    inline T Vector3<T, E>::Z() const { return (*this)[2][0]; }

    template<typename T, typename E>
    inline void Vector3<T, E>::SetX(T valX) { (*this)[0][0] = valX; }

    template<typename T, typename E>
    inline void Vector3<T, E>::SetY(T valY) { (*this)[1][0] = valY; }

    template<typename T, typename E>
    inline void Vector3<T, E>::SetZ(T valZ) { (*this)[2][0] = valZ; }

    template<typename T, typename E>
    inline float Vector3<T, E>::Length() const {
        return Math::SquareRoot(X() * X() + Y() * Y() + Z() * Z());
    }

    template<typename T, typename E>
    inline void Vector3<T, E>::Normalize() {
        T length = Length();
        length = Math::Equals(length, 0.0f) ? 1.0f : length;
        SetX(X() / length);
        SetY(Y() / length);
        SetZ(Z() / length);
    }

    template<typename T, typename E>
    inline Vector3<T, E> Vector3<T, E>::Normalized() {
        T length = Length();
        return Vector3<T, E>(X() / length, Y() / length, Z() / length);
    }

    template<typename T, typename E>
    inline float Vector3<T, E>::Dot(const Vector3<T, E> &other) const {
        return X() * other.X() + Y() * other.Y() + Z() * other.Z();
    }

    template<typename T, typename E>
    inline Vector3<T, E> Vector3<T, E>::Cross(const Vector3<T, E> &other) const {
        return Vector3<T, E>(Y() * other.Z() - Z() * other.Y(),
                             Z() * other.X() - X() * other.Z(),
                             X() * other.Y() - Y() * other.X());
    }

    template<typename T, typename E>
    inline Vector3<T, E> Vector3<T, E>::PolygonNormal(Vector3<> p1, Vector3<> p2, Vector3<> p3) {
        Vector3<T, E> v1 = p2;
        Vector3<T, E> v2 = p3;
        v1 -= p1;
        v2 -= p1;
        return v1.Cross(v2).Normalized();
    }

    template<typename T, typename E>
    inline crust::Vector4<T, E> Vector3<T, E>::ToVector4(T wVal) const {
        return Vector4<T, E>(X(), Y(), Z(), wVal);
    }

    template<typename T, typename E>
    inline Vector3<T, E> &Vector3<T, E>::operator=(const crust::Vector4<T, E> &other) noexcept {
        SetX(other.X());
        SetY(other.Y());
        SetZ(other.Z());
        return *this;
    }

}

#endif /* _VECTOR3_HPP_ */
