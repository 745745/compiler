#include "RegAllocator.h"

RegisterMapping SimpleAllocator::getMapping()
{
    RegisterMapping map;

    auto functions = module->getFunctions();

    for (auto func : functions)
    {
        int spill = 0;
        // TODO:
        // see each instruction in func
        // simply allocate stack space for every defined value
        for (auto block : func->blocks)
        {
            for (auto instr : block->getInstructions())
            {
                /*
                Value *v = instr->args[0]
                if (instr->is not control instruction)
                {
                    map[v] = ++spill;
                }
                */
            }
        }
    }
}

RegisterMapping LinearScanAllocator::getMapping()
{
    RegisterMapping map;

    auto functions = module->getFunctions();
}