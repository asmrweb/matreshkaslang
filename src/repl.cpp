#include <iostream>
#include <string>
#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"

void runREPL() {
    std::cout << "MatreshkaScript REPL\n";
    Environment env;
    Interpreter interpreter(env);

    while (true) {
        std::cout << ">>> ";
        std::string input;
        std::getline(std::cin, input);
        if (input == "выйти" || input == "exit") break;

        try {
            auto tokens = tokenize(input);
            auto ast = parse(tokens);
            interpreter.interpret(ast);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}