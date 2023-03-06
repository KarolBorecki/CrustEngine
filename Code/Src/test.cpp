#include <cstdlib> /* Plz no - atoi */

#include <Logging/Logger.hpp>
#include <iostream>

#include <Physics/Matrix.hpp>
#include <Physics/Vector4.hpp>

#include "boost/lexical_cast.hpp"


void print_mat(Matrix<double> &mat)
{
  std::string result = "";
  for (int r = 0; r < mat.Height(); r++)
  {
    for (int c = 0; c < mat.Width(); c++)
    {
      result += "(" + std::to_string(r) + "," + std::to_string(c) + ")" + boost::lexical_cast<std::string>(mat[c][r]) + " ";
    }
    result += "\n";
  }
  Logger::Info("%s", result.c_str());
}

int main(int argc, char *argv[])
{
    Vector4 v1;
    v1 = {1,2,3,4};
    print_mat(v1);

    return 0;
}