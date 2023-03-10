#ifndef _MATRIXTESTS_HPP_
#define _MATRIXTESTS_HPP_

#include <CrustTesting.hpp>

#include <Math/Matrix.hpp>

// #include "boost/lexical_cast.hpp"
// void print_mat(Matrix<double> &mat)
// {
//     std::string result = "";
//     for (int r = 0; r < mat.Height(); r++)
//     {
//         for (int c = 0; c < mat.Width(); c++)
//         {
//             result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" + boost::lexical_cast<std::string>(mat[c][r]) + " ";
//         }
//         result += "\n";
//     }
//     Logger::Info("%s", result.c_str());
// }

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
        for(int x=0; x<10; x++)
            for(int y=0; y<10; y++)
                _EQUALSDET(m[x][y], 10.0, 0.00001);
    }

    void test_adding() 
    {
        Matrix<double> m1(3, 3);
        Matrix<double> m2(3,3);

        m1 = {1, 3, 7, 2, 4, 8, 3, 5, 9};
        m2 = {9, 5, 3, 8, 4, 2, 7, 3, 1};

        Matrix<double> expected(3, 3);
        expected = {30, 84, 138, 24, 69, 114, 18, 54, 90};

        Matrix<double> got;
        got = m1 * m2;

        _EQUALS(got, expected);
    }

    void test_substracting()
    {
    }

    void test_multiplying()
    {

    }

    void test_dividing()
    {

    }

    void test_equals()
    {

    }

    void call_all()
    {
        test_constructor_noparameters();
        test_constructor_2parameters();
        test_constructor_3parameters();

        test_adding();
        test_substracting();
        test_multiplying();
        test_dividing();
        test_equals();
    }
}

#endif