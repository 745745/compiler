CC := clang++
target := test

inc := Block.h Function.h Instruction.h Module.h Value.h
src := Block.cpp Function.cpp Instruction.cpp Module.cpp Value.cpp test.cpp

objs := *.o
flags := -g -std=c++17

all : $(target)

$(target) : $(objs)
	$(CC) $(objs) -o $(target) $(flags)

$(objs) : $(src) $(inc)
	$(CC) -c $(src) $(flags)

clean:
	rm $(objs) $(target)