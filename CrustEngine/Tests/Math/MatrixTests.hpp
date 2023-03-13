#ifndef _MATRIXTESTS_HPP_
#define _MATRIXTESTS_HPP_

#include <CrustTesting.hpp>

#include <Math/Matrix.hpp>

#include <Logging/Logger.hpp>

namespace MatrixTests
{
    void test_constructor_noparameters()
    {
        Matrix<double> m;
        _EQUALS(m.Width(), 0);
        _EQUALS(m.Height(), 0);
    }

    void test_constructor_2parameters()
    {
        Matrix<double> m(10, 10);
        _EQUALS(m.Width(), 10);
        _EQUALS(m.Height(), 10);
        _NOTNULLPTR(m[0]);
    }

    void test_constructor_3parameters()
    {
        Matrix<double> m(10, 10, 10.0);
        _EQUALS(m.Width(), 10);
        _EQUALS(m.Height(), 10);
        _NOTNULLPTR(m[0]);
        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
                _EQUALSDET(m[x][y], 10.0, 0.00001);
    }

    void test_init_with_matrix()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m2[0][0] = 1;
        m2[0][1] = 3;
        m2[0][2] = 7;

        m2[1][0] = 2;
        m2[1][1] = 4;
        m2[1][2] = 8;

        m2[2][0] = 3;
        m2[2][1] = 5;
        m2[2][2] = 9;

        m1 = m2;

        _EQUALS(m1[0][0], 1);
        _EQUALS(m1[0][1], 3);
        _EQUALS(m1[0][2], 7);

        _EQUALS(m1[1][0], 2);
        _EQUALS(m1[1][1], 4);
        _EQUALS(m1[1][2], 8);

        _EQUALS(m1[2][0], 3);
        _EQUALS(m1[2][1], 5);
        _EQUALS(m1[2][2], 9);
    }

    void test_init_with_initlist()
    {
        Matrix<double> m(3, 3);

        m = {1, 3, 7, 2, 4, 8, 3, 5, 9};

        _EQUALS(m[0][0], 1);
        _EQUALS(m[0][1], 3);
        _EQUALS(m[0][2], 7);

        _EQUALS(m[1][0], 2);
        _EQUALS(m[1][1], 4);
        _EQUALS(m[1][2], 8);

        _EQUALS(m[2][0], 3);
        _EQUALS(m[2][1], 5);
        _EQUALS(m[2][2], 9);
    }

    void test_equals()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1.34, 3.235232, 7.12, 2.2342, 4.12, 8.235, 3.211, 5.223, 9.12412};
        m2 = {1.34, 3.235232, 7.12, 2.2342, 4.12, 8.235, 3.211, 5.223, 9.12412};

        _TRUE(m1 == m2);
        _FALSE(m1 != m2);

        m1 = {1.34, 3.235232, 7.12, 2.2342, 4.12, 8.235, 3.211, 5.223, 9.12412};
        m2 = {1.3401, 3.235232, 7.12, 2.2342, 4.12, 8.235, 3.211, 5.223, 9.12412};

        _TRUE(m1 != m2);
        _FALSE(m1 == m2);
    }

    void test_not_equals()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};
        m2 = {9, 5, 3, 8, 4, 2, 7, 3, 1};
    }

    void test_adding_constant()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};

        Matrix<double> expected(3, 3);
        expected = {11, 13, 17, 12, 14, 18, 13, 15, 19};
        m1 += 10;

        _EQUALS(m1, expected);
    }

    void test_adding_matrixes()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};
        m2 = {9, 5, 3, 8, 4, 2, 7, 3, 1};

        Matrix<double> expected(3, 3);
        expected = {10, 8, 10, 10, 8, 10, 10, 8, 10};
        m1 += m2;

        _EQUALS(m1, expected);
    }

    void test_adding_initlist()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};

        Matrix<double> expected(3, 3);
        expected = {10, 8, 10, 10, 8, 10, 10, 8, 10};
        m1 += {9, 5, 3, 8, 4, 2, 7, 3, 1};

        _EQUALS(m1, expected);
    }

    void test_substracting_constant()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};

        Matrix<double> expected(3, 3);
        expected = {-9, -7, -3, -8, -6, -2, -7, -5, -1};
        m1 -= 10;

        _EQUALS(m1, expected);
    }

    void test_substracting_matrixes()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};
        m2 = {9, 5, 3, 8, 4, 2, 7, 3, 1};

        Matrix<double> expected(3, 3);
        expected = {-8, -2, 4, -6, 0, 6, -4, 2, 8};
        m1 -= m2;

        _EQUALS(m1, expected);
    }

    void test_substracting_initlist()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};

        Matrix<double> expected(3, 3);
        expected = {-8, -2, 4, -6, 0, 6, -4, 2, 8};
        m1 -= {9, 5, 3, 8, 4, 2, 7, 3, 1};

        _EQUALS(m1, expected);
    }

    void test_multiplying_constant()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 4, 7, 2, 5, 8, 3, 6, 9};

        Matrix<double> expected(3, 3);
        expected = {10, 40, 70, 20, 50, 80, 30, 60, 90};

        m1 *= 10;

        _EQUALS(m1, expected);
    }

    void test_multiplying_matrix()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 4, 7, 2, 5, 8, 3, 6, 9};
        m2 = {9, 6, 3, 8, 5, 2, 7, 4, 1};

        Matrix<double> expected(3, 3);
        expected = {30, 84, 138, 24, 69, 114, 18, 54, 90};

        m1 *= m2;

        _EQUALS(m1, expected);
    }

    void test_multiplying_initlist()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 4, 7, 2, 5, 8, 3, 6, 9};

        Matrix<double> expected(3, 3);
        expected = {30, 84, 138, 24, 69, 114, 18, 54, 90};

        m1 *= {9, 6, 3, 8, 5, 2, 7, 4, 1};

        _EQUALS(m1, expected);
    }

    void test_dividing_constant()
    {
        Matrix<double> m1(3, 3);

        m1 = {1, 4, 7, 2, 5, 8, 72, 6, 9};

        Matrix<double> expected(3, 3);
        expected = {0.25, 1, 1.75, 0.5, 1.25, 2, 18, 1.5, 2.25};

        m1 /= 4;

        _EQUALS(m1, expected);
    }

    void test_dividing_matrix()
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3, 3);

        m1 = {1, 4, 7, 2, 5, 8, 3, 6, 9};
        m2 = {4, 2, 14, 2, 5, 2, 1.5, 0.5, 2};

        Matrix<double> expected(3, 3);
        expected = {0.25, 2, 0.5, 1, 1, 4, 2, 12, 4.5};

        m1 /= m2;

        _EQUALS(m1, expected);
    }

    void call_all()
    {
        test_constructor_noparameters();
        test_constructor_2parameters();
        test_constructor_3parameters();

        test_init_with_matrix();
        test_init_with_initlist();

        test_equals();
        test_not_equals();

        test_adding_constant();
        test_adding_matrixes();
        test_adding_initlist();

        test_substracting_constant();
        test_substracting_matrixes();
        test_substracting_initlist();

        test_multiplying_constant();
        test_multiplying_matrix();
        test_multiplying_initlist();

        test_dividing_constant();
        test_dividing_matrix();

        test_equals();
    }
}

#endif