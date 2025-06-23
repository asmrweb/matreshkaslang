#pragma once
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <map>

class NativeFunction;

using NativeFunctionPtr = std::shared_ptr<NativeFunction>;

class Value {
public:
    using InternalType = std::variant<
        std::monostate,
        double,
        std::string,
        bool,
        std::shared_ptr<std::map<std::string, Value>>,
        std::shared_ptr<std::vector<Value>>,
        NativeFunctionPtr
    >;

    enum class Type {
        UNDEFINED,
        NUMBER,
        STRING,
        BOOLEAN,
        OBJECT,
        ARRAY,
        FUNCTION
    };

    Value() : type(Type::UNDEFINED) {}
    Value(double number) : data(number), type(Type::NUMBER) {}
    Value(const std::string& str) : data(str), type(Type::STRING) {}
    Value(bool boolean) : data(boolean), type(Type::BOOLEAN) {}

    static Value undefined() { return Value(); }
    static Value object() { return Value(std::make_shared<std::map<std::string, Value>>()); }
    static Value array() { return Value(std::make_shared<std::vector<Value>>()); }
    static Value function(NativeFunctionPtr fn) { return Value(fn); }

    Type getType() const { return type; }
    bool isNumber() const { return type == Type::NUMBER; }
    bool isString() const { return type == Type::STRING; }
    bool isBoolean() const { return type == Type::BOOLEAN; }
    bool isTrue() const { return isBoolean() && std::get<bool>(data); }
    bool isObject() const { return type == Type::OBJECT; }
    bool isArray() const { return type == Type::ARRAY; }
    bool isFunction() const { return type == Type::FUNCTION; }

    double asNumber() const { return std::get<double>(data); }
    std::string asString() const { return std::get<std::string>(data); }
    bool asBoolean() const { return std::get<bool>(data); }

    std::string toString() const;

private:
    InternalType data;
    Type type;

    Value(const InternalType& d);
    Value(NativeFunctionPtr fn);
};

class NativeFunction {
public:
    virtual Value call(std