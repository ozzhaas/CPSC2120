SHELL := /bin/bash
CXX = g++
CXXFLAGS = -g -Wall -o
TARGET1 = bad1
TARGET2 = prog1
TARGET3 = bad2
TARGET4 = prog2

make:
	$(CXX) $(CXXFLAGS) bad1 bad1.cpp
	$(CXX) $(CXXFLAGS) prog1 prog1.cpp
	$(CXX) $(CXXFLAGS) bad2 bad2.cpp
	$(CXX) $(CXXFLAGS) prog2 prog2.cpp
	$(CXX) $(CXXFLAGS) bad3 bad3.cpp
	$(CXX) $(CXXFLAGS) prog3 prog3.cpp

runBad1:
	time ./bad1 100000 > input1

runProg1:
	time ./prog1 < input1

runBad2:
	time ./bad2 100000 > input2

runProg2:
	time ./prog2 < input2

runBad3:
	time ./bad3 100000 > input3

runProg3:
	time ./prog3 < input3 > output3
