#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "token.hpp"

std::vector<Token> tokenize(const std::string& code) {
    std::vector<Token> tokens;
    std::regex pattern(R"((\bпеременная\b|\bесли\b|\bтогда\b|\bиначе\b|\bконец\b|\bфункция\b|\bвернуть\b|\bвывести\b|\bкласс\b|\bметод\b|\bэто\b|\bцикл\b|\bдо\b|\bв\b|\bДЖЕСОН\.разобрать$$(.*?)$$|\"(.*?)\"|\d+|[+\-*/=(){}[\],])|(\w+))");
    std::sregex_iterator next(code.begin(), code.end(), pattern);
    std::sregex_iterator end;

    while (next != end) {
        std::smatch match = *next;
        std::string val = match.str();
        if (val == "переменная") tokens.emplace_back(TokenType::VAR, val);
        else if (val == "если") tokens.emplace_back(TokenType::IF, val);
        else if (val == "тогда") tokens.emplace_back(TokenType::THEN, val);
        else if (val == "иначе") tokens.emplace_back(TokenType::ELSE, val);
        else if (val == "конец") tokens.emplace_back(TokenType::END, val);
        else if (val == "функция") tokens.emplace_back(TokenType::FUNCTION, val);
        else if (val == "вернуть") tokens.emplace_back(TokenType::RETURN, val);
        else if (val == "вывести") tokens.emplace_back(TokenType::PRINT, val);
        else if (val == "класс") tokens.emplace_back(TokenType::CLASS, val);
        else if (val == "метод") tokens.emplace_back(TokenType::METHOD, val);
        else if (val == "это") tokens.emplace_back(TokenType::THIS, val);
        else if (val == "цикл") tokens.emplace_back(TokenType::LOOP, val);
        else if (val == "до") tokens.emplace_back(TokenType::TO, val);
        else if (val == "в") tokens.emplace_back(TokenType::IN, val);
        else if (val == "+") tokens.emplace_back(TokenType::PLUS, val);
        else if (val == "-") tokens.emplace_back(TokenType::MINUS, val);
        else if (val == "*") tokens.emplace_back(TokenType::MULTIPLY, val);
        else if (val == "/") tokens.emplace_back(TokenType::DIVIDE, val);
        else if (val == "=") tokens.emplace_back(TokenType::EQUALS, val);
        else if (val == "(") tokens.emplace_back(TokenType::LPAREN, val);
        else if (val == ")") tokens.emplace_back(TokenType::RPAREN, val);
        else if (val == "{") tokens.emplace_back(TokenType::LBRACE, val);
        else if (val == "}") tokens.emplace_back(TokenType::RBRACE, val);
        else if (val == "[") tokens.emplace_back(TokenType::LBRACKET, val);
        else if (val == "]") tokens.emplace_back(TokenType::RBRACKET, val);
        else if (val == ",") tokens.emplace_back(TokenType::COMMA, val);
        else if (std::isdigit(val[0])) tokens.emplace_back(TokenType::NUMBER, val);
        else if (val.front() == '"') tokens.emplace_back(TokenType::STRING, val.substr(1, val.size()-2));
        else tokens.emplace_back(TokenType::IDENTIFIER, val);

        ++next;
    }

    return tokens;
}