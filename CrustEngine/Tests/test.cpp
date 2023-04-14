#include <Logging/Logger.hpp>

#include <Math/MatrixTests.hpp>


int main(int argc, char *argv[])
{
    MatrixTests::call_all();

    Logger::Log(Logger::FontColor::GREEN, "ALL TESTS DONE.");

    return 0;
}