#pragma once
#include <iostream>
#include <sstream>
#include <cassert>
#include <source_location>

#define Test(func) {\
        std::cout << std::endl;\
        std::cout << "[" << __COUNTER__ + 1<< "] " << #func << " : ";\
        func();\
        std::cout << "SUCCESS" << std::endl;\
    }

constexpr void EXPECT_EQ(auto val, decltype(val) expe){ 
    if (!(val == expe)) {
        std::ostringstream oss;
        oss << "Expected: " << expe << ", but got: " << val;
        std::cerr << oss.str() << std::endl;
        assert(false);
    }
}
constexpr void EXPECT_NEQ(auto val, decltype(val) expe){
    if (val == expe) {
        std::ostringstream oss;
        oss << "Expected: " << expe << ", but got: " << val;
        std::cerr << oss.str() << std::endl;
        assert(false);
    }
} 