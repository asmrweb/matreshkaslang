#include "interpreter.hpp"
#include "value.hpp"
#include <iostream>

void Interpreter::interpret(std::unique_ptr<Program> program) {
    for (auto& stmt : program->statements) {
        execute(stmt.get());
    }
}

void Interpreter::execute(Stmt* stmt) {
    if (auto varDecl = dynamic_cast<VarStmt*>(stmt)) {
        Value value = evaluate(varDecl->initializer.get());
        environment.define(varDecl->name.value, value);
    } else if (auto printStmt = dynamic_cast<PrintStmt*>(stmt)) {
        Value value = evaluate(printStmt->expression.get());
        std::cout << value.toString() << std::endl;
    } else if (auto exprStmt = dynamic_cast<ExpressionStmt*>(stmt)) {
        evaluate(exprStmt->expression.get());
    } else if (auto ifStmt = dynamic_cast<IfStmt*>(stmt)) {
        if (evaluate(ifStmt->condition.get()).isTrue()) {
            execute(ifStmt->thenBranch.get());
        } else if (ifStmt->elseBranch) {
            execute(ifStmt->elseBranch.get());
        }
    }
}