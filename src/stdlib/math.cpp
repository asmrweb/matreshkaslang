#include "stdlib/math.hpp"
#include <cmath>

Value математика_sqrt(std::vector<Value>& args) {
    if (args.size() != 1 || !args[0].isNumber())
        throw RuntimeError("Функция sqrt ожидает одно число");

    return Value(sqrt(args[0].asNumber()));
}

void registerMathModule(Environment& env) {
    auto mathObj = std::make_shared<NativeModule>();
    mathObj->methods["sqrt"] = математика_sqrt;
    env.define("математика", Value(mathObj));
}