CXX = g++
CXXFLAGS = -Wall -g

mytest:	checkers.o mytest.cpp
	$(CXX) $(CXXFLAGS) checkers.o mytest.cpp -o mytest

checkers.o: checkers.h checkers.cpp
	$(CXX) $(CXXFLAGS) -c checkers.cpp

run:
	./mytest

val1:
	valgrind ./mytest

clean:
	rm *~
	rm *.o
