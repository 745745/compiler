#pragma once

#include <variant>

#include "../IR/Module.h"

typedef std::map<Value*, int> RegisterMapping;

class RegAllocator
{
public:
    RegAllocator(Module *module) : module(module) {}

    virtual RegisterMapping getMapping() = 0;
protected:
    Module *module;
};

class SimpleAllocator :
    public RegAllocator
{
public:
    SimpleAllocator(Module *module) :
        RegAllocator(module) {}

    RegisterMapping getMapping();
private:
};

class ChordalGraphAllocator:
    public RegAllocator
{
public:
    ChordalGraphAllocator(Module *module) :
        RegAllocator(module) {}

    RegisterMapping getMapping();
};

class LinearScanAllocator:
    public RegAllocator
{
    // input model must be guaranteed to contain IR instructions only in SSA forms
public:
    LinearScanAllocator(Module *module) :
        RegAllocator(module) {}

    RegisterMapping getMapping();
};

class GraphColoringAllocator;