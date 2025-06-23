#include "stdlib/module_loader.hpp"

void ModuleLoader::loadStandardModules(Environment& env) {
    registerMathModule(env);
    registerFileModule(env);
}