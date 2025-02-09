CXX = g++
CXXFLAGS = -Wall -std=c++11

all: main

main: LetterCount.o WordCount.o LineCount.o main.o
	$(CXX) $(CXXFLAGS) -o main LetterCount.o WordCount.o LineCount.o main.o

LetterCount.o: LetterCount.cpp LetterCount.h
	$(CXX) $(CXXFLAGS) -c LetterCount.cpp

WordCount.o: WordCount.cpp WordCount.h
	$(CXX) $(CXXFLAGS) -c WordCount.cpp

LineCount.o: LineCount.cpp LineCount.h
	$(CXX) $(CXXFLAGS) -c LineCount.cpp

main.o: main.cpp LetterCount.h WordCount.h LineCount.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o main

