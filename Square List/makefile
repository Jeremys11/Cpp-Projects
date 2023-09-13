CXX = g++
CXXFLAGS = -Wall -g -ansi

proj2: SqList.o Int341.o p2timetest2.cpp
	$(CXX) $(CXXFLAGS) SqList.o Int341.o p2timetest2.cpp  -o proj2

SqList.o: SqList.cpp SqList.h
	$(CXX) $(CXXFLAGS) -c SqList.cpp

Int341.o: Int341.cpp Int341.h
	$(CXX) $(CXXFLAGS) -c Int341.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj2