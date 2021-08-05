
#pragma once
#include"Module.h"



class Pass
{
public:
	void doPass();
	void addPass(PassMethod*);

private:	
	vector<PassMethod> method;
};


class PassMethod
{
public:
	void setModule(Module*);
	void run();

private:
	Module* mod;
};

