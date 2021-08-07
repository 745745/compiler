
#pragma once
#include"Module.h"

/*
class Pass
{
public:
	void doPass();
	void addPass(PassMethod*);

private:	
	vector<PassMethod> method;
};*/

class PassMethod
{
public:
	void setModule(Module module)
	{
		mod = module;
	};
	virtual void run(){};

protected:
	Module mod;
};

class loopDetection : public PassMethod {
private:
    vector<Instruction*> InstructionList; //最终的大指令序列
public:
    loopDetection();
    ~loopDetection();
	void run();
};
