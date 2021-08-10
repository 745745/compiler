# 定义编译命令变量
CC := clang++

targetAll := compiler

incParser := parser/node.h parser/parser.hpp
srcParser := parser/node.cpp parser/tokens.cpp parser/parser.cpp
objParser := node.o tokens.o parser.o

incIr := ir/BasicBlock.h ir/ConstantValue.h ir/Function.h ir/Instruction.h ir/Module.h \
		ir/Pass.h ir/Type.h ir/User.h ir/Value.h
srcIr := ir/Function.cpp ir/Instruction.cpp ir/Module.cpp ir/BasicBlock.cpp
objIr := Function.o Instruction.o Module.o BasicBlock.o

incAsm := assembly/AsmInstruction.h assembly/AsmTranslate.h
srcAsm := assembly/AsmInstruction.cpp assembly/AsmTranslate.cpp
objAsm := AsmInstruction.o AsmTranslate.o

incAll := $(incParser) $(incIr) $(incAsm)
srcAll := $(srcParser) $(srcIr) $(srcAsm) compiler.cpp
objAll := $(objParser) $(objIr) $(objAsm) compiler.o

flags := -g -std=c++17

all : $(objAll)
	$(CC) $(objAll) -o $(targetAll) $(flags)

$(objAll) : $(srcAll) $(incAll)
	$(CC) -c $(srcAll) $(flags)

clean:
	rm $(objAll) $(target)