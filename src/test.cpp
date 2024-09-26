#include "Test.hpp"
#include "List.hpp"

void test_list_ctor(){
    auto obj = List<int>{};
    EXPECT_EQ(obj.size(), 0);

    auto obj2 = List<int>{4, 1};
    EXPECT_EQ(obj2.size(), 4);

    EXPECT_EQ(obj2.str(), "{ [0] = 1, [1] = 1, [2] = 1, [3] = 1 }");
}
void test_list_push_back(){
    auto obj = List<int>{};
    obj.push_back(1);
    obj.push_back(2);
    EXPECT_EQ(obj.size(), 2);
    EXPECT_EQ(obj.str(), "{ [0] = 1, [1] = 2 }");
    
}
void test_list_push_at(){
    auto obj = List<int>{10, -1};
    EXPECT_EQ(obj.size(), 10);
    EXPECT_EQ(obj.str(), "{ [0] = -1, [1] = -1, [2] = -1, [3] = -1, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1 }");

    obj.push_at(3, 0);
    EXPECT_EQ(obj.size(), 11);
    EXPECT_EQ(obj.str(), "{ [0] = -1, [1] = -1, [2] = -1, [3] = 0, [4] = -1, [5] = -1, [6] = -1, [7] = -1, [8] = -1, [9] = -1, [10] = -1 }");


}
void test_list_push_remove(){
    auto obj = List<int>{10, -1};
    EXPECT_EQ(obj.size(), 10);
    obj.remove(3);
    EXPECT_EQ(obj.size(), 9);
}
void test_list_clear(){
    auto obj = List<int>{10, -1};
    EXPECT_EQ(obj.size(), 10);

    obj.clear();
    EXPECT_EQ(obj.size(), 0);
}
void test_list_pop(){
    auto obj = List<int>{300, -1};
    EXPECT_EQ(obj.size(), 300);
    obj.pop();
    EXPECT_EQ(obj.size(), 300 - 1);
}
void test_list_front(){
    auto obj = List<int>{2, -1};
    EXPECT_EQ(obj.size(), 2);

    EXPECT_EQ(obj.front(), -1);
    obj.front() = 11;
    EXPECT_EQ(obj.front(), 11);
}

void test_list_op_pracket(){
    auto obj = List<int>{5, -1};
    EXPECT_EQ(obj.size(), 5);

    EXPECT_EQ(obj[2], -1);

    obj[2] = 11;
    EXPECT_EQ(obj[2], 11);
}

void test_list_str(){
    auto obj = List<int>{3, -1};
    EXPECT_EQ(obj.size(), 3);

    EXPECT_EQ(obj.str(), "{ [0] = -1, [1] = -1, [2] = -1 }");
}
void test_list_cctor(){
    auto obj = List<int>{3, -1};
    EXPECT_EQ(obj.size(), 3);
    EXPECT_EQ(obj.str(), "{ [0] = -1, [1] = -1, [2] = -1 }");

    auto obj2(obj);
    EXPECT_EQ(obj2.size(), obj.size());
    EXPECT_EQ(obj2.str(), obj.str());
}
void test_list_op_cpy(){
    auto obj = List<int>{3, -1};
    EXPECT_EQ(obj.str(), "{ [0] = -1, [1] = -1, [2] = -1 }");

    // obj size == obj2 size
    List<int> obj2 ;
    obj2.push_back(10);
    obj2.push_back(100);
    obj2.push_back(1);
    obj2 = obj;
    EXPECT_EQ(obj2.size(), obj.size());
    EXPECT_EQ(obj2.str(), obj.str());

    // obj size < obj3 size
    List<int>  obj3;
    EXPECT_EQ(obj3.size(), 0);
    obj3 = obj;
    EXPECT_EQ(obj3.size(), obj.size());
    EXPECT_EQ(obj3.str(), obj.str());

    // obj size < obj3 size
    List<int> obj4(12, 2);
    EXPECT_EQ(obj4.size(), 12);
    obj4 = obj;
    EXPECT_EQ(obj4.size(), obj.size());
    EXPECT_EQ(obj4.str(), obj.str());
}

int main(){
    Test(test_list_ctor);
    Test(test_list_push_back);
    Test(test_list_push_at);
    Test(test_list_push_remove);
    Test(test_list_clear);
    Test(test_list_pop);
    Test(test_list_front);
    Test(test_list_op_pracket);
    Test(test_list_str);
    Test(test_list_cctor);
    Test(test_list_op_cpy);
}