#pragma once
#include<list>
#include<vector>
#include"User.h"
#include"Module.h"
using std::list;
using std::vector;

class Function :public User
{
public:
	void addBasicBlock(BasicBlock* p);
	void removeBasicBlock(BasicBlock* p);


private:
	list<BasicBlock*> blocks;
	Module* parent;
};
