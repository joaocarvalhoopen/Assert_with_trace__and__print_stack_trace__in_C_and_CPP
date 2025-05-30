# Makefile

all:
	g++ -g -std=c++11 -Wall -o out.exe assert_with_trace.cpp main.cpp -lbacktrace

clean:
	rm out.exe

run:
	./out.exe
