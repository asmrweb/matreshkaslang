#pragma once
#include <memory>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include "ast.hpp"

struct CodeGenContext {
    LLVMContext context;
    std::unique_ptr<Module> module;
    IRBuilder<> builder;
    std::map<std::string, llvm::Value*> locals;

    CodeGenContext();
    void generateCode(const std::vector<StmtPtr>& program);
};