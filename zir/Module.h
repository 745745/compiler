#pragma once

#include <iostream>
#include <fstream>
#include <memory>

#include "../parser/node.h"
#include "Function.h"

enum class OptimLevel
{
    None, O1
};

namespace ZIR
{
    class Block;
    class Value;
    class Module;
    class Function;
    class Instruction;
    typedef std::shared_ptr<Block> BlockPtr;
    typedef std::shared_ptr<Value> ValuePtr;
    typedef std::shared_ptr<Module> ModulePtr;
    typedef std::shared_ptr<Function> FuncPtr;
    typedef std::shared_ptr<Instruction> InstrPtr;

    class Module
    {
    public:
        Module(NCompUnit *ast, const std::string &outFilePath, OptimLevel optLevel) :
            ast(ast), outFilePath(outFilePath), optLevel(optLevel) {}
        void translate();
        void generateAsm();

    private:
        void printGlobalVars();
        void printFunctions();

        void addGlobalValue(NVarDecl *varDecl);
        void addFunction(NFuncDecl *funcDecl);

    private:
        NCompUnit *ast;
        std::string outFilePath;
        OptimLevel optLevel;

        std::vector<FuncPtr> functions;
        std::vector<ValuePtr> globalVars;
    };
}