#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <List.hpp>
#include <iostream>
#define STRINGIZE(x) #x
#define TAG(x) "[" STRINGIZE(x) "]"

#define COM_TEST \
TEST_CASE("contructor()", GlistTag){    \
    auto obj = Glist{}; \
    REQUIRE(obj.size() == 0);   \
    auto obj2 = Glist{4, 1};    \
    REQUIRE(obj2.size() == 4);  \
    REQUIRE(obj2.str() == "{ [0] = 1, [1] = 1, [2] = 1, [3] = 1 }");    \
}   \
TEST_CASE("push_back", GlistTag){   \
    auto obj = Glist{}; \
    obj.push_back(1);   \
    obj.push_back(2);   \
    REQUIRE(obj.size() == 2);   \
    REQUIRE(obj.str() == "{ [0] = 1, [1] = 2 }");   \
}   \
TEST_CASE("push_befor", GlistTag){ \
    auto obj = Glist{10, -1};   \
    REQUIRE(obj.size() == 10);  \
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1 }"); \
    obj.push_befor(3, 0);  \
    REQUIRE(obj.size() == 11);  \
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = 0, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1, [10] = -1 }");   \
}   \
TEST_CASE("remove", GlistTag){  \
    auto obj = Glist{10, -1};   \
    REQUIRE(obj.size() == 10);  \
    obj.remove(3);  \
    REQUIRE(obj.size() == 9);   \
}   \
TEST_CASE("clear", GlistTag){   \
    auto obj = Glist{10, -1};   \
    REQUIRE(obj.size() == 10);  \
    \
    obj.clear();    \
    REQUIRE(obj.size() == 0);   \
}   \
TEST_CASE("pop", GlistTag){ \
    auto obj = Glist{300, -1};  \
    REQUIRE(obj.size() == 300); \
    obj.pop();  \
    REQUIRE(obj.size() == 300 - 1); \
}   \
TEST_CASE("front", GlistTag){   \
    auto obj = Glist{2, -1};    \
    REQUIRE(obj.size() == 2);   \
    \
    REQUIRE(obj.front() == -1); \
    obj.front() = 11;   \
    REQUIRE(obj.front() == 11); \
}   \
TEST_CASE("op_pracket", GlistTag){  \
    auto obj = Glist{5, -1};    \
    REQUIRE(obj.size() == 5);   \
    \
    REQUIRE(obj[2] == -1);  \
    \
    obj[2] = 11;    \
    REQUIRE(obj[2] == 11);  \
}   \
TEST_CASE("str", GlistTag){ \
    auto obj = Glist{3, -1};    \
    REQUIRE(obj.size() == 3);   \
    \
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");   \
}   \
TEST_CASE("cctor", GlistTag){   \
    auto obj = Glist{3, -1};    \
    REQUIRE(obj.size() == 3);   \
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");   \
    \
    auto obj2(obj); \
    REQUIRE(obj2.size() == obj.size()); \
    REQUIRE(obj2.str() == obj.str());   \
}   \
TEST_CASE("op_cpy", GlistTag){  \
    auto obj = Glist{3, -1};    \
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");   \
    \
    Glist obj2 ;    \
    SECTION("obj size == obj3 size"){   \
        obj2.push_back(10); \
        obj2.push_back(100);    \
        obj2.push_back(1);  \
        obj2 = obj; \
        REQUIRE(obj2.size() == obj.size()); \
        REQUIRE(obj2.str() == obj.str());   \
    }   \
    Glist  obj3;    \
    SECTION("obj size < obj3 size"){    \
        REQUIRE(obj3.size() == 0);  \
        obj3 = obj; \
        REQUIRE(obj3.size() == obj.size()); \
        REQUIRE(obj3.str() == obj.str());   \
    }   \
    \
    Glist obj4(12, 2);  \
    SECTION("obj size > obj3 size"){    \
        REQUIRE(obj4.size() == 12); \
        obj4 = obj; \
        REQUIRE(obj4.size() == obj.size()); \
        REQUIRE(obj4.str() == obj.str());   \
    }   \
}   \
TEST_CASE("find", GlistTag){    \
    auto obj = Glist(); \
    obj.push_back(1);   \
    obj.push_back(10);  \
    obj.push_back(100); \
    obj.push_back(1000);    \
    \
    REQUIRE(obj.find(10) == 1); \
    REQUIRE(obj.find(2) == std::nullopt);   \
}   \
TEST_CASE("iterators", GlistTag){   \
    Glist obj;  \
    int i;  \
    for (i = 0; i < 10; i++)    \
    {   \
        obj.push_back(i);   \
    }   \
    \
    for (auto&& j : obj)    \
    {   \
        REQUIRE(j == 10 - i--); \
    }   \
    \
    REQUIRE(*obj.begin() == obj[0]);    \
    REQUIRE(obj.end() == typename Glist::Iterator(nullptr));    \
    \
}
// int
#define Glist List<int>
#define GlistTag TAG(List<int>)
COM_TEST

// short
#define Glist List<short>
#define GlistTag TAG(List<short>)
COM_TEST

// float
#define Glist List<float>
#define GlistTag TAG(List<float>)
COM_TEST

// double
#define Glist List<double>
#define GlistTag TAG(List<double>)
COM_TEST

/////////////////////
TEST_CASE("contructor()","[list<std::string>]"){
    auto obj = List<std::string>{};
    REQUIRE(obj.size() == 0);

    auto obj2 = List<std::string>{4, "1"};
    REQUIRE(obj2.size() == 4);

    REQUIRE(obj2.str() == "{ [0] = 1, [1] = 1, [2] = 1, [3] = 1 }");
}
TEST_CASE("push_back", "[list<std::string>]"){
    auto obj = List<std::string>{};
    obj.push_back("1");
    obj.push_back("2");
    REQUIRE(obj.size() == 2);
    REQUIRE(obj.str() == "{ [0] = 1, [1] = 2 }");
    
}
TEST_CASE("push_befor", "[list<std::string>]"){
    auto obj = List<std::string>{10, "-1"};
    REQUIRE(obj.size() == 10);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1 }");

    obj.push_befor(3, "0");
    REQUIRE(obj.size() == 11);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = 0, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1, [10] = -1 }");
}

TEST_CASE("push_after", "[list<std::string>]"){
    auto obj = List<std::string>{10, "-1"};
    REQUIRE(obj.size() == 10);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1 }");

    obj.push_after(3, "0");
    REQUIRE(obj.size() == 11);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = 0, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1, [10] = -1 }");
}

TEST_CASE("remove", "[list<std::string>]"){
    auto obj = List<std::string>{10, "-1"};
    REQUIRE(obj.size() == 10);
    obj.remove(3);
    REQUIRE(obj.size() == 9);
}

TEST_CASE("clear", "[list<std::string>]"){
    auto obj = List<std::string>{10, "-1"};
    REQUIRE(obj.size() == 10);

    obj.clear();
    REQUIRE(obj.size() == 0);
}

TEST_CASE("pop", "[list<std::string>]"){
    auto obj = List<std::string>{300, "-1"};
    REQUIRE(obj.size() == 300);
    obj.pop();
    REQUIRE(obj.size() == 300 - 1);
}

TEST_CASE("front", "[list<std::string>]"){
    auto obj = List<std::string>{2, "-1"};
    REQUIRE(obj.size() == 2);

    REQUIRE(obj.front() == "-1");
    obj.front() = "11";
    REQUIRE(obj.front() == "11");
}

TEST_CASE("op_pracket", "[list<std::string>]"){
    auto obj = List<std::string>{5, "-1"};
    REQUIRE(obj.size() == 5);

    REQUIRE(obj[2] == "-1");

    obj[2] = "11";
    REQUIRE(obj[2] == "11");
}

TEST_CASE("str", "[list<std::string>]"){
    auto obj = List<std::string>{3, "-1"};
    REQUIRE(obj.size() == 3);

    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");
}

TEST_CASE("cctor", "[list<std::string>]"){
    auto obj = List<std::string>{3, "-1"};
    REQUIRE(obj.size() == 3);
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");

    auto obj2(obj);
    REQUIRE(obj2.size() == obj.size());
    REQUIRE(obj2.str() == obj.str());
}

TEST_CASE("op_cpy", "[list<std::string>]"){
    auto obj = List<std::string>{3, "-1"};
    REQUIRE(obj.str() == "{ [0] = -1, [1] = -1, [2] = -1 }");

    List<std::string> obj2 ;
    SECTION("obj size == obj3 size"){
        obj2.push_back("10");
        obj2.push_back("100");
        obj2.push_back("1");
        obj2 = obj;
        REQUIRE(obj2.size() == obj.size());
        REQUIRE(obj2.str() == obj.str());
    }
    List<std::string>  obj3;
    SECTION("obj size < obj3 size"){
        REQUIRE(obj3.size() == 0);
        obj3 = obj;
        REQUIRE(obj3.size() == obj.size());
        REQUIRE(obj3.str() == obj.str());
    }

    List<std::string> obj4(12, "2");
    SECTION("obj size > obj3 size"){
        REQUIRE(obj4.size() == 12);
        obj4 = obj;
        REQUIRE(obj4.size() == obj.size());
        REQUIRE(obj4.str() == obj.str());
    }
}

TEST_CASE("find", "[list<std::string>]"){
    auto obj = List<std::string>();
    obj.push_back("1");
    obj.push_back("10");
    obj.push_back("100");
    obj.push_back("1000");

    REQUIRE(obj.find("10") == 1);
    REQUIRE(obj.find("2") == std::nullopt);
}

TEST_CASE("iterators", "[list<std::string>]"){
    List<std::string> obj;
    int i;

    for (i = 0; i < 10; i++)
    {
        obj.push_back(std::to_string(i));
    }
    for (auto j : obj)
    {
        REQUIRE(j == std::to_string(10 - i--));
    }

    REQUIRE(*obj.begin() == obj[0]);
    REQUIRE(obj.end() == typename List<std::string>::Iterator(nullptr));

}