#include "../include/Pass.h"
//循环优化

//首先需要找到循环

/*目前的状况是只能进行暴力优化，在一开始将所有的block打开成为指令序列，然后根据这些指令序列建表
  在指令序列当中搜索循环，对循环进行优化，可能的话还要对流程进行优化*/

loopDetection::loopDetection()
{
}

loopDetection::~loopDetection()
{
}

void loopDetection::run()
{
    for (auto func : mod.getFunctionList()) {
        BaseBlock* p = func->entry;
        while (p->succ_bbs_.size() != 0 && p->succ_bbs_[0] != nullptr) {
            InstructionList.insert(InstructionList.end(), p->insrList.begin(), p->insrList.end());
            p = p->succ_bbs_[0];
        }
        InstructionList.insert(InstructionList.end(), p->insrList.begin(), p->insrList.end());
    }
    for (auto inst: InstructionList)
    {
        inst->debugPrint();
        cout << endl;
    }
}