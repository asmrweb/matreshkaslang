#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.hpp"
#include "parser.hpp"
#include "interpreter.hpp"
#include "repl.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        runREPL();
    } else {
        std::string filename = argv[1];
        if (filename == "--repl") {
            runREPL();
        } else {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Ошибка: Не могу открыть файл " << filename << "\n";
                return 1;
            }
            std::stringstream buffer;
            buffer << file.rdbuf();
            std::string code = buffer.str();

            auto tokens = tokenize(code);
            auto ast = parse(tokens);
            Environment env;
            Interpreter interpreter(env);
            interpreter.interpret(ast);
        }
    }
    return 0;
}