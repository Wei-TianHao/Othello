CC=gcc
CXX=g++
CXXFLAGS=-std=c++11

OBJS=one_step.o OthelloState.o naive.o roxanne.o lethe.o cooper.o

all: one_step is_end

one_step: $(OBJS)
	$(CXX) $(CXXFLAGS) -o one_step $(OBJS)

is_end: $(OBJS)
	$(CXX) $(CXXFLAGS) -o is_end is_end.o


one_step.o: one_step.cc OthelloState.hpp naive.hpp roxanne.hpp lethe.hpp cooper.hpp

is_end.o: OthelloState.hpp

naive.o: OthelloState.hpp
cooper.o: OthelloState.hpp
roxanne.o: OthelloState.hpp
lethe.o: OthelloState.hpp

.PHONY : clean
clean:
	rm one_step $(OBJS)