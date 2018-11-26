CXX = g++
CXXFLAGS=-std=c++11 -g
OBJS=AllPairsDriver.o AllPairs0.o AllPairs1.o Vectors.o InvList.o

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o allpairs 

AllPairsDriver.o: AllPairsDriver.cpp AllPairs0.cpp AllPairs1.cpp
AllPairs0.o: AllPairs0.cpp InvList.cpp AllPairs.h 
AllPairs1.o: AllPairs1.cpp InvList.cpp Vectors.h AllPairs.h 
Vectors.o : Vectors.h Vectors.cpp

clean:
	rm -f *.o allpairs
