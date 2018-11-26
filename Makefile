CXX = g++
CXXFLAGS=-std=c++11 -g
OBJS=AllPairsDriver.o AllPairs0.o AllPairs1.o VectorList.o InvList.o

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o allpairs 

AllPairsDriver.o: AllPairsDriver.cpp AllPairs0.cpp AllPairs1.cpp
AllPairs0.o: AllPairs0.cpp InvList.cpp AllPairs.h 
AllPairs1.o: AllPairs1.cpp InvList.cpp VectorList.h AllPairs.h 
VectorList.o : VectorList.h VectorList.cpp

clean:
	rm -f *.o allpairs
