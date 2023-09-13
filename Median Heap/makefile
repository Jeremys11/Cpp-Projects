CXX = g++
CXXFLAGS = -Wall -g -ansi

proj4: MedianHeap.o City.o proj4test7.cpp
	$(CXX) $(CXXFLAGS) MedianHeap.o City.o proj4test7.cpp  -o proj4

MedianHeap.o: MedianHeap.cpp MedianHeap.h
	$(CXX) $(CXXFLAGS) -c MedianHeap.cpp

City.o: City.cpp City.h
	$(CXX) $(CXXFLAGS) -c City.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj4