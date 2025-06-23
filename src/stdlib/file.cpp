#include "stdlib/file.hpp"
#include <fstream>

Value файлы_читать(std::vector<Value>& args) {
    if (args.size() != 1 || !args[0].isString())
        throw RuntimeError("Функция 'читать' ожидает строку с путём");

    std::ifstream file(args[0].asString());
    if (!file.is_open()) {
        throw RuntimeError("Не могу открыть файл: " + args[0].asString());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return Value(buffer.str());
}

Value файлы_писать(std::vector<Value>& args) {
    if (args.size() != 2 || !args[0].isString() || !args[1].isString())
        throw RuntimeError("Функция 'писать' ожидает путь и содержимое");

    std::ofstream file(args[0].asString());
    if (!file.is_open()) {
        throw RuntimeError("Не могу открыть файл для записи: " + args[0].asString());
    }

    file << args[1].asString();
    return Value::undefined();
}

void registerFileModule(Environment& env) {
    auto fileObj = std::make_shared<NativeModule>();
    fileObj->methods["читать"] = файлы_читать;
    fileObj->methods["писать"] = файлы_писать;
    env.define("файлы", Value(fileObj));
}