#pragma once
#include <map>
#include <string>
#include "value.hpp"

class Environment {
public:
    Environment() = default;

    void define(const std::string& name, const Value& value);
    Value get(const std::string& name);
    bool assign(const std::string& name, const Value& value);

private:
    std::map<std::string, Value> values;
};