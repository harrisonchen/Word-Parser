all: parser

parser: parser.o
	g++ -o parser parser.o

parser.o: parser.cpp
	g++ -c parser.cpp

clean:
	rm -rf *o parser

run:
	g++ -o parser parser.cpp
	./parser constitution.txt
