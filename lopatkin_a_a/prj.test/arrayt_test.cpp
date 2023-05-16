#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayt/arrayt.hpp>

TEST_CASE("[arrayt] - ArrayT ctor") {
    ArrayT<int> arr(1);
    CHECK(arr[0] == 0);

    ArrayT<double> arr1(1);
    CHECK(arr[0] == 0.0);
}
