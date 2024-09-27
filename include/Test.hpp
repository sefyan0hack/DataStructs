#pragma once
#include <iostream>
#include <sstream>
#include <cassert>
#include <source_location>
#include <type_traits>
#include <concepts>
#include <functional>
#include <vector>

template <typename T>
concept Streamable = requires(T a, std::ostream& os) {
    { os << a } -> std::same_as<std::ostream&>;
};
#define T(Class, member) {\
        std::cout << std::endl;\
        std::cout << "[" << __COUNTER__ + 1<< "] " << #Class"."#member << " : ";\
        Class##_##member();\
        std::cout << "SUCCESS" << std::endl;\
    }

constexpr void EXPECT_EQ(auto val, decltype(val) expe){
    if (!(val == expe)) {
        std::ostringstream oss;
        if constexpr (Streamable<decltype(expe)>) {
            oss << "Expected: " << expe << ", but got: " << val;
            std::cerr << oss.str() << std::endl;
        }
        else{
            std::cerr << "val and expected not Streamable " << std::endl;
        }
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

using TestFunction = std::function<void()>;
std::vector<TestFunction> rfuncs;

std::vector<TestFunction>& getFuncRegistry() {
    static std::vector<TestFunction> funcRegistry;
    return funcRegistry;
}

void registerFunc(TestFunction func) {
    getFuncRegistry().push_back(func);
}

class AutoRegistrar {
public:
    AutoRegistrar(TestFunction func) {
        registerFunc(func);
    }
};
#define Test(Class, member)           \
    void Class##_##member();                        \
    static AutoRegistrar _registrar_##Class##_##member([]() { T(Class, member); }); \
    void Class##_##member()

#define RUN_ALL_TESTS() {for (const auto& func : getFuncRegistry()) func();}