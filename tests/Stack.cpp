#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <Stack.hpp>
#include <iostream>

using namespace sof;

TEST_CASE("cctor", "[Stack<int>]"){
    auto obj = Stack<int>();
    REQUIRE(obj.size() == 0);
}
