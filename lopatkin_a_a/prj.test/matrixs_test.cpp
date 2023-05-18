#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>

#include <sstream>

TEST_CASE("[matrixs] - MatrixS ctor") {
    MatrixS m(1, 1);
    CHECK(m.at(0, 0) == 0);
}
