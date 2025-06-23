#include "parser.hpp"
#include "ast.hpp"

std::unique_ptr<Program> parse(const std::vector<Token>& tokens) {
    Parser parser(tokens);
    return parser.parseProgram();
}

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

std::unique_ptr<Program> Parser::parseProgram() {
    auto program = std::make_unique<Program>();
    while (!isAtEnd()) {
        program->statements.push_back(parseStatement());
    }
    return program;
}

std::unique_ptr<Stmt> Parser::parseStatement() {
    if (match(TokenType::VAR)) {
        return parseVarDeclaration();
    } else if (match(TokenType::FUNCTION)) {
        return parseFunction();
    } else if (match(TokenType::PRINT)) {
        return parsePrintStatement();
    } else if (match(TokenType::IF)) {
        return parseIfStatement();
    } else if (match(TokenType::LOOP)) {
        return parseLoopStatement();
    } else {
        return parseExpressionStatement();
    }
}