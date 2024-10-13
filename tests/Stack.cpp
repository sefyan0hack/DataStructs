#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <Stack.hpp>
#include <iostream>

using namespace sof;

TEST_CASE("cctor", "[Stack<int>]")
{
    SECTION("test default constructor")
    {
        auto obj = Stack<int>();
        REQUIRE(obj.size() == 0);
        REQUIRE(obj.max_size() == static_cast<decltype(obj)::size_type>(-1));
    }
    SECTION("test constructor with max size")
    {
        auto obj = Stack<int>(100);
        REQUIRE(obj.size() == 0);
        REQUIRE(obj.max_size() == static_cast<decltype(obj)::size_type>(100));
    }
}

TEST_CASE("push", "[Stack<int>]")
{
    auto obj = Stack<int>();
    obj.push(1);
    obj.push(10);
    obj.push(1000);
    obj.push(100);
    obj.push(1000);
    REQUIRE(obj.size() == 5);
}

TEST_CASE("pop", "[Stack<int>]")
{
    auto obj = Stack<int>();
    obj.push(1);
    obj.push(10);
    obj.push(100);
    REQUIRE(obj.pop() == 100);
    REQUIRE(obj.size() == 2);
}

TEST_CASE("peek", "[Stack<int>]")
{
    auto obj = Stack<int>();
    obj.push(1);
    obj.push(10);
    REQUIRE(obj.peek() == 10);
    REQUIRE(obj.size() == 2);
}

TEST_CASE("str", "[Stack<int>]")
{
    auto obj = Stack<int>();
    obj.push(1);
    obj.push(10);
    obj.push(110);
    obj.push(130);
    REQUIRE(obj.str() == "{ 1, 10, 110, 130 }");
}