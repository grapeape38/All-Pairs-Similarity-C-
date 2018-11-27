CXX = g++
CXXFLAGS=-std=c++11 -g
OBJS=AllPairsDriver.o AllPairs0.o AllPairs1.o VectorList.o InvList.o VectorFunctions.o

all: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o allpairs 

#BinVectorList.o: BinVectorList.cpp BinVectorList.h
#AllPairsDriver.o: AllPairsDriver.cpp AllPairs0.cpp AllPairs1.cpp AllPairs2.cpp AllPairsBin.cpp
#AllPairs0.o: AllPairs0.cpp InvList.cpp AllPairs.h 
#AllPairs1.o: AllPairs1.cpp InvList.cpp VectorList.h AllPairs.h VectorFunctions.h
#AllPairs2.o: AllPairs1.cpp InvList.cpp VectorList.h AllPairs.h VectorFunctions.h
#AllPairsBinary.o: AllPairsBinary.cpp AllPairs.h VectorFunctions.h InvList.cpp
#VectorList.o : VectorList.h 
#VectorFunctions.o : VectorFunctions.h VectorFunctions.cpp

clean:
	rm -f *.o allpairs
