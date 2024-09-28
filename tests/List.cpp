#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "List.hpp"


TEST_CASE("contructor()","[list]"){
    auto obj = List<int>{};
    REQUIRE(obj.size() == 0);

    auto obj2 = List<int>{4, 1};
    REQUIRE(obj2.size() == 4);

    REQUIRE(obj2.str() == "{ [0] = 1, [1] = 1, [2] = 1, [3] = 1 }");
}
TEST_CASE("push_back", "[list]"){
    auto obj = List<int>{};
    obj.push_back(1);
    obj.push_back(2);
    REQUIRE(obj.size() == 2);
    REQUIRE(obj.str() == "{ [0] = 1, [1] = 2 }");
    
}
TEST_CASE("push_at", "[list]"){
    auto obj = List<int>{10, -1};
    REQUIRE(obj.size() == 10);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1 }");

    obj.push_at(3, 0);
    REQUIRE(obj.size() == 11);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = 0, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1, [10] = -1 }");
}

TEST_CASE("remove", "[list]"){
    auto obj = List<int>{10, -1};
    REQUIRE(obj.size() == 10);
    obj.remove(3);
    REQUIRE(obj.size() == 9);
}

TEST_CASE("clear", "[list]"){
    auto obj = List<int>{10, -1};
    REQUIRE(obj.size() == 10);

    obj.clear();
    REQUIRE(obj.size() == 0);
}

TEST_CASE("pop", "[list]"){
    auto obj = List<int>{300, -1};
    REQUIRE(obj.size() == 300);
    obj.pop();
    REQUIRE(obj.size() == 300 - 1);
}

TEST_CASE("front", "[list]"){
    auto obj = List<int>{2, -1};
    REQUIRE(obj.size() == 2);

    REQUIRE(obj.front() == -1);
    obj.front() = 11;
    REQUIRE(obj.front() == 11);
}

TEST_CASE("op_pracket", "[list]"){
    auto obj = List<int>{5, -1};
    REQUIRE(obj.size() == 5);

    REQUIRE(obj[2] == -1);

    obj[2] = 11;
    REQUIRE(obj[2] == 11);
}

TEST_CASE("str", "[list]"){
    auto obj = List<int>{3, -1};
    REQUIRE(obj.size() == 3);

    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");
}

TEST_CASE("cctor", "[list]"){
    auto obj = List<int>{3, -1};
    REQUIRE(obj.size() == 3);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");

    auto obj2(obj);
    REQUIRE(obj2.size() == obj.size());
    REQUIRE(obj2.str() == obj.str());
}

TEST_CASE("op_cpy", "[list]"){
    auto obj = List<int>{3, -1};
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");

    List<int> obj2 ;
    SECTION("obj size == obj3 size"){
        obj2.push_back(10);
        obj2.push_back(100);
        obj2.push_back(1);
        obj2 = obj;
        REQUIRE(obj2.size() == obj.size());
        REQUIRE(obj2.str() == obj.str());
    }
    List<int>  obj3;
    SECTION("obj size < obj3 size"){
        REQUIRE(obj3.size() == 0);
        obj3 = obj;
        REQUIRE(obj3.size() == obj.size());
        REQUIRE(obj3.str() == obj.str());
    }

    List<int> obj4(12, 2);
    SECTION("obj size > obj3 size"){
        REQUIRE(obj4.size() == 12);
        obj4 = obj;
        REQUIRE(obj4.size() == obj.size());
        REQUIRE(obj4.str() == obj.str());
    }
}

TEST_CASE("find", "[list]"){
    auto obj = List<int>();
    obj.push_back(1);
    obj.push_back(10);
    obj.push_back(100);
    obj.push_back(1000);

    REQUIRE(obj.find(10) == 1);
    REQUIRE(obj.find(2) == std::nullopt);
}

TEST_CASE("iterators", "[list]"){
    List<int> obj;
    int i;
    for (i = 0; i < 10; i++)
    {
        obj.push_back(i);
    }

    for (auto&& j : obj)
    {
        REQUIRE(j == 10 - i--);
    }

    REQUIRE(*obj.begin() == obj[0]);

}