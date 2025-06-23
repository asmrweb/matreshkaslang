#include "codegen.hpp"
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>

using namespace llvm;

Value *NumberExpr::codeGen(CodeGenContext &context) {
    return ConstantFP::get(Type::getDoubleTy(context.context), value);
}

Value *BinaryOpExpr::codeGen(CodeGenContext &context) {
    Value *lhs = left->codeGen(context);
    Value *rhs = right->codeGen(context);

    if (!lhs || !rhs)
        return nullptr;

    switch (op) {
        case TokenType::PLUS:
            return context.builder.CreateFAdd(lhs, rhs, "addtmp");
        case TokenType::MINUS:
            return context.builder.CreateFSub(lhs, rhs, "subtmp");
        case TokenType::MULTIPLY:
            return context.builder.CreateFMul(lhs, rhs, "multmp");
        case TokenType::DIVIDE:
            return context.builder.CreateFDiv(lhs, rhs, "divtmp");
        default:
            return nullptr;
    }
}