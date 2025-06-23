#pragma once
#include <string>

enum class TokenType {
    VAR, IF, THEN, ELSE, END,
    FUNCTION, RETURN, PRINT,
    CLASS, METHOD, THIS,
    LOOP, TO, IN,
    PLUS, MINUS, MULTIPLY, DIVIDE, EQUALS,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET, COMMA,
    NUMBER, STRING, IDENTIFIER
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};