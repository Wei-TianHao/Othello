CC=gcc
CXX=g++
CXXFLAGS=-std=c++11

STEP_OBJS=one_step.o OthelloState.o naive.o cooper.o
END_OBJS=is_end.o OthelloState.o naive.o cooper.o

all: one_step is_end

one_step: $(STEP_OBJS)
	$(CXX) $(CXXFLAGS) -o one_step $(STEP_OBJS)

is_end: $(END_OBJS)
	$(CXX) $(CXXFLAGS) -o is_end $(END_OBJS)

one_step.o: OthelloState.hpp cooper.hpp naive.hpp
cooper.o: OthelloState.hpp
naive.o: OthelloState.hpp

is_end.o: OthelloState.hpp

.PHONY : clean
clean:
	rm one_step $(STEP_OBJS) is_end $(END_OBJS)