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
        _TRUE(false);
    }

    void call_all()
    {
        test_constructor_noparameters();
    }
}

#endif