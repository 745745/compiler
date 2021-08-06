#!/bin/sh
for file in $(ls ./)
do
	if [ "${file##*.}"x = "sy"x ]
	then
		echo "This is test: $file \n"
		cat $file
		echo "\n"
		echo "This is test AST: $file \n"
		./parser.exe $file
		echo "\n"
		echo "This is test IR: $file \n"
		./a.out $file
		echo "\n"
	fi
done
