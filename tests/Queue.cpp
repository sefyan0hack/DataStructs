#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <Queue.hpp>
#include <iostream>

using namespace sof;
TEST_CASE("cctor", "Queue<int>"){
    auto obj = Queue<int>();
    REQUIRE(obj.size() == 0);

    auto obj2 = Queue<int>(10, 1);
    REQUIRE(obj2.size() == 10);

    obj2.push(0);
    REQUIRE(obj2.size() == 11);
    REQUIRE(obj2[10] == 0);
    std::cout << obj2.str();

}