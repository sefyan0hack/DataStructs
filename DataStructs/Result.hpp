#pragma once
#include <variant>
template<typename Ok, typename Err>
class Result {
public:
    std::variant<Ok, Err> value;

    Result(const Ok& ok) : value(ok) {}
    Result(const Err& err) : value(err) {}

    bool is_ok() const {
        return std::holds_alternative<Ok>(value);
    }

    bool is_err() const {
        return std::holds_alternative<Err>(value);
    }

    Ok unwrap() const {
        if (is_ok()) {
            return std::get<Ok>(value);
        } else {
            throw std::runtime_error("Tried to unwrap an Err result");
        }
    }

    Err unwrap_err() const {
        if (is_err()) {
            return std::get<Err>(value);
        } else {
            throw std::runtime_error("Tried to unwrap an Ok result");
        }
    }
};